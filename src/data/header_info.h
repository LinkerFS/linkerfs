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

#ifndef LINKERFS_HEADER_INFO_H
#define LINKERFS_HEADER_INFO_H


#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>

typedef struct file_format_version {
    uint8_t major;
    uint8_t minor;
} LINKERFS_WARP_VERSION;

typedef struct header_info {
    uint8_t magic[12];
    int32_t part_info_begin_offset;
    int64_t warp_size;
    uint16_t num_parts;
    LINKERFS_WARP_VERSION fmt_version;
    uint32_t unused;
} LINKERFS_HEADER;

static const unsigned char header_length = sizeof(LINKERFS_HEADER);

#endif //LINKERFS_HEADER_INFO_H
