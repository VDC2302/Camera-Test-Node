cmake_minimum_required(VERSION 3.15)
project(CameraTestNode CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CameraTestNode
	src/main.cpp
	src/LogParser.cpp
 "include/LogParser.h" "include/ImageAnalyzer.h" "src/ImageAnalyzer.cpp" "include/VcmAlgorithm.h" "src/VcmAlgorithm.cpp")

target_include_directories(CameraTestNode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/data/test_log.csv"
	"${CMAKE_CURRENT_BINARY_DIR}/test_log.csv"
	COPYONLY
)