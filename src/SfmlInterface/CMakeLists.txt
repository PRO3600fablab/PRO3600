find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)


add_library(guilib 
        Button.cpp
        ButtonSwitch.cpp
        InputBox.cpp
        Scene.cpp
        Widget.cpp
        VectorMaths.cpp
        TextScene.cpp
        matElementaire.cpp
        )

add_subdirectory(headers)

target_link_libraries(guilib sfml-graphics)


add_executable(sfml-app Main.cpp)

target_link_libraries(sfml-app RDMLIB sfml-graphics guilib)

