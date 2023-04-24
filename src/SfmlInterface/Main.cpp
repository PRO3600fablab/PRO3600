#include <SFML/Graphics.hpp>
#include <iostream>
#include "ScrollBar.cpp"
#include "VectorMaths.cpp"
#include "./headers/Scene.h"
#include "headers/ButtonSwitch.h"
#include <ButtonSwitch.h>
using namespace std;

int main()
{
    
    // declaration des variables pour le modèle
    // nombre de point
    int nbNode = 0;
    //liste des points
    vector<vector<float>> nodeList;
    // matrice d adjacence 
    vector<vector<bool>> adjaMat;
    // matrice des caractérisqtiques des adjacences
    // each link is caracterised by [i,a,b,L,teta,E]
    // i=0 for rectangle,1 for circle; a and b are dimensions; L is length beetwen nodes; teta is the angle between the two nodes;
    // and E is the young module
    vector<vector<float[6]>> linkSpec;
    
    
    //mode choice
    int mode = 0;
    //making window
    sf::RenderWindow window(sf::VideoMode(800, 600), "PRO3600");
    window.setFramerateLimit(60);
    //loading font
    sf::Font arialFont;

    if (!arialFont.loadFromFile("./srcFont/arial.ttf"))
    {
        std::cout<<"impossible de charger la font";
    };

    //widgets for scene one :
    Scene scene1 = Scene();

    //creating button
    bool * addNodeValue; 
    Button addNodeButton(14,sf::Color::White,false,10,200,80,40,"Add Node",addNodeValue);
    addNodeButton.setFont(arialFont);
    bool * nextButtonValue;
    Button nextButton(14,sf::Color::White,false,10,550,80,40,"Next Step", nextButtonValue );
    nextButton.setFont(arialFont);

    //Buttons for selecting
    bool * dogXValue;
    bool * dogYValue; 
    ButtonSwitch dogButtonX(14,sf::Color::White,false,400,120,80,40,"Static","Not static",dogXValue);
    dogButtonX.setFont(arialFont);
    ButtonSwitch dogButtonY(14,sf::Color::White,false,500,120,80,40,"Static","Not static",dogYValue);
    dogButtonY.setFont(arialFont);

    // Coordinate of graphe node selection
    float * XlocValue;
    float * YlocValue;
    InputBox InputX(sf::Color::White,10,130, 80, 30, arialFont,XlocValue);
    InputBox InputY(sf::Color::White,140,130, 80, 30, arialFont,YlocValue);
    vector<int> nodeCoord;
    nodeCoord.resize(2);

    scene1.addWidget(&addNodeButton);
    scene1.addWidget(&nextButton);
    scene1.addWidget(&dogButtonX);
    scene1.addWidget(&dogButtonY);
    scene1.addWidget(&InputX);
    scene1.addWidget(&InputY);



    //text for first page
    sf::Text nodes("",arialFont,20);//node array
    nodes.setPosition(sf::Vector2f(40,300));
    nodes.setColor(sf::Color(255,255,255));

    sf::Text titleTxt("Creating a new node",arialFont,40);//title of the first scene
    titleTxt.setPosition(sf::Vector2f(10,10));
    titleTxt.setColor(sf::Color(255,255,255));

    sf::Text xyCoordTxt("X and Y coordinates :",arialFont,20);
    xyCoordTxt.setPosition(sf::Vector2f(20,80));
    xyCoordTxt.setColor(sf::Color(255,255,255));

    sf::Text dogTxt("Rotation dog, X dog and Y dog",arialFont,20);
    dogTxt.setPosition(sf::Vector2f(300,80));
    dogTxt.setColor(sf::Color(255,255,255));

    

    //textlist for scene 1
    
    vector<sf::Text*> textList;
    textList.push_back( &nodes );
    textList.push_back( &titleTxt );
    textList.push_back( &xyCoordTxt );
    textList.push_back( &dogTxt );

    string nodesLtext ; 

    //scene 2
    //Scene scene2();


    

    //input
    bool mouseClick = false;

    
    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            mouseClick = (event.type == sf::Event::MouseButtonPressed);

        }
        mouseClick=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        window.clear(sf::Color(20,20,20));

        //rendering the scene
        scene1.render(window,mouseClick);
        for(int j = 0; j<textList.size();j++){
            window.draw(*textList[j]);
        };
        

        nodeCoord[0] =  *XlocValue;
        nodeCoord[1] = *YlocValue;

        if(nextButtonValue){
            mode+=1;
        }

        window.display();
        
        
        if(addNodeValue){
            std::cout<<" Adding the node\n";
            nbNode+=1;
            nodeList.resize(nbNode);
            nodeList[nbNode-1].resize(2);
            nodeList[nbNode-1][0]=nodeCoord[0];
            nodeList[nbNode-1][1]=nodeCoord[1];
        };
        
        
        nodesLtext = " Nodes \n"+displayVect(nodeList);
        nodes.setString(nodesLtext);
    }
    std::cout<<"Hello world";
    return 0;
}
