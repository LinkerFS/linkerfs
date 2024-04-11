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

#include <stddef.h>
#include <stdlib.h>
#include "opt_parser.h"

int check_wrap_dir_valid(const char *path);

static int opt_processing(void *data, const char *arg, int key, struct fuse_args *outargs);

enum opt_type {
    LINKERFS_OPT_HELP
};


const struct fuse_opt opts[] = {
        FUSE_OPT_KEY("-h", LINKERFS_OPT_HELP),
        FUSE_OPT_KEY("--help", LINKERFS_OPT_HELP),
        FUSE_OPT_END
};


void opt_parse(struct fuse_args *args, struct linkerfs_mount_config *mount_config) {

    fuse_opt_parse(args, mount_config, opts, opt_processing);

}

static int
opt_processing(void *data, const char *arg, int key, struct fuse_args *outargs) {
    (void) outargs;

    struct linkerfs_mount_config *mount_config = (struct linkerfs_mount_config *) data;
    switch (key) {
        case FUSE_OPT_KEY_NONOPT:
            if (mount_config->wrap_dir == NULL) {
                mount_config->wrap_dir = arg;
                return 0;
            } else
                break;
        case LINKERFS_OPT_HELP:
            //TODO: print help
            exit(0);
        default:
            break;

    }
    return 1;
}

