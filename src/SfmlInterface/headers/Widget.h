#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>

class Widget{
    public:
        virtual void render(sf::RenderWindow &window, bool clicked){};
};
