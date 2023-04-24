// a scene is a collection of widget pointers
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./headers/Scene.h"
using namespace std;

Scene::Scene(){};

void Scene::addWidget(Widget* wid){
    collection.push_back(wid);
};
void Scene::render(sf::RenderWindow &window,bool clicked){
    for( auto& i : collection){
        (*i).render(window,clicked);
    };
};



