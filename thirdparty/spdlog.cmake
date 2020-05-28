add_subdirectory(spdlog)

include_directories(
  spdlog/include
)
# Module folder
set_target_properties(spdlog PROPERTIES FOLDER thirdparty/spdlog)
