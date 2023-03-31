#include <SFML/Graphics.hpp>
#include <iostream>
class Widget{
    public:
        virtual bool render(bool clicked,sf::RenderWindow &window){};
};