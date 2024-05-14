/*
 * LinkerFS: a data remapping filesystem
 * Copyright (C) 2024  kaedeair <kaedeair@outlook.com>
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

#include "base.h"

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


ssize_t fs_read(const char *path, void *buf, size_t size, off_t offset) {
    if (offset < 0) {
        return -errno;
    }
    int fd;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return -errno;
    ssize_t res;
    res = pread(fd, buf, size, offset);
    close(fd);
    if (res == -1) {
        return -errno;
    }
    return res;
}

int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler) {
    DIR *dp;
    struct dirent *de;
    dp = opendir(path);
    if (dp == NULL)
        return -errno;
    while ((de = readdir(dp)) != NULL) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de->d_ino;
        st.st_mode = de->d_type << 12;
        if (filler(buf, de->d_name, &st, 0))
            break;
    }

    closedir(dp);
    return 0;
}

int fs_getattr(const char *path, struct stat *buf) {
    int res;
    res = lstat(path, buf);
    if (res == -1)
        return -errno;
    return res;
}