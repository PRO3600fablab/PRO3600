#pragma once 

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


#include <iostream>

class Widget{
    public:
        virtual void render(sf::RenderWindow &window, bool clicked)=0;
};
