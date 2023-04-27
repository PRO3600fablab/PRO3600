#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
using namespace std;

class TextScene {
    public :

    void addText(sf::Text* text);
    void render(sf::RenderWindow &window);

    private :
    vector<sf::Text*> collection;
};