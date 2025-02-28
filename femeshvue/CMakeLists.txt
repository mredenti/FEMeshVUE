add_library(core)
target_sources(core
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
        mesh.cpp)

add_executable(main.x main.cpp)
target_link_libraries(main.x PRIVATE core)