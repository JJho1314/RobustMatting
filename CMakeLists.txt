cmake_minimum_required(VERSION 2.9)

project(RobustMatting)

# Add OpenCV:
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS}
${PROJECT_SOURCE_DIR}
${PROJECT_SOURCE_DIR}/libs/eigen-3.3.3
)

link_directories(${OpenCV_LIBRARY_DIRS}
${PROJECT_SOURCE_DIR}/libs/eigen-3.3.3
)

add_definitions(${OpenCV_DEFINITIONS})

project(RobustMatting)

include_directories(./libs/eigen-3.3.3/)

#add_subdirectory(./libs/utils/)
#add_subdirectory(./src/generalar/)

file(GLOB ROBUSTMATTING_SRC
	./src/robust_matting/*.h
	./src/robust_matting/*.cpp
)
add_executable(RobustMatting ${ROBUSTMATTING_SRC})


target_link_libraries(RobustMatting  
	${OpenCV_LIBS}
)

