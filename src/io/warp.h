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

#ifndef LINKERFS_WARP_H
#define LINKERFS_WARP_H

#include <unistd.h>
#include "data/header_info.h"

int is_warp_file(const char *path, LINKERFS_HEADER *header);

ssize_t warp_read(int warp_fd, void *buf, size_t size, off_t offset, LINKERFS_HEADER *header);

#endif //LINKERFS_WARP_H
