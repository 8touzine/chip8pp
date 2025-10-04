# CMakeList.txt : CMake project for chip8pp, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (chip8pp "chip8pp.cpp" "chip8pp.h" "Core/App.h" "Core/App.cpp" "Core/Core.h" "Core/Core.cpp" "Memory/Memory.h" "Memory/Memory.cpp" "Core/OpcodeProcessor.h" "Core/OpcodeProcessor.cpp" "Controls/Keyboard.h"  "Display/IDisplayBridge.h" "Display/Window.h" "Display/Window.cpp" "Memory/Fontset.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET chip8pp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
#Include and link SDL2
target_include_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2/include)

target_link_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2/lib/x64)


add_custom_command(TARGET chip8pp POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
"${CMAKE_SOURCE_DIR}/libs/SDL2/lib/x64/SDL2.dll"
$<TARGET_FILE_DIR:chip8pp>)


#include and link SDL2_Image
target_include_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2_Image/include)

target_link_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2_Image/lib/x64)


add_custom_command(TARGET chip8pp POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
"${CMAKE_SOURCE_DIR}/libs/SDL2_Image/lib/x64/SDL2_image.dll"
$<TARGET_FILE_DIR:chip8pp>)
###########################

#include and link SDL2_Mixer
target_include_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2_mixer/include)

target_link_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2_mixer/lib/x64)

add_custom_command(TARGET chip8pp POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
"${CMAKE_SOURCE_DIR}/libs/SDL2_mixer/lib/x64/SDL2_mixer.dll"
$<TARGET_FILE_DIR:chip8pp>)
#############################

#include and link SDL2_ttf
target_include_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2_ttf/include)

target_link_directories(chip8pp PRIVATE
${CMAKE_SOURCE_DIR}/libs/SDL2_ttf/lib/x64)

add_custom_command(TARGET chip8pp POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_if_different
"${CMAKE_SOURCE_DIR}/libs/SDL2_ttf/lib/x64/SDL2_ttf.dll"
$<TARGET_FILE_DIR:chip8pp>)
#############################

##copy
add_custom_command(TARGET chip8pp POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
"${CMAKE_SOURCE_DIR}/chip8pp/rom"
$<TARGET_FILE_DIR:chip8pp>/rom)

target_link_libraries(chip8pp PRIVATE
SDL2.lib SDL2main.lib SDL2_image.lib SDL2_mixer.lib SDL2_ttf.lib)