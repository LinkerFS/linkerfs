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

#define FUSE_USE_VERSION 29

#include <fuse.h>
#include <string.h>
#include <errno.h>

static int linkerfs_getattr(const char *path, struct stat *stbuf) {
    int res = 0;
    return res;
}

static int linkerfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                            off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    return 0;
}

static int linkerfs_open(const char *path, struct fuse_file_info *fi) {
    if ((fi->flags & O_ACCMODE) != O_RDONLY)
        return -EROFS;

    return 0;
}

static int linkerfs_read(const char *path, char *buf, size_t size, off_t offset,
                         struct fuse_file_info *fi) {
    return size;
}

static int linkerfs_release(const char *path, struct fuse_file_info *fi) {
    (void) path;
    (void) fi;
    return 0;
}

static const struct fuse_operations linkerfs_operations = {
        .getattr = linkerfs_getattr,
        .readdir = linkerfs_readdir,
        .open    = linkerfs_open,
        .read    = linkerfs_read,
        .release = linkerfs_release
};

int main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &linkerfs_operations, NULL);
}