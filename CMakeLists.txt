cmake_minimum_required(VERSION 3.5)
project(LinkerFS LANGUAGES C)
set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED IMPORTED_TARGET fuse)
set(SOURCES
        src/fuse/opt_parser.c
        src/linkerfs.c
        src/io/base.c
        src/io/warp.c
        src/fuse/opt_parser.c
)
set(HEADERS
        include/linkerfs/filesystem/data/format_version.h
        include/linkerfs/filesystem/data/mount_config.h
        include/linkerfs/filesystem/data/part_info.h
        include/linkerfs/filesystem/io/base.h
        include/linkerfs/filesystem/fuse/opt_parser.h
        include/linkerfs/filesystem/io/warp.h
        include/linkerfs/filesystem/data/header_info.h
)
include_directories(src)
include_directories(include)
add_executable(linkerfs ${HEADERS} ${SOURCES} ${FUSE_INCLUDE_DIRS})
target_link_libraries(linkerfs PRIVATE PkgConfig::FUSE ${Threads})
