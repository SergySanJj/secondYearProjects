file(GLOB Sources "*.cpp")
add_executable(Grid2D ${Sources})
target_link_libraries(Grid2D src)
