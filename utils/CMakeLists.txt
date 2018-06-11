INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
add_executable(pcd_viewer pcd_viewer.cpp)
target_link_libraries(pcd_viewer sgl  )

#aruco_create_board
INSTALL(TARGETS pcd_viewer RUNTIME DESTINATION bin)
