# LinkerFS

---

# DESCRIPTION

`linkerfs` is a read-only filesystem based on FUSE. It allows remapping arbitrary parts of files to arbitrary positions
in a target file.

# Usage

`linkerfs <warp point> <mount_point>`

`warp point` must be a directory, and it is the directory that `linkerfs` will process.

`linkerfs` passes through the directory structure and file data from `warp point` to `mount point`,
except for special files (see **How it works**).

If you are using samba, the option `-o allow_other` is needed.

# Dependence

Requires `libfuse`≥ 2.9.9 (older versions may work, but are not guaranteed).

# Support Platform

* OS: 64-bit Linux (32-bit may work, but use caution with `size_t` and `off_t`).
* CPU: Little Endian only

# How it works

`linkerfs` creates a read-only mirror of the `warp point` directory.
When it encounters a special file called a `warp file`,it remaps the file contents according to the embedded rules(see
format below).
Only file contents are remapped; Each file retains its original name, identical to its corresponding warp file.

# Warp configuration file format

**Alias**: A `warp file` (short for `warp configuration file`) defines how file contents should be remapped.

**Note**: Byte order may vary across different CPU architecture.

#### Header Info:

Located at the beginning of the `warp file`, it contains basic information about the source data mapping.
The length is 64 bytes.

|       Field Name       | Offset | Length(Bytes) |                               Description                               |
|:----------------------:|:------:|:-------------:|:-----------------------------------------------------------------------:|
|         magic          |  0x00  |      12       |            Magic number(D1 FE 4C 69 6E 6B 65 72 46 53 B7 E3)            |
| part_info_begin_offset |  0x0C  |       4       | Absolute offset (from start of warp file) to the parts info in the file |
|       warp_size        |  0x10  |       8       |                   Total size (sum of all part sizes)                    |
|       num_parts        |  0x18  |       2       |                    Number of data parts in the file                     |
|         major          |  0x1A  |       1       |                       Major version (file format)                       |
|         minor          |  0x1B  |       1       |                       Minor version (file format)                       |
|        reserved        |  0x1C  |      36       |                         Reserved for future use                         |

#### Parts info:

This section consists of sequential parts.
Its total length is num_parts * 32 bytes.

Each part defines:

* The size of data to read
* The seek offset in the source file
* The absolute offset to the source file's path string

Each part like this:

|    Field Name     | Offset | Length(Bytes) |                                Description                                 |
|:-----------------:|:------:|:-------------:|:--------------------------------------------------------------------------:|
|     data_size     |  0x00  |       8       |                Number of bytes to read from the source file                |
| data_begin_offset |  0x08  |       8       |                Offset within the file to begin reading from                |
|    path_offset    |  0x10  |       4       | Absolute offset (from start of warp file) to the source file's path string |
|    path_length    |  0x14  |       2       |                  Length of the file path (in bytes/UTF-8)                  |
|     reserved      |  0x16  |      10       |                          Reserved for future use                           |

#### Paths info:

Includes UTF-8 encoded file paths,
which may be located anywhere in the file except within the header or parts info areas.
Typically, it follows the Parts info.

**Note**:Each path info does not need to end with `\0`.

