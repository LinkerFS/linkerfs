/*
  LinkerFS: Filesystem based on FUSE for splitting or unioning streams
  Copyright (C) 2024  kaedeair <kaedeair@outlook.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU LGPLv3 License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the file LICENSE for more details.
*/

#include <memory.h>
#include <errno.h>

#include "warp.h"
#include "base.h"
#include "data/part_info.h"

/*
 *  magic_number: hex "LinkerFS"
 */
static const unsigned char magic_number[8] = {0x4c, 0x69, 0x6e, 0x6b, 0x65, 0x72, 0x46, 0x53};


int is_warp_file(const char *path, struct header_info *header) {
    int res;
    if (!header)
        return 0;
    res = (int) fs_read(path, header, header_length, 0);
    if (res < header_length)
        return 0;
    res = memcmp(header->magic, magic_number, sizeof(magic_number)) == 0;

    return res;
}


ssize_t warp_read(const int warp_fd, void *buf, size_t size, off_t offset, struct header_info *header) {

    if (!header)
        return 0;
    if (offset < 0) {
        return -errno;
    }
    ssize_t res;
    off_t part_offset = 0;
    size_t left_size = size;
    char part_real_path[4097];
    const struct part_info *part = NULL;
    if (warp_fd == -1)
        return -errno;
    unsigned char part_info_buf[part_info_length * header->part_num];
    res = pread(warp_fd, part_info_buf, part_info_length * header->part_num, 32);
    if (res == -1)
        return -errno;

    if (offset < header->size) {
        int i = 0;
        // find first data which part in
        while (i < header->part_num) {
            part = (struct part_info *) part_info_buf + i;
            part_offset += part->file_size;
            if (part_offset > offset)
                break;
            ++i;
        }
        if (!part)
            return -1;
        //calculate offset of part begin
        part_offset = part->file_size - (part_offset - offset);
        while (left_size > 0 && i < header->part_num) {

            //read part real path
            res = pread(warp_fd, part_real_path, part->path_length, part->path_offset);
            if (res == -1)
                return -errno;
            part_real_path[res + 1] = '\0';
            //size_has_read = size - left_size
            res = fs_read(part_real_path, buf + size - left_size,
                          left_size > part->file_size ? part->file_size : left_size, part->start_offset + part_offset);
            //only first part need add part_offset
            part_offset = 0;
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
