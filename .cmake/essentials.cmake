########################################################################################################################

# define the project name to be used in the code
set(ROBOCIN_PROJECT_NAME ${CMAKE_PROJECT_NAME})

if (NOT ROBOCIN_PROJECT_NAME)
  message(FATAL_ERROR "essentials: ROBOCIN_PROJECT_NAME is not defined.")
endif ()

########################################################################################################################

# define the project path to be used in the code
if (NOT ROBOCIN_PROJECT_PATH)
  message(FATAL_ERROR "essentials: ROBOCIN_PROJECT_PATH is not defined.")
endif ()

########################################################################################################################

# set CMAKE_EXPORT_COMPILE_COMMANDS to ON to generate a compile_commands.json file in the build directory by default
# this file is used by clang tools such as clangd, clang-tidy and clang-format
if (NOT CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

########################################################################################################################

# (Helper) Concatenate two paths using '/' as separator
function(robocin_concatenate_paths lhs rhs result)
    if (NOT ${lhs} STREQUAL "" AND NOT ${rhs} STREQUAL "")
        set(${result} "${lhs}/${rhs}" PARENT_SCOPE)
    elseif (NOT ${lhs} STREQUAL "")
        set(${result} "${lhs}" PARENT_SCOPE)
    elseif (NOT ${rhs} STREQUAL "")
        set(${result} "${rhs}" PARENT_SCOPE)
    else ()
        set(${result} "" PARENT_SCOPE)
    endif ()
endfunction()

########################################################################################################################

include(GNUInstallDirs) # provided by CMake

########################################################################################################################

# find Threads package
find_package(Threads REQUIRED)

########################################################################################################################

# Find abseil installation
# It enable the following variables:
#   absl::...                             the abseil libraries (https://abseil.io/docs/cpp/guides)
find_package(absl CONFIG REQUIRED HINTS "/usr/local/absl" "/opt/absl" "/usr/local/protobuf" "/opt/protobuf")
message(STATUS "Using absl: ${absl_VERSION}")

########################################################################################################################

# find Google Test package
# it enable the following variables:
#   GTest::gtest                          the gtest library
#   GTest::gtest_main                     the gtest_main library, which is used to link against the main function
#   GTest::gmock                          the gmock library
#   GTest::gmock_main                     the gmock_main library, which is used to link against the main function

# find GTest installation
# looks for GTest cmake config files installed by GTest's cmake installation.
find_package(GTest CONFIG REQUIRED HINTS "/usr/local/googletest" "/opt/googletest")
message(STATUS "Using GTest: ${GTest_VERSION}")

include(GoogleTest) # provided by CMake

enable_testing() # enable testing for the entire project

########################################################################################################################

# find Google Benchmark package
# it enable the following variables:
#   benchmark::benchmark                  the benchmark library
#   benchmark::benchmark_main             the benchmark_main library, which is used to link against the main function

# find Google Benchmark installation
# looks for Google Benchmark cmake config files installed by Google Benchmark's cmake installation.
find_package(benchmark CONFIG HINTS "/usr/local/benchmark" "/opt/benchmark")
message(STATUS "Using Google Benchmark: ${benchmark_VERSION}")

########################################################################################################################

# Find Protobuf installation
# Looks for protobuf cmake config files installed by Protobuf's cmake installation.
# It enable the following variables:
#   protobuf::libprotobuf                 the protobuf library
#   $<TARGET_FILE:protobuf::protoc>       the protobuf compiler
find_package(utf8_range CONFIG HINTS "/usr/local/protobuf" "/opt/protobuf") # protobuf dependency.
find_package(Protobuf CONFIG REQUIRED HINTS "/usr/local/protobuf" "/opt/protobuf")
message(STATUS "Using Protobuf: ${Protobuf_VERSION}")

########################################################################################################################

# Find cppzmq package
# It enable the following variables:
#   cppzmq                                the cppzmq library

# Find cppzmq installation
# Looks for cppzmq cmake config files installed by cppzmq's cmake installation.
find_package(ZeroMQ CONFIG REQUIRED HINTS "/usr/local/libzmq" "/opt/libzmq")
find_package(cppzmq CONFIG REQUIRED HINTS "/usr/local/cppzmq" "/opt/cppzmq")
message(STATUS "Using cppzmq: ${cppzmq_VERSION}")

########################################################################################################################

# add cpp library
# named parameters:
#  NAME: name of the library
#  HDRS: header files
#  SRCS: source files
#  MODS: module files
#  DEPS: dependencies
#  MACROS: macros
#  CONFIGS: CMake configurable header files
#  COMPILE_OPTIONS: compile options
#  COMPILE_FEATURES: compile features
function(robocin_cpp_library)
  cmake_parse_arguments(
          ARG                                                                     # prefix of output variables
          ""                                                                      # list of names of the boolean arguments
          "NAME"                                                                  # list of names of mono-valued arguments
          "HDRS;SRCS;MODS;DEPS;MACROS;CONFIGS;COMPILE_OPTIONS;COMPILE_FEATURES"   # list of names of multi-valued arguments
          ${ARGN}                                                                 # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # if there isn't at least one module file, then should be at least one header file and one source file
  if (NOT ARG_MODS)
    # if there isn't at least one header file, then the library is not created
    if (NOT ARG_HDRS)
      message(FATAL_ERROR "robocin_cpp_library: no header files given.")
    endif ()

    # if there isn't at least one source file, then the library is not created
    if (NOT ARG_SRCS)
      message(FATAL_ERROR "robocin_cpp_library: no source files given.")
    endif ()
  endif ()

  # if there are CMake configurable files, then they are configured and added to the library
  if (ARG_CONFIGS)
    foreach (CONFIG_FILE ${ARG_CONFIGS})
      get_filename_component(config_last_extension ${CONFIG_FILE} LAST_EXT)

      if (NOT ${config_last_extension} STREQUAL ".in")
        message(FATAL_ERROR "robocin_cpp_library: invalid extension '${config_last_extension}' for configurable file '${CONFIG_FILE}'.")
      endif ()

      get_filename_component(config_absolute_file ${CONFIG_FILE} ABSOLUTE)
      get_filename_component(config_absolute_path ${config_absolute_file} DIRECTORY)
      file(RELATIVE_PATH config_relative_subdirectory ${CMAKE_CURRENT_SOURCE_DIR} ${config_absolute_path})

      get_filename_component(config_filename ${CONFIG_FILE} NAME_WLE)
      robocin_concatenate_paths("${config_relative_subdirectory}" "${config_filename}" config_filename)

      configure_file(${CONFIG_FILE} ${config_filename})
      robocin_concatenate_paths("${CMAKE_CURRENT_BINARY_DIR}" "${config_filename}" config_filename_real_path)
      list(APPEND CONFIG_HDRS "${config_filename_real_path}")
    endforeach ()
  endif ()

  add_library(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_MODS} ${CONFIG_HDRS}) # add library with given name, headers, sources and modules
  target_link_libraries(${ARG_NAME} PUBLIC ${ARG_DEPS}) # link library with given dependencies

  if (ARG_MODS)
    if (CMAKE_CXX_STANDARD)
      if (CMAKE_CXX_STANDARD GREATER_EQUAL 20)
        target_compile_features(${ARG_NAME} PUBLIC cxx_std_${CMAKE_CXX_STANDARD})
      else ()
        message(FATAL_ERROR "robocin_cpp_library: modules are only supported with C++20 or newer.")
      endif ()
    else ()
      message(WARNING "robocin_cpp_library: CMAKE_CXX_STANDARD is not defined when adding modules to library '${ARG_NAME}'. Using C++20 as default.")
      target_compile_features(${ARG_NAME} PUBLIC cxx_std_20)
    endif ()

    target_sources(${ARG_NAME} PUBLIC FILE_SET CXX_MODULES FILES ${ARG_MODS})
  endif ()

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

  if (ARG_COMPILE_OPTIONS)
    target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
  endif ()

  if (ARG_COMPILE_FEATURES)
    target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
  endif ()

  # installing steps:
  #  - include directories to be used by other projects
  target_include_directories(${ARG_NAME} INTERFACE
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  #  - install header files preserving the directory structure
  foreach (HDR_FILE ${ARG_HDRS})
    get_filename_component(header_absolute_file ${HDR_FILE} ABSOLUTE)
    get_filename_component(header_absolute_path ${header_absolute_file} DIRECTORY)
    file(RELATIVE_PATH header_relative_path ${ROBOCIN_PROJECT_PATH} ${header_absolute_path})

    robocin_concatenate_paths("${CMAKE_INSTALL_INCLUDEDIR}" "${header_relative_path}" header_install_path)
    install(FILES ${HDR_FILE} DESTINATION "${header_install_path}")
  endforeach ()
  #  - install module files preserving the directory structure
  foreach (MOD_FILE ${ARG_MODS})
    get_filename_component(module_absolute_file ${MOD_FILE} ABSOLUTE)
    get_filename_component(module_absolute_path ${module_absolute_file} DIRECTORY)
    file(RELATIVE_PATH module_relative_path ${ROBOCIN_PROJECT_PATH} ${module_absolute_path})

    robocin_concatenate_paths("${CMAKE_INSTALL_INCLUDEDIR}" "${module_relative_path}" module_install_path)
    install(FILES ${MOD_FILE} DESTINATION "${module_install_path}")
  endforeach ()
  #  - install config files preserving the directory structure
  foreach (CONFIG_HDR ${CONFIG_HDRS})
    file(RELATIVE_PATH config_relative_path ${ROBOCIN_PROJECT_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

    get_filename_component(config_relative_subdirectory ${CONFIG_HDR} DIRECTORY)
    file(RELATIVE_PATH config_relative_subdirectory ${CMAKE_CURRENT_BINARY_DIR} ${config_relative_subdirectory})

    robocin_concatenate_paths("${config_relative_path}" "${config_relative_subdirectory}" config_relative_path)
    robocin_concatenate_paths("${CMAKE_INSTALL_INCLUDEDIR}" "${config_relative_path}" config_install_path)

    install(FILES ${CONFIG_HDR} DESTINATION "${config_install_path}")
  endforeach ()
  #  - install library
  install(TARGETS ${ARG_NAME} EXPORT "${PROJECT_NAME}Targets" CXX_MODULES_BMI DESTINATION modules
                                                              FILE_SET HEADERS DESTINATION include
                                                              FILE_SET CXX_MODULES DESTINATION modules)
  #  - install CMake configuration files
  install(
          EXPORT "${PROJECT_NAME}Targets"
          NAMESPACE "${PROJECT_NAME}::"
          FILE "${PROJECT_NAME}Config.cmake"
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
          CXX_MODULES_DIRECTORY cxx_modules
  )

endfunction(robocin_cpp_library)

########################################################################################################################

# Add cpp unit test
# Named parameters:
#  NAME: name of the test
#  HDRS: header files
#  SRCS: source files
#  MODS: module files
#  DEPS: dependencies
#  MACROS: macros
#  COMPILE_OPTIONS: compile options
#  COMPILE_FEATURES: compile features
function(robocin_cpp_test)
  cmake_parse_arguments(
          ARG                                                             # prefix of output variables
          ""                                                              # list of names of the boolean arguments
          "NAME"                                                          # list of names of mono-valued arguments
          "HDRS;SRCS;MODS;DEPS;MACROS;COMPILE_OPTIONS;COMPILE_FEATURES"   # list of names of multi-valued arguments
          ${ARGN}                                                         # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # check if at least one source file is given with suffix '_test.cpp'
  if (NOT ARG_SRCS)
    message(FATAL_ERROR "robocin_cpp_test: no source files given.")
  else ()
    set(FILTERED_SRCS ${ARG_SRCS})
    list(FILTER FILTERED_SRCS INCLUDE REGEX "_test\\.cpp$")

    if (NOT FILTERED_SRCS)
      message(FATAL_ERROR "robocin_cpp_test: no source files given with suffix '_test.cpp'.")
    endif ()
  endif ()

  add_executable(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_MODS}) # add test with given name, headers, sources and modules
  target_link_libraries(${ARG_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MODS)
    target_sources(${ARG_NAME} PUBLIC FILE_SET CXX_MODULES FILES ${ARG_MODS})
  endif ()

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

  if (ARG_COMPILE_OPTIONS)
    target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
  endif ()

  if (ARG_COMPILE_FEATURES)
    target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
  endif ()

  gtest_discover_tests(${ARG_NAME})

endfunction(robocin_cpp_test)

########################################################################################################################

# Add cpp benchmark test
# Named parameters:
#  NAME: name of the test
#  HDRS: header files
#  SRCS: source files
#  MODS: module files
#  DEPS: dependencies
#  MACROS: macros
#  COMPILE_OPTIONS: compile options
#  COMPILE_FEATURES: compile features
function(robocin_cpp_benchmark_test)
  cmake_parse_arguments(
          ARG                                                             # prefix of output variables
          ""                                                              # list of names of the boolean arguments
          "NAME"                                                          # list of names of mono-valued arguments
          "HDRS;SRCS;MODS;DEPS;MACROS;COMPILE_OPTIONS;COMPILE_FEATURES"   # list of names of multi-valued arguments
          ${ARGN}                                                         # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # check if at least one source file is given with suffix '_benchmark.cpp'
  if (NOT ARG_SRCS)
    message(FATAL_ERROR "robocin_cpp_benchmark_test: no source files given.")
  else ()
    set(FILTERED_SRCS ${ARG_SRCS})
    list(FILTER FILTERED_SRCS INCLUDE REGEX "_benchmark\\.cpp$")

    if (NOT FILTERED_SRCS)
      message(FATAL_ERROR "robocin_cpp_benchmark_test: no source files given with suffix '_benchmark.cpp'.")
    endif ()
  endif ()

  add_executable(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_MODS}) # add test with given name, headers, sources and modules
  target_link_libraries(${ARG_NAME} PRIVATE benchmark::benchmark benchmark::benchmark_main ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MODS)
    target_sources(${ARG_NAME} PUBLIC FILE_SET CXX_MODULES FILES ${ARG_MODS})
  endif ()

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

  if (ARG_COMPILE_OPTIONS)
    target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
  endif ()

  if (ARG_COMPILE_FEATURES)
    target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
  endif ()

endfunction(robocin_cpp_benchmark_test)

########################################################################################################################

# Add cpp executable
# Named parameters:
#  NAME: name of the executable
#  HDRS: header files
#  SRCS: source files
#  MODS: module files
#  DEPS: dependencies
#  MACROS: macros
#  COMPILE_OPTIONS: compile options
#  COMPILE_FEATURES: compile features
function(robocin_cpp_executable)
  cmake_parse_arguments(
          ARG                                                             # prefix of output variables
          ""                                                              # list of names of the boolean arguments
          "NAME"                                                          # list of names of mono-valued arguments
          "HDRS;SRCS;MODS;DEPS;MACROS;COMPILE_OPTIONS;COMPILE_FEATURES"   # list of names of multi-valued arguments
          ${ARGN}                                                         # arguments of the function to parse (ARGN contains all the arguments after the function name)
  )

  # check if at least one source file is given with suffix '_main.cpp'
  if (NOT ARG_SRCS)
    message(FATAL_ERROR "robocin_cpp_executable: no source files given.")
  else ()
    set(FILTERED_SRCS ${ARG_SRCS})
    list(FILTER FILTERED_SRCS INCLUDE REGEX "_main\\.cpp$")

    if (NOT FILTERED_SRCS)
      message(FATAL_ERROR "robocin_cpp_executable: no source files given with suffix '_main.cpp'.")
    endif ()
  endif ()

  add_executable(${ARG_NAME} ${ARG_HDRS} ${ARG_SRCS} ${ARG_MODS}) # add executable with given name, headers, sources and modules
  target_link_libraries(${ARG_NAME} PRIVATE ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_NAME="${ROBOCIN_PROJECT_NAME}")
  target_compile_definitions(${ARG_NAME} PRIVATE ROBOCIN_PROJECT_PATH="${ROBOCIN_PROJECT_PATH}")

  if (ARG_MODS)
    target_sources(${ARG_NAME} PUBLIC FILE_SET CXX_MODULES FILES ${ARG_MODS})
  endif ()

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

  if (ARG_COMPILE_OPTIONS)
    target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
  endif ()

  if (ARG_COMPILE_FEATURES)
    target_compile_features(${ARG_NAME} ${ARG_COMPILE_FEATURES})
  endif ()

endfunction(robocin_cpp_executable)

########################################################################################################################

# Add cpp proto library
# Named parameters:
#  NAME: name of the library
#  PROTOS: proto files
#  DEPS: dependencies
#  MACROS: macros
#  COMPILE_OPTIONS: compile options
#  COMPILE_FEATURES: compile features
function(robocin_cpp_proto_library)
  cmake_parse_arguments(
          ARG                                                     # prefix of output variables
          ""                                                      # list of names of the boolean arguments
          "NAME"                                                  # list of names of mono-valued arguments
          "PROTOS;DEPS;MACROS;COMPILE_OPTIONS;COMPILE_FEATURES"   # list of names of multi-valued arguments
          ${ARGN}                                                 # arguments of the function to parse
  )

  # if there isn't at least one proto file, then the library is not created
  if (NOT ARG_PROTOS)
    message(WARNING "robocin_cpp_proto_library: no proto files given for library '${ARG_NAME}'.")
    return()
  endif ()

  set(proto_hdrs)
  set(proto_srcs)

  foreach (PROTO ${ARG_PROTOS})
    get_filename_component(proto_name ${PROTO} NAME_WE)
    get_filename_component(proto_absolute_file ${PROTO} ABSOLUTE)
    get_filename_component(proto_absolute_path ${proto_absolute_file} DIRECTORY)
    file(RELATIVE_PATH proto_relative_file ${ROBOCIN_PROJECT_PATH} ${proto_absolute_file})
    file(RELATIVE_PATH proto_relative_path ${ROBOCIN_PROJECT_PATH} ${proto_absolute_path})

    set(proto_hdr_file "${CMAKE_BINARY_DIR}/${proto_relative_path}/${proto_name}.pb.h")
    set(proto_src_file "${CMAKE_BINARY_DIR}/${proto_relative_path}/${proto_name}.pb.cc")

    add_custom_command(
            OUTPUT "${proto_hdr_file}" "${proto_src_file}"
            COMMAND $<TARGET_FILE:protobuf::protoc>
            ARGS --proto_path ${ROBOCIN_PROJECT_PATH}
            --cpp_out "${CMAKE_BINARY_DIR}"
            "${proto_relative_file}"
            DEPENDS "${proto_absolute_file}"
            WORKING_DIRECTORY ${ROBOCIN_PROJECT_PATH}
    )

    list(APPEND proto_hdrs ${proto_hdr_file})
    list(APPEND proto_srcs ${proto_src_file})

  endforeach (PROTO)

  add_library(${ARG_NAME} ${proto_hdrs} ${proto_srcs})
  target_link_libraries(${ARG_NAME} PUBLIC protobuf::libprotobuf ${ARG_DEPS}) # link library with given dependencies

  target_include_directories(${ARG_NAME} PRIVATE ${ROBOCIN_PROJECT_PATH})
  target_include_directories(${ARG_NAME} PRIVATE ${CMAKE_BINARY_DIR})

  if (ARG_MACROS)
    target_compile_definitions(${ARG_NAME} ${ARG_MACROS})
  endif ()

  if (ARG_COMPILE_OPTIONS)
    target_compile_options(${ARG_NAME} ${ARG_COMPILE_OPTIONS})
  endif ()

  # installing steps:
  #  - include directories to be used by other projects
  target_include_directories(${ARG_NAME} INTERFACE
          $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  #  - install header files preserving the directory structure
  foreach (HDR_FILE ${proto_hdrs})
    file(RELATIVE_PATH header_relative_path ${ROBOCIN_PROJECT_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

    get_filename_component(header_relative_subdirectory ${HDR_FILE} DIRECTORY)
    file(RELATIVE_PATH header_relative_subdirectory ${CMAKE_CURRENT_BINARY_DIR} ${header_relative_subdirectory})

    robocin_concatenate_paths("${header_relative_path}" "${header_relative_subdirectory}" header_relative_path)
    robocin_concatenate_paths("${CMAKE_INSTALL_INCLUDEDIR}" "${header_relative_path}" header_install_path)

    install(FILES ${HDR_FILE} DESTINATION "${header_install_path}")
  endforeach ()

  #  - install the project's library
  install(TARGETS ${ARG_NAME} EXPORT "${PROJECT_NAME}Targets")

  #  - install CMake configuration files
  install(
          EXPORT "${PROJECT_NAME}Targets"
          NAMESPACE "${PROJECT_NAME}::"
          FILE "${PROJECT_NAME}Config.cmake"
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  )

endfunction(robocin_cpp_proto_library)

########################################################################################################################
