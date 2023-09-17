cmake_minimum_required(VERSION 3.16)
project(hdr_histogram_cpp_example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(HDR_HISTOGRAM_BUILD_PROGRAMS OFF)
set(HDR_HISTOGRAM_BUILD_SHARED OFF)
set(HDR_HISTOGRAM_BUILD_STATIC ON)

# add_subdirectory(
#   ${CMAKE_CURRENT_SOURCE_DIR}/../../../vendor/HdrHistogram_c
#   ${CMAKE_CURRENT_BINARY_DIR}/HdrHistogram_c
# )

Include(FetchContent)

FetchContent_Declare(
  hdr_histogram
  GIT_REPOSITORY https://github.com/HdrHistogram/HdrHistogram_c.git
  GIT_TAG        0.11.8
)

FetchContent_MakeAvailable(hdr_histogram)

# This is needed to make sure that when building, the library's headers are
# treated as system headers, as otherwise clang-tidy will run on them.
#
# After cmake 3.25, this shouldn't be needed anymore: https://gitlab.kitware.com/cmake/cmake/-/issues/18040
get_target_property(HDR_HISTOGRAM_INCLUDES hdr_histogram_static INTERFACE_INCLUDE_DIRECTORIES)
set_target_properties(hdr_histogram_static PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${HDR_HISTOGRAM_INCLUDES}")

add_executable(hdr_histogram_example
  main.cc
  hdr_histogram.cc
)

target_compile_features(hdr_histogram_example
  PRIVATE
  cxx_std_17
)

target_link_libraries(hdr_histogram_example
  PRIVATE
  hdr_histogram_static
)
