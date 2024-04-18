add_library(portscanner "")

target_sources(portscanner
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/portscanner.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/portscanner.hpp
  )

target_include_directories(portscanner PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(portscanner
  PRIVATE
    tools
  )