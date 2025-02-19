/*
 * LinkerFS: a data remapping filesystem
 * Copyright (C) 2024-2025  kaedeair <kaedeair@outlook.com>
 *
 * This file is part of LinkerFS.
 *
 * LinkerFS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * LinkerFS is distributed in the hope that it will be useful,but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LinkerFS. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LINKERFS_FORMAT_VERSION_H
#define LINKERFS_FORMAT_VERSION_H

#include "header_info.h"

const LINKERFS_WARP_VERSION format_version = {
        .major=0x0,
        .minor=0x0
};

#endif //LINKERFS_FORMAT_VERSION_H
