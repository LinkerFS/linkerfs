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

#ifndef LINKERFS_PART_INFO_H
#define LINKERFS_PART_INFO_H

#include <stdint.h>

struct part_info {
    int64_t file_size;
    int64_t file_begin_offset;
    int32_t path_offset;
    uint16_t path_length;
    uint16_t unused;
};

static const unsigned char part_info_length = sizeof(struct part_info);

#endif //LINKERFS_PART_INFO_H
