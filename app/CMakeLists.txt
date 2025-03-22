# Find all .cpp files in src/
file(GLOB APP_SOURCES src/*.cpp)

# Create an executable
add_executable(App ${APP_SOURCES})

# Include headers (for the App and linked libraries)
target_include_directories(App PUBLIC src/headers)

# Link the engine library

# ✅ Find and Link SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# ✅ Link SDL2 and SDL2_ttf to App
target_link_libraries(App INTERFACE engine ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
