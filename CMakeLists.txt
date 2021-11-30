cmake_minimum_required (VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)

# Below line is for using C++14 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Our project name
project (framework)

# include_directories(src)
# link_directories(src)

add_executable(framework main.cpp src/board.cpp src/player.cpp src/spritesheet.cpp src/tile.cpp
src/utils.cpp src/tt.cpp src/mapgen.cpp src/gamemenu.cpp src/weather.cpp src/daycycle.cpp
src/actor.cpp src/actors.cpp)
# add_subdirectory(framework src)

# For finding our SDL2 package!
INCLUDE(FindPkgConfig)

# Searching SDL2 package.
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

# Including our external library's directory for header files!
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} include)

# Linking SDL2 library with our project.
target_link_libraries(framework ${SDL2_LIBRARIES} SDL2_image)