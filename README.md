# linkerfs

---

# DESCRIPTION

`linkerfs` is a read-only filesystem based on FUSE, designed to remap any part of files to anywhere in the target file.

# Usage

`linkerfs <warp point> <mount_point>`

`warp point` must be a directory, and it is the directory that `linkerfs` will process.

linkerfs will passthrough the data and structure included in `warp point` to `mount point` except special files (see details in **How it works**).

If you are using samba, the option `-o allow_other` is needed.

# Dependence

`libfuse - 2.9.9` lower version maybe works as well.

# Support  Platform

Operating System:  64-bit Linux (32-bit may also work, but be cautious with size_t and off_t, smaller value may be helpful).

CPU: Little Endian

# How it works

linkerfs creates a read-only file system as mirror of `warp point`.

linkerfs will remap data according  configuration, when meeting the special file called `warp file`(format is below).

linkerfs only modify the file content, file name will leave it as it is .

# Warp configuration file format

**Notice**: the Byte-Order may different between CPUs.

#### Header Info:

Includes the basic information of target mapping. Its length is 64(decimal).

|      begin       | offset(hex) | length(Bytes in decimal) |                    definition                     |
|:----------------:|:-----------:|:------------------------:|:-------------------------------------------------:|
|        -         |      -      |            64            |                    header info                    |
| this file at 0x0 |     +00     |            12            | magic number(D1 FE 4C 69 6E 6B 65 72 46 53 B7 E3) |
|                  |     +0C     |            4             |      begin offset of parts info in this file      |
|                  |     +10     |            8             |       total size(the sum of each part size)       |
|                  |     +18     |            2             |                the number of parts                |
|                  |     +1A     |            1             |            major version(file format)             |
|                  |     +1B     |            1             |            minor version(file format)             |
|                  |     +1C     |            36            |                     reserved                      |

#### Parts info:

This area is made up of sequential part. Its length equals `the number of parts`  * 32 (decimal). Every part declares
the path from which to read data, the offset to seek before reading, and the size to read. The final data sequence is
the same as the part sequence.

Each part like this:

|   begin   | offset(hex) | length(Bytes in decimal) |                definition                 |
|:---------:|:-----------:|:------------------------:|:-----------------------------------------:|
|     -     |      -      |            32            |                 part info                 |
| part info |     +00     |            8             |    part size(data length of this part)    |
|           |     +08     |            8             |      offset need to seek before read      |
|           |     +10     |            4             | offset of full path that the file to read |
|           |     +14     |            2             | length of full path that the file to read |
|           |     +16     |            10            |                 reserved                  |

#### Path info:

**Notice**:Each path info does not need to end with `\0`.

Includes ASCII characters, possibly located anywhere except the header and parts info area. Typically, it follows the Parts info.

