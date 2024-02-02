cmake_minimum_required(VERSION 3.0)
project(Scheduler)

# Add the executable
add_executable(scheduler main.c tasks.c scheduler.c merge.c)

# Include the directory containing header files
target_include_directories(scheduler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally, set C standard (e.g., C99)
set(CMAKE_C_STANDARD 99)
