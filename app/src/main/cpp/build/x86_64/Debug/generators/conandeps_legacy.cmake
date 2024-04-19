message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(glm)
find_package(stb)
find_package(magic_enum)

set(CONANDEPS_LEGACY  glm::glm  stb::stb  magic_enum::magic_enum )