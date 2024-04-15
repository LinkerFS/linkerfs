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

#ifndef LINKERFS_OPT_PARSER_H
#define LINKERFS_OPT_PARSER_H

#include <fuse_opt.h>
#include "data/mount_config.h"

void opt_parse(struct fuse_args *args, struct linkerfs_mount_config *mount_config);

#endif //LINKERFS_OPT_PARSER_H
