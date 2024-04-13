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

#ifndef LINKERFS_PARTINFO_H
#define LINKERFS_PARTINFO_H

#include <stdint.h>


struct PartInfo {
    uint64_t fileSize;
    uint32_t pathOffset;
    uint16_t pathLength;
};

#endif //LINKERFS_PARTINFO_H
