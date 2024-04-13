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

#ifndef LINKERFS_PART_INFO_H
#define LINKERFS_PART_INFO_H

#include <stdint.h>


struct part_info {
    uint64_t file_size;
    uint32_t path_offset;
    uint16_t path_length;
};

#endif //LINKERFS_PART_INFO_H
