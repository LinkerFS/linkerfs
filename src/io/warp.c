/*
 * LinkerFS: a data remapping filesystem
 * Copyright (C) 2024-2025  kaedeair <kaedeair@outlook.com>
 *
 * This file is part of LinkerFS.
 *
 * LinkerFS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * LinkerFS is distributed in the hope that it will be useful,but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LinkerFS. If not, see <https://www.gnu.org/licenses/>.
 */

#include <memory.h>
#include <errno.h>

#include "linkerfs/filesystem/io/warp.h"
#include "linkerfs/filesystem/io/base.h"
#include "linkerfs/filesystem/data/part_info.h"


int is_warp_file(const char *path, LINKERFS_HEADER *header) {
    int res;
    if (!header)
        return 0;
    res = (int) fs_read(path, header, header_length, 0);
    if (res < header_length)
        return 0;
    res = memcmp(header->magic, magic_number, sizeof(magic_number)) == 0;

    return res;
}


ssize_t warp_read(const int warp_fd, void *buf, size_t size, off_t offset, LINKERFS_HEADER *header) {

    if (!header)
        return 0;
    if (offset < 0) {
        return -errno;
    }
    ssize_t res;
    off_t part_read_offset = 0;
    size_t left_size = size;
    char part_real_path[4097];
    LINKERFS_PART *part = NULL;
    if (warp_fd == -1)
        return -errno;
    unsigned char part_info_buf[part_info_length * header->num_parts];
    res = pread(warp_fd, part_info_buf, part_info_length * header->num_parts, header->part_info_begin_offset);
    if (res == -1)
        return -errno;

    if (offset < header->warp_size) {
        int i = 0;
        // find first data which part in
        while (i < header->num_parts) {
            part = (LINKERFS_PART *) part_info_buf + i;
            part_read_offset += part->data_size;
            if (part_read_offset > offset)
                break;
            ++i;
        }
        if (!part)
            return -1;
        //compute the starting offset of the part data.
        part_read_offset = part->data_size - (part_read_offset - offset);
        while (left_size > 0 && i < header->num_parts) {
            //get real path of this part
            res = pread(warp_fd, part_real_path, part->path_length, part->path_offset);
            if (res == -1)
                return -errno;
            part_real_path[res + 1] = '\0';
            //size_has_read = size - left_size
            res = fs_read(part_real_path, buf + size - left_size,
                          left_size > part->data_size ? part->data_size : left_size,
                          part->data_begin_offset + part_read_offset);
            //only first part need add part_read_offset
            part_read_offset = 0;
            if (res == -1)
                return -errno;
            left_size -= res;
            ++part;
            ++i;
        }
    } else
        return 0;
    if (left_size > 0)
        res = size - left_size;

    return res;
}
