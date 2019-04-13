if (NOT SANITIZE AND NOT ARCH_ARM AND NOT ARCH_32 AND NOT ARCH_PPC64LE)
    if (NOT EXISTS "${ClickHouse_SOURCE_DIR}/contrib/lfalloc/src/lf_allocX64.h")
        message (FATAL_ERROR "submodule contrib/lfalloc is missing. to fix try run: \n git submodule update --init --recursive")
    endif()
    set (USE_LFALLOC 1)
    set (USE_LFALLOC_RANDOM_HINT 1)
    set (LFALLOC_INCLUDE_DIR ${ClickHouse_SOURCE_DIR}/contrib/lfalloc/src)
    message (STATUS "Using lfalloc=${USE_LFALLOC}: ${LFALLOC_INCLUDE_DIR}")
endif ()
