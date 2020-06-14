cmake_minimum_required(VERSION 3.9)
set(CMAKE_VERBOSE_MAKEFILE ON)

## Global properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if(NOT GLOBAL_LIBS_LIST)
  define_property(GLOBAL PROPERTY GLOBAL_LIBS_LIST
      BRIEF_DOCS "Global list of libs"
      FULL_DOCS "Global list of libs")
  set_property(GLOBAL PROPERTY GLOBAL_LIBS_LIST "")
endif()
#在子模块中可通过以下语句加入其它库SUB_LIB
# set_property(GLOBAL APPEND PROPERTY GLOBAL_LIBS_LIST SUB_LIB)

if(NOT GLOBAL_INCLUDE_LIST)
  define_property(GLOBAL PROPERTY GLOBAL_INCLUDE_LIST
      BRIEF_DOCS "Global list of includes"
      FULL_DOCS "Global list of includes")
  set_property(GLOBAL PROPERTY GLOBAL_INCLUDE_LIST "")
endif()
# set_property(GLOBAL APPEND PROPERTY GLOBAL_INCLUDE_LIST include)


## Project name
set (PROJECT_NAME S4)
project(${PROJECT_NAME})
message(STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

## Thirdparty
add_subdirectory("thirdparty")

## CMake module path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## Compiler features
set(CMAKE_WARN_AS_ERROR ON)
if(MSVC)
  include(SetCompilerFeatures)
endif()
include(SetCompilerWarnings)
include(SetPlatformFeatures)
include(SystemInformation)

add_definitions(-D__STDC_CONSTANT_MACROS)#ffmepg or some libs require this
add_definitions(-D__STDC_FORMAT_MACROS)

message(STATUS "CMAKE_C_COMPILER=${CMAKE_C_COMPILER} CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")

if(NOT MSVC)
  message(STATUS "CC_VERSION=")
  EXECUTE_PROCESS( COMMAND ${CMAKE_C_COMPILER} -dumpversion CC_VERSION )
  message(STATUS "CXX_VERSION=")
  EXECUTE_PROCESS( COMMAND ${CMAKE_CXX_COMPILER} -dumpversion CXX_VERSION )
endif()

## -- QT --
message(STATUS "_QT_PATH=${_QT_PATH}")
if (NOT EXISTS ${_QT_PATH})
  if(MSVC)
    message(FATAL_ERROR "_QT_PATH error! Please use -D_QT_PATH=path/to/QT/msvc2017_64")
  else()
    message(FATAL_ERROR "_QT_PATH error! Please use -D_QT_PATH=path/to/QT/folder_which_contains_include_and_lib")
  endif()
endif()

set(CMAKE_PREFIX_PATH ${_QT_PATH}) #设置Qt安装路径
set(CMAKE_AUTOMOC ON) #打开全局moc,设置自动生成moc文件，一定要设置
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED)
list(APPEND LINKLIBS   Qt5::Core Qt5::Gui Qt5::Qml Qt5::Quick)


# -- OpenCV --
# find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc imgcodecs videoio calib3d)
# if(NOT OpenCV_FOUND) # if not OpenCV 3.x, then imgcodecs are not found
#   message(STATUS "OpenCV imgcodecs missing")
#   # find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc)
# endif()
# include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
# list(APPEND LINKLIBS ${OpenCV_LIBS})
# message(STATUS " OpenCV_LIBS=${OpenCV_LIBS}")
# message(STATUS "OpenCV ${OpenCV_VERSION} found (${OpenCV_CONFIG_PATH})")

# # -- OpenSSL libraries --
# if(CYGWIN)
#   set(OPENSSL_ROOT_DIR "/usr/lib")
#   set(OPENSSL_INCLUDE_DIR "/usr/include")
#   set(OPENSSL_CRYPTO_LIBRARY "/usr/lib/libcrypto.dll.a")
#   set(OPENSSL_SSL_LIBRARY "/usr/lib/libssl.dll.a")
# elseif(MINGW)
#   set(OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/OpenSSL/MinGW")
#   set(OPENSSL_USE_STATIC_LIBS TRUE)
# elseif(MSVC)
#   set(OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/OpenSSL/VS")
#   set(OPENSSL_USE_STATIC_LIBS TRUE)
#   set(OPENSSL_MSVC_STATIC_RT TRUE)
# endif()
# find_package(OpenSSL REQUIRED)
# message(STATUS "OpenSSL version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")

