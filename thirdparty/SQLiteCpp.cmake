if(NOT TARGET YY_cpp_common)
  add_subdirectory(SQLiteCpp)

  include_directories(
    SQLiteCpp/include
  )
  # Module folder
  set_target_properties(SQLiteCpp PROPERTIES FOLDER thirdparty/SQLiteCpp)
endif()
