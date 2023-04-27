#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "./headers/TextScene.h"


#include <iostream>


void TextScene::addText(sf::Text* text){
    collection.push_back(text);
};

void TextScene::render(sf::RenderWindow &window){
    for(auto& i : collection){
        window.draw(*i);
    };
};