# if(WIN32)
#   find_package(Crypt REQUIRED)
#   find_package(WinSock REQUIRED)
# else()
#   # mkl TBC...
#   FIND_LIBRARY(iomp5_LIBRARY
#           iomp5
#     /opt/intel/compilers_and_libraries_2020.0.166/linux/compiler/lib/intel64_lin
#   )
#   message(STATUS "iomp5_LIBRARY= ${iomp5_LIBRARY}")
# endif()



## Link libraries
list(APPEND LINKLIBS ${OPENSSL_LIBRARIES})
if(WIN32)
  list(APPEND LINKLIBS ${CRYPT_LIBRARIES})
  list(APPEND LINKLIBS ${WINSOCK_LIBRARIES})
endif()
# list(APPEND LINKLIBS cpp_common)  #not ready

if(NOT MSVC)
  list(APPEND LINKLIBS stdc++fs)
endif()

## System directories
get_property(dirs DIRECTORY ${SYSTEM} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "SYSTEM dir has: '${dir}'")
endforeach()

## Library
file(GLOB_RECURSE LIB_HEADER_FILES "include/*.h")
file(GLOB_RECURSE LIB_INLINE_FILES "include/*.inl")
file(GLOB_RECURSE LIB_SOURCE_FILES "source/*.cpp")
set_source_files_properties(${LIB_SOURCE_FILES} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")

add_library(${PROJECT_NAME} ${LIB_HEADER_FILES} ${LIB_INLINE_FILES} ${LIB_SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include;")

## collect GLOBAL_INCLUDE_LIST
get_property(global_include GLOBAL PROPERTY GLOBAL_INCLUDE_LIST)
message(STATUS "GLOBAL_INCLUDE_LIST = ${global_include}")
target_include_directories(${PROJECT_NAME} PUBLIC "${global_include};")

## collect GLOBAL_LIBS_LIST
get_property(global_libs GLOBAL PROPERTY GLOBAL_LIBS_LIST)
message(STATUS "GLOBAL_LIBS_LIST = ${global_libs}")
target_link_libraries(${PROJECT_NAME} ${LINKLIBS} ${global_libs})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER libraries)

list(APPEND INSTALL_TARGETS ${PROJECT_NAME})
list(APPEND LINKLIBS ${PROJECT_NAME})



## Additional module components: benchmarks, examples, plugins, tests, tools and install
if(NOT AI_basic_MODULE)
  # Application
  file(GLOB APP_HEADER_FILES "application/*.h")
  file(GLOB APP_INLINE_FILES "application/*.inl")
  file(GLOB APP_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/application" "application/*.cpp")
  foreach(APP_SOURCE_FILE ${APP_SOURCE_FILES})
    string(REGEX REPLACE "(.*)\\.cpp" "\\1" APP_NAME ${APP_SOURCE_FILE})
    set(APP_TARGET "${PROJECT_NAME}-${APP_NAME}")
    set_source_files_properties(application/${APP_SOURCE_FILE} PROPERTIES COMPILE_FLAGS "${PEDANTIC_COMPILE_FLAGS}")
    add_executable(${APP_TARGET} ${APP_HEADER_FILES} ${APP_INLINE_FILES} application/${APP_SOURCE_FILE})
    target_link_libraries(${APP_TARGET} ${LINKLIBS})
    set_target_properties(${APP_TARGET} PROPERTIES FOLDER application)
    list(APPEND INSTALL_TARGETS ${APP_TARGET})
    list(APPEND INSTALL_TARGETS_PDB ${APP_TARGET})
  endforeach()
  
  # Install
  install(TARGETS ${INSTALL_TARGETS}
    RUNTIME DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    LIBRARY DESTINATION "${PROJECT_SOURCE_DIR}/bin"
    ARCHIVE DESTINATION "${PROJECT_SOURCE_DIR}/bin")

  # Install *.pdb files
  if(MSVC)
    foreach(INSTALL_TARGET_PDB ${INSTALL_TARGETS_PDB})
      install(FILES $<TARGET_PDB_FILE:${INSTALL_TARGET_PDB}> DESTINATION "${PROJECT_SOURCE_DIR}/bin")
    endforeach()
  endif()
endif()
