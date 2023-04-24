#pragma once 

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


#include <iostream>
#include "ButtonSwitch.h"
#include "Button.h"
#include "InputBox.h"

using namespace std ;



class Scene{
    public:
    Scene();

    void addWidget(Widget* wid);

    void render(sf::RenderWindow &window,bool clicked);


    private:
	vector <Widget*> collection;
};
