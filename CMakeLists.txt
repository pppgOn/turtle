cmake_minimum_required(VERSION 3.25)
 
project(VIEWER
	VERSION 0.1.0
)
 
find_package(gf REQUIRED)
 
add_executable(turtle-viewer
	turtle-viewer.cc
	# and the rest of your sources
)
 
target_link_libraries(turtle-viewer
	PRIVATE
		gf::graphics
		gf::net
)