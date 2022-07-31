cmake_minimum_required(VERSION 3.20)
project(opengl-sample)

set(CMAKE_CXX_STANDARD 14)
find_package(Threads REQUIRED)

include_directories(
        #F:\\home\\lib\\glut\\include
        F:\\home\\lib\\glew-2.1.0\\include
        F:\\home\\lib\\glfw-3.3.5\\include
)

file(GLOB scripts
        src/*.cpp
        src/*.h
        )

add_executable(${PROJECT_NAME} ${scripts})

file(GLOB shader src/shader/*.shader)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${shader} $<TARGET_FILE_DIR:${PROJECT_NAME}>)


target_link_libraries(${PROJECT_NAME}
        Threads::Threads
        opengl32.lib
        F:\\home\\lib\\glew-2.1.0\\lib\\Release\\x64\\glew32.lib
        F:\\home\\lib\\glew-2.1.0\\lib\\Release\\x64\\glew32s.lib
        F:\\home\\lib\\glfw-3.3.5\\lib-vc2022\\glfw3.lib
        )