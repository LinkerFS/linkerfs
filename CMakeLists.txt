cmake_minimum_required(VERSION 3.5)
project(LinkerFS LANGUAGES C)
set(CMAKE_C_STANDARD 99)

find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED IMPORTED_TARGET fuse)
set(SOURCES
        src/linkerfs.c
        src/io/base.c
        src/io/warp.c
        src/opt_parser.c
)
set(HEADERS
        src/data/mount_config.h
        src/data/part_info.h
        src/io/base.h
        src/opt_parser.h
        src/io/warp.h
        src/data/header_info.h
)
include_directories(fuse)
include_directories(src)
add_executable(linkerfs ${HEADERS} ${SOURCES} ${FUSE_INCLUDE_DIRS})
target_link_libraries(linkerfs PRIVATE PkgConfig::FUSE ${Threads})


