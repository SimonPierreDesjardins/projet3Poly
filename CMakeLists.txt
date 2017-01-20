cmake_minimum_required(VERSION 3.5.0)
project(log3900-03)

# Use C++11 with visual studio warnings level 4
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 /W4")

# Enable folder creation to organize projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SUPPRESS_REGENERATION true)

# Move generated libraries to /lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/lib")

# Move generated .exe and .dll to /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin")

# Adds heavy-client as a visual studio project
add_subdirectory(src/client/heavy)
