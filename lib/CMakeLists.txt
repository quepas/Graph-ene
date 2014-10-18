file (GLOB SOURCE_FILE_LIST src/*.cpp)
file (GLOB HEADER_FILE_LIST include/*.h)

add_library (Graphene_lib STATIC ${SOURCE_FILE_LIST} ${HEADER_FILE_LIST})
target_include_directories(Graphene_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
