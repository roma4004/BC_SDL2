cmake_minimum_required(VERSION 3.19)
project(BC)

set(CMAKE_MODULE_PATH	${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/find_sdl2/")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread")

#find_package(SFML 2.5
#        COMPONENTS
#        graphics
#        audio
#        REQUIRED)

set(LIB_PATH            libraries)
set(SRC_PATH            sources)
set(INC_PATH            ${SRC_PATH}/include)

#find_package(			Threads				)#for windows
find_package(			SDL2		REQUIRED)
find_package(			SDL2_ttf	REQUIRED)
find_package(			SDL2_image	REQUIRED)
find_package(			SDL2_mixer	REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        )

include_directories(${INC_PATH}
        ${SDL2_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR}
        )

aux_source_directory(${SRC_PATH} SOURCE_FILES)
add_executable(BC ${SOURCE_FILES})

target_link_libraries(BC
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        )
