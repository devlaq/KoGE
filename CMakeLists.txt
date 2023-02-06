cmake_minimum_required(VERSION 3.23)
project(KoRPG)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
link_directories(library)

add_executable(KoRPG src/main.cpp src/graphic/shader.cpp src/graphic/shader.h src/stb_image.cpp src/stb_image.h src/glad.c src/graphic/camera/camera.h src/graphic/camera/perspectiveCamera.h src/graphic/camera/cameraController.cpp src/graphic/camera/cameraController.h src/time.cpp src/time.h src/ui/font/fonts.h src/ui/font/fonts.cpp src/ui/font/font.cpp src/ui/font/font.h src/ui/font/glyph.cpp src/ui/font/glyph.h src/graphic/graphics.cpp src/graphic/graphics.h src/util/resources.cpp src/util/resources.h src/graphic/texture.cpp src/graphic/texture.h)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)

#add_custom_command(TARGET KoRPG POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory resources ${CMAKE_CURRENT_BINARY_DIR}/Debug)

message(STATUS ${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent)

FetchContent_Declare(
        freetype
        GIT_REPOSITORY https://github.com/freetype/freetype.git
        GIT_TAG VER-2-12-1
)

FetchContent_MakeAvailable(freetype)
target_link_libraries(KoRPG libglfw3.a freetype libharfbuzz.a libharfbuzz-subset.a libz.so libbz2.a libgzip.a libpng.a libbrotlidec.so libwoff2common.so libwoff2dec.so libspdlog.a libfmt.a X11)