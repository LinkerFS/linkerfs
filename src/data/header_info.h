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

struct file_format_version{
    uint8_t major;
    uint8_t minor;
};

struct header_info {
    uint8_t magic[12];
    int32_t part_info_begin_offset;
    int64_t warp_size;
    uint16_t num_parts;
    struct file_format_version fmt_version;
    uint32_t unused;
};

static const unsigned char header_length = sizeof(struct header_info);

#endif //LINKERFS_HEADER_INFO_H
