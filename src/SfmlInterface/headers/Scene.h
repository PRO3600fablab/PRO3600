#include <SFML/Graphics.hpp>
#include <iostream>
#include "ButtonSwitch.h"
#include "Button.h"
#include "InputBox.h"

class Scene{
    public:
    Scene();

    void addWidget(Widget* wid);

    void render(sf::RenderWindow &window,bool clicked);


    private:
    vector<Widget*> collection;
};
