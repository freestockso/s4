if(NOT TARGET asio)
  # add_subdirectory("asio")
  # set_target_properties(YY_cpp_common PROPERTIES FOLDER modules/asio)

  # Module library
  file(GLOB SOURCE_FILES "asio/asio/src/*.cpp")

  add_library(asio ${SOURCE_FILES})
  target_compile_definitions(asio PRIVATE ASIO_STANDALONE ASIO_SEPARATE_COMPILATION ASIO_HAS_CO_AWAIT)
  target_include_directories(asio PUBLIC "asio/asio/include" PUBLIC ${OPENSSL_INCLUDE_DIR})
  target_link_libraries(asio ${OPENSSL_LIBRARIES})

  # Module folder
  set_target_properties(asio PROPERTIES FOLDER thirdparty/asio)

endif()
