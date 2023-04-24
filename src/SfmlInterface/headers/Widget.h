#include <SFML/Graphics.hpp>
#include <iostream>

class Widget{
    public:
        virtual void render(sf::RenderWindow &window, bool clicked);
};