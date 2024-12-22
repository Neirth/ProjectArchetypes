# Copyright (c) 2020 Wind River Systems, Inc. All Rights Reserved.
#
cmake_minimum_required(VERSION 3.15)
project(ElectricalGripHardware LANGUAGES C CXX)
set(arch gcc_ntoaarch64le)

set(CMAKE_C_COMPILER qcc)
set(CMAKE_C_COMPILER_TARGET ${arch})
set(CMAKE_CXX_COMPILER q++)
set(CMAKE_CXX_COMPILER_TARGET ${arch})

foreach(DIR ${CMAKE_INCLUDE_PATH})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${DIR}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${DIR}")
endforeach()

foreach(DIR ${CMAKE_LIBRARY_PATH})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${DIR}")
endforeach()

set(CMAKE_VERBOSE_MAKEFILE ON)

# Configuración específica para QNX
if(${CMAKE_SYSTEM_NAME} STREQUAL "QNX")
    set(CMAKE_C_COMPILER qcc)
    set(CMAKE_CXX_COMPILER QCC)
    set(CMAKE_LINKER qcc)
    set(CMAKE_AR qnx-ar)
    set(CMAKE_RANLIB qnx-ranlib)
endif()

# Configuración de compilación para modo debug y release
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -ffast-math")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -ffast-math")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Oz -ffast-math")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Oz -ffast-math")

add_executable(ElectricalGridHardware 
    src/ElectricalGridHardware.c
    src/services/main_service.c
    src/services/data_collector_service.c
    src/services/predict_load_service.c
    src/utils/main_utils.c
)

target_link_libraries(ElectricalGridHardware PRIVATE
    xml2
    curl
    ssl
    crypto
    z
    m
)

add_custom_target(rpi_image
    COMMAND mkifs -r ../../config/rpi_image.build -o ../../build/ElectricalGripHardware.ifs
    DEPENDS ElectricalGridHardware
)
