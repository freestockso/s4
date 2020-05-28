add_subdirectory(json)

include_directories(
  json/include
)
# Module folder
set_target_properties(json PROPERTIES FOLDER thirdparty/json)
