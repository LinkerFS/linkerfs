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

#ifndef LINKERFS_BASE_H
#define LINKERFS_BASE_H

#include <fuse.h>
#include <stdio.h>
#include <bits/struct_stat.h>

ssize_t fs_read(const char *path, void *buf, size_t size, off_t offset);

int fs_readdir(const char *path, void *buf, fuse_fill_dir_t filler);

int fs_getattr(const char *path, struct stat *buf);

#endif //LINKERFS_BASE_H
