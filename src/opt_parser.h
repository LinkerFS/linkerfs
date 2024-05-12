/*
 * LinkerFS: a data remapping filesystem
 * Copyright (C) 2024  kaedeair <kaedeair@outlook.com>
 *
 * This file is part of LinkerFS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LinkerFS. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LINKERFS_OPT_PARSER_H
#define LINKERFS_OPT_PARSER_H

#include <fuse_opt.h>
#include "data/mount_config.h"

void opt_parse(struct fuse_args *args, LINKERFS_MOUNT_CONFIG *mount_config);

#endif //LINKERFS_OPT_PARSER_H
