add_library(tools "")

target_sources(tools
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/tools.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tools.hpp
  )

target_include_directories(tools PUBLIC ${CMAKE_CURRENT_LIST_DIR})