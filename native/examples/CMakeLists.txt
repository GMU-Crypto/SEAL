# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

cmake_minimum_required(VERSION 3.10)

project(SEALExamples VERSION 3.2.0 LANGUAGES CXX)

#add_library(FHE SHARED IMPORTED)
#set_target_properties(FHE
#   IMPORTED_LOCATION /home/pchatzig/MP-SPDZ/libFHE.so
#   INTERFACE_INCLUDE_DIRECTORIES /home/pchatzig/MP-SPDZ
#   INTERFACE_COMPILE_DEFINITIONS "USING_FHE;FHE_SHARED"
#)
#find_library(FHE libFHE.so PATHS /home/pchatzig/MP-SPDZ)
#find_library(SPDZ libSPDZ.so PATHS /home/pchatzig/MP-SPDZ)

# Executable will be in ../bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)

add_executable(sealexamples examples.cpp pir.cpp pir_client.cpp pir_server.cpp good_index.cpp share_at.cpp verifier_state.cpp)

# Import Microsoft SEAL
find_package(SEAL 3.2.0 EXACT REQUIRED)

# Link Microsoft SEAL
target_link_libraries(sealexamples SEAL::seal)


# Link additional external libraries
target_link_libraries(sealexamples gmp gmpxx)
target_link_libraries(sealexamples /usr/local/lib/libcryptopp.a)
target_link_libraries(sealexamples  /home/pchatzig/MP-SPDZ/libFHE.so)
target_link_libraries(sealexamples  /home/pchatzig/MP-SPDZ/libSPDZ.so)
target_link_libraries(sealexamples  /home/pchatzig/SEAL-3.2.0/include/usr/local/lib/libsodium.a)
include_directories( /home/pchatzig/MP-SPDZ /home/pchatzig/SEAL-3.2.0/include/usr/local/include /usr/local/include )

set(CMAKE_BUILD_TYPE DEBUG)
