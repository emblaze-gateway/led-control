cmake_minimum_required(VERSION 3.22)
project(led_control C)

set(BINDDIR "/usr/local/bin")

add_executable(${PROJECT_NAME} main.c)

install(TARGETS ${PROJECT_NAME} DESTINATION ${BINDDIR})
