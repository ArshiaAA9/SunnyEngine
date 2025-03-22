# source all the cpp files in engine # source all the cpp files in engine # source all the cpp files in engine 
file(GLOB ENGINE_SOURCES src/*.cpp)

#make the library 
add_library(engine STATIC ${ENGINE_SOURCES})

# header files
target_include_directories(engine PUBLIC src/headers)
