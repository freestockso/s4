if(NOT TARGET asio)
  # add_subdirectory("asio")
  # set_target_properties(YY_cpp_common PROPERTIES FOLDER modules/asio)

  find_package(OpenSSL REQUIRED)
  message(STATUS "OpenSSL version: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}")
  if (WIN32)
    macro(get_WIN32_WINNT version)
        if (CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if ("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif ("${verMajor}" MATCHES "10")
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif(CMAKE_SYSTEM_VERSION)
    endmacro(get_WIN32_WINNT)

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
  endif(WIN32)

  # Module library
  file(GLOB SOURCE_FILES "asio/asio/src/*.cpp")

  add_library(asio ${SOURCE_FILES})
  target_compile_definitions(asio PRIVATE ASIO_STANDALONE ASIO_SEPARATE_COMPILATION ASIO_HAS_CO_AWAIT)
  target_include_directories(asio PUBLIC "asio/asio/include" PUBLIC ${OPENSSL_INCLUDE_DIR})
  target_link_libraries(asio ${OPENSSL_LIBRARIES})

  # Module folder
  set_target_properties(asio PROPERTIES FOLDER thirdparty/asio)
  
  get_property(global_libs GLOBAL PROPERTY GLOBAL_LIBS_LIST)
  if(NOT global_libs)
    define_property(GLOBAL PROPERTY GLOBAL_LIBS_LIST
        BRIEF_DOCS "Global list of libs"
        FULL_DOCS "Global list of libs")
    set_property(GLOBAL PROPERTY GLOBAL_LIBS_LIST "")
  endif()
  set_property(GLOBAL APPEND PROPERTY GLOBAL_LIBS_LIST asio)

endif()
