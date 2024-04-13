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
    unsigned char major;
    unsigned char minor;
};

struct header_info {
    unsigned char magic[12];
    int32_t part_info_begin_offset;
    int64_t size;
    uint16_t part_num;
    struct file_format_version fmt_version;
    uint32_t unused;
};

static const unsigned char header_length = sizeof(struct header_info);

#endif //LINKERFS_HEADER_INFO_H
