
add_library(guilib 
        Button.cpp
        ButtonSwitch.cpp
        InputBox.cpp
        Scene.cpp
        Widget.cpp
        )

add_subdirectory(headers)

target_link_libraries(guilib sfml-graphics OpenGL)
target_link_libraries(guilib sfml-graphics OpenGL ${ALL_LIBS} )

add_executable(sfml-app Main.cpp)

target_link_libraries(sfml-app guilib)
target_link_libraries(sfml-app sfml-graphics OpenGL)
target_link_libraries(sfml-app sfml-graphics OpenGL ${ALL_LIBS} )

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET sfml-app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:sfml-app> $<TARGET_FILE_DIR:sfml-app> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS sfml-app)
