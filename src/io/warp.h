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

#ifndef LINKERFS_WARP_H
#define LINKERFS_WARP_H

#include <unistd.h>
#include "data/header_info.h"

int is_warp_file(const char *path, struct header_info *header);

ssize_t warp_read(int warp_fd, void *buf, size_t size, off_t offset, struct header_info *header);

#endif //LINKERFS_WARP_H
