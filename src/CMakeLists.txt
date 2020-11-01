# setup:
cmake_minimum_required(VERSION 3.8.2)

# macros:
macro(setup_properties)
    target_compile_features(
            ${ARGV0}
            PUBLIC cxx_std_20
    )
    set_target_properties(
            ${ARGV0}
            PROPERTIES
            CXX_EXTENSIONS OFF
    )
endmacro()
macro(setup_libraries)
    target_link_libraries(
            ${ARGV0}
            PUBLIC Vulkan::Vulkan
    )
    target_link_libraries(
            ${ARGV0}
            PUBLIC SDL2::SDL2 
    )
endmacro()

# executables and target properties:
add_executable(
        hypnitro-imgui
        interface/sdl2.cpp
        interface/imgui_draw.cpp
        interface/imgui_impl_vulkan.cpp
        interface/imgui_impl_sdl.cpp
        interface/imgui_widgets.cpp
        interface/imgui.cpp
)
add_executable(
        hypnitro-cli
        interface/cli.cpp
)
setup_properties(hypnitro-imgui)
setup_properties(hypnitro-cli)

# dependencies:
find_package(Vulkan REQUIRED)
find_package(SDL2 REQUIRED)
setup_libraries(hypnitro-imgui)
setup_libraries(hypnitro-cli)

install(
        TARGETS hypnitro-imgui hypnitro-cli
        RUNTIME
        DESTINATION bin
)
