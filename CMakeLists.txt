cmake_minimum_required(VERSION 3.5)
project(LinkerFS)
find_package(Threads REQUIRED)
FIND_PACKAGE(PkgConfig REQUIRED)
pkg_check_modules(FUSE REQUIRED IMPORTED_TARGET fuse)
set(SOURCES
    src/linkerfs.c
)
include_directories(fuse)
add_executable(linkerfs ${SOURCES} ${FUSE_INCLUDE_DIRS})
target_link_libraries(linkerfs  PRIVATE PkgConfig::FUSE ${Threads})


