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

#include "linkerfs/filesystem/fuse/opt_parser.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int check_warp_point_valid(const char *path);

static int opt_processing(void *data, const char *arg, int key, struct fuse_args *outargs);

enum opt_type {
    LINKERFS_OPT_HELP
};


const struct fuse_opt opts[] = {FUSE_OPT_KEY("-h", LINKERFS_OPT_HELP), FUSE_OPT_KEY("--help", LINKERFS_OPT_HELP),
                                FUSE_OPT_END};

void opt_parse(struct fuse_args *args, LINKERFS_MOUNT_CONFIG *mount_config) {

    fuse_opt_parse(args, mount_config, opts, opt_processing);
}

void usage() {
    fprintf(stderr, "usage: linkerfs wrappoint mountpoint [options]\n\n"
                    "general options:\n"
                    "    -o opt,[opt...]        mount options\n"
                    "    -h   --help            print help\n"
                    "\n");
}

static int opt_processing(void *data, const char *arg, int key, struct fuse_args *outargs) {
    (void) outargs;

    LINKERFS_MOUNT_CONFIG *mount_config = (LINKERFS_MOUNT_CONFIG *) data;
    switch (key) {
        case FUSE_OPT_KEY_NONOPT:
            if (mount_config->warp_point == NULL) {
                mount_config->warp_point = arg;
                return 0;
            } else
                break;
        case LINKERFS_OPT_HELP:
            usage();
            exit(0);
        default:
            break;
    }
    return 1;
}
