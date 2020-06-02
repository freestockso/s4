add_subdirectory(SQLiteCpp)

include_directories(
  SQLiteCpp/include
)
# Module folder
set_target_properties(SQLiteCpp PROPERTIES FOLDER thirdparty/SQLiteCpp)

set_property(GLOBAL APPEND PROPERTY GLOBAL_LIBS_LIST SQLiteCpp)
set_property(GLOBAL APPEND PROPERTY GLOBAL_INCLUDE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/SQLiteCpp/include)
