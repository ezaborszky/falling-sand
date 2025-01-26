add_executable(example_exe main.cpp game.cpp EntityManager.cpp Entity.cpp Systems.cpp Components.cpp)
target_link_libraries(example_exe PRIVATE sfml-graphics)
