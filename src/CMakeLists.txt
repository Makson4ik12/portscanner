add_executable(scanner main.cpp)
  
add_subdirectory(portscanner)
add_subdirectory(tools)

target_link_libraries(scanner
  PRIVATE
    tools
    portscanner
  )