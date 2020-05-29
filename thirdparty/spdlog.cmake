# add_subdirectory(spdlog)

# include_directories(SYSTEM 
#   spdlog/include
# )
# Module folder
# set_target_properties(spdlog PROPERTIES FOLDER thirdparty/spdlog)

set_property(GLOBAL APPEND PROPERTY GLOBAL_INCLUDE_LIST ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/include)