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

#ifndef LINKERFS_HEADER_INFO_H
#define LINKERFS_HEADER_INFO_H


#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>


struct header_info {
    unsigned char magic[16];
    int64_t size;
    uint16_t part_num;
    uint32_t unused;
};

static const unsigned char header_length = sizeof(struct header_info);

#endif //LINKERFS_HEADER_INFO_H
