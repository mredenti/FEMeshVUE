add_library(mesh)
target_sources(mesh
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
        mesh.cpp)