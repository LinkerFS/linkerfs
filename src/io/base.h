/*
  LinkerFS: a data remapping filesystem
  Copyright (C) 2024  kaedeair <kaedeair@outlook.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU LGPLv3 License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the file LICENSE for more details.
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
