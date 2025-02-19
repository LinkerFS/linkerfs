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

#define FUSE_USE_VERSION 29

#include <fuse.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linkerfs/filesystem/fuse/opt_parser.h"
#include "linkerfs/filesystem/data/mount_config.h"
#include "linkerfs/filesystem/io/base.h"
#include "linkerfs/filesystem/io/warp.h"


static LINKERFS_MOUNT_CONFIG mount_config;

static char *get_real_path(const char *path) {
    char *real_path = malloc(strlen(mount_config.warp_point) + strlen(path));
    strcpy(real_path, mount_config.warp_point);
    strcat(real_path, path);
    return real_path;
}

static int linkerfs_getattr(const char *path, struct stat *stbuf) {
    int res;
    LINKERFS_HEADER header;
    char *real_path = get_real_path(path);
    res = fs_getattr(real_path, stbuf);
    memset(&header, 0, header_length);
    if (is_warp_file(real_path, &header))
        stbuf->st_size = header.warp_size;
    free(real_path);
    return res;
}

static int linkerfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                            off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;
    int res;
    char *real_path = get_real_path(path);
    res = fs_readdir(real_path, buf, filler);
    free(real_path);
    return res;
}

static int linkerfs_open(const char *path, struct fuse_file_info *fi) {
    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EROFS;
    return 0;
}

static int linkerfs_read(const char *path, char *buf, size_t size, off_t offset,
                         struct fuse_file_info *fi) {
    ssize_t res;
    LINKERFS_HEADER header;
    memset(&header, 0, header_length);
    char *real_path = get_real_path(path);

    if (is_warp_file(real_path, &header)) {
        int warp_fd = open(real_path, O_RDONLY);
        res = warp_read(warp_fd, buf, size, offset, &header);
        close(warp_fd);
    } else
        res = fs_read(real_path, buf, size, offset);

    free(real_path);
    return (int) res;
}

static int linkerfs_release(const char *path, struct fuse_file_info *fi) {
    (void) path;
    (void) fi;
    close(fi->fh);
    return 0;
}

int check_warp_point_valid(const char *path) {
    struct stat buf;
    int res = -1;
    if (path && stat(path, &buf) == 0 && S_IFDIR & buf.st_mode)
        res = 0;
    return res;
}


static const struct fuse_operations linkerfs_operations = {
        .getattr = linkerfs_getattr,
        .readdir = linkerfs_readdir,
        .open    = linkerfs_open,
        .read    = linkerfs_read,
        .release = linkerfs_release
};


int main(int argc, char *argv[]) {


    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    opt_parse(&args, &mount_config);
    if (check_warp_point_valid(mount_config.warp_point) != 0) {
        fprintf(stderr, "warp point: %s is invalid !\n", mount_config.warp_point);
        exit(1);
    }
    return fuse_main(args.argc, args.argv, &linkerfs_operations, NULL);
}