cmake_minimum_required(VERSION 3.13.4)
project(OpenGL)


add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/common.hpp
    src/window.hpp
    src/shader.hpp
    src/Texture.hpp
    src/ErrorHandeler.hpp
    libraries/stb_image/stb_image.cpp
    libraries/stb_image/stb_image.h
)

find_package(Git QUIET) 
if(GIT_FOUND AND EXISTS "${PROJEKT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE, "Check submodules  during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodual update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libraries/GLFW/CMakeLists.txt")
    message(FATAL_ERROR "The given submodles was not downloaded! GIT_SUBMODULE was turnd off or faild. You may need to clone the GLFW Github repostiory and replace the libraries/GLFW folder with it.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libraries/glm/CMakeLists.txt")
    message(FATAL_ERROR "The given submodles was not downloaded! GIT_SUBMODULE was turnd off or faild. You may need to clone the glm Github repostiory and replace the libraries/glm folder with it.")
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libraries/GLAD/CMakeLists.txt")
    message(FATAL_ERROR "The given submodles was not downloaded! GIT_SUBMODULE was turnd off or faild.")
endif()

add_subdirectory(libraries/GLFW)
add_subdirectory(libraries/glm)
add_subdirectory(libraries/GLAD)


target_include_directories(${PROJECT_NAME} 
    PUBLIC libraries/GLAD/include
)

target_link_libraries(${PROJECT_NAME} glad)

target_link_directories(${PROJECT_NAME}
    PRIVATE libraries/GLFW/src
)

target_link_libraries(${PROJECT_NAME} glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC libraries/glm/glm
)

target_link_libraries(${PROJECT_NAME} glm)