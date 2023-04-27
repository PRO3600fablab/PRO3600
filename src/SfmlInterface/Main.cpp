#include <SFML/Graphics.hpp>
#include <iostream>
#include "./headers/Scene.h"
#include "./headers/TextScene.h"
#include "./headers/Button.h"
#include "./headers/ButtonSwitch.h"
#include "./headers/InputBox.h"
#include "VectorMaths.cpp"
using namespace std;

int main()
{
    
    // declaration des variables pour le modele
    // nombre de point
    int nbNode = 0;
    //liste des points
    vector<vector<float>> nodeList;
    // matrice d adjacence 
    vector<vector<bool>> adjaMat;
    // matrice des caracterisqtiques des adjacences
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
    
    //collection of scene and textual scene
    vector<Scene> sceneList; //is the list of the different scenes that can be render
    vector<TextScene> textSceneList;
    //a scene is a collection of widgets or collection of texts

    //widgets for scene one :
    Scene scene1 = Scene();

    //creating button
    bool addNodeValue= false;
    bool * addNodeValuePtr= &addNodeValue; 
    Button addNodeButton(14,sf::Color::White,false,10,200,80,40,"Add Node",addNodeValuePtr);
    addNodeButton.setFont(arialFont);
    
    bool nextButtonValue = false;
    bool * nextButtonValuePtr = & nextButtonValue;
    Button nextButton(14,sf::Color::White,false,10,550,80,40,"Next Step", nextButtonValuePtr );
    nextButton.setFont(arialFont);

    //Buttons for selecting
    bool dogXValue = false;
    bool dogYValue = false;
    bool * dogXValuePtr = & dogXValue;
    bool * dogYValuePtr = & dogYValue; 
    ButtonSwitch dogButtonX(14,sf::Color::White,false,400,120,80,40,"Static","Not static",dogXValuePtr);
    dogButtonX.setFont(arialFont);
    ButtonSwitch dogButtonY(14,sf::Color::White,false,500,120,80,40,"Static","Not static",dogYValuePtr);
    dogButtonY.setFont(arialFont);

    // Coordinate of graphe node selection
    float XlocValue = 0;
    float YlocValue = 0;
    float * XlocValuePtr = &XlocValue;
    float * YlocValuePtr = &YlocValue;
    InputBox InputX(sf::Color::White,10,130, 80, 30, arialFont,XlocValuePtr);
    InputBox InputY(sf::Color::White,140,130, 80, 30, arialFont,YlocValuePtr);
    vector<float> nodeCoord;
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
    
    TextScene textScene1= TextScene();
    textScene1.addText(&nodes );
    textScene1.addText( &titleTxt );
    textScene1.addText( &xyCoordTxt );
    textScene1.addText( &dogTxt );
    
    string nodesLtext ; 


    sceneList.push_back(scene1);
    textSceneList.push_back(textScene1);

    //scene 2
    Scene scene2 = Scene();

    bool addLinkValue=false;
    bool * addLinkValuePtr = & addLinkValue;
    Button addLinkButton(14,sf::Color::White,false,10,420,80,40,"Add Link", addLinkValuePtr );
    addLinkButton.setFont(arialFont);

    bool removeLinkValue=false;
    bool * removeLinkValuePtr = &removeLinkValue;
    Button removeLinkButton(14,sf::Color::White,false,110,420,80,40,"Remove Link", removeLinkValuePtr );
    removeLinkButton.setFont(arialFont);

    float firstNodeValue=0;
    float * firstNodeValuePtr=&firstNodeValue;
    float secondNodeValue=0;
    float * secondNodeValuePtr=&secondNodeValue;
    InputBox firstNode (sf::Color::White,10,130, 80, 30, arialFont,firstNodeValuePtr);
    InputBox secondNode(sf::Color::White,140,130, 80, 30, arialFont,secondNodeValuePtr);

    bool renderCalculsValueBool = false;
    bool * renderCalculsValueBoolPtr=&renderCalculsValueBool;
    Button renderCalculsValue(14,sf::Color::White,false,10,550,80,40,"Next Step", renderCalculsValueBoolPtr );
    renderCalculsValue.setFont(arialFont);

    float firstLinkParametreValue=0;
    float secondLinkParametreValue=0;
    float * firstLinkParametreValuePtr=&firstLinkParametreValue;
    float * secondLinkParametreValuePtr=&secondLinkParametreValue;
    InputBox firstParameterInput(sf::Color::White,10,130, 80, 30, arialFont,firstLinkParametreValuePtr);
    InputBox secondParameterInput(sf::Color::White,140,130, 80, 30, arialFont,secondLinkParametreValuePtr);

    scene2.addWidget(&addLinkButton);
    scene2.addWidget(&removeLinkButton);
    scene2.addWidget(&firstNode);
    scene2.addWidget(&secondNode);
    scene2.addWidget(&renderCalculsValue);
    scene2.addWidget(&firstParameterInput);
    scene2.addWidget(&secondParameterInput);

    // textlist for scene 2

    sf::Text node1et2("Node 1 and 2 index:",arialFont,20);//node array
    node1et2.setPosition(sf::Vector2f(20,60));
    node1et2.setColor(sf::Color(255,255,255));

    sf::Text addLinkText("Add a new link",arialFont,40);//title of the first scene
    addLinkText.setPosition(sf::Vector2f(10,10));
    addLinkText.setColor(sf::Color(255,255,255));

    sf::Text aAndBValue("a & b :",arialFont,20);
    aAndBValue.setPosition(sf::Vector2f(20,180));
    aAndBValue.setColor(sf::Color(255,255,255));

    sf::Text profilSelection("Choose the profile section :",arialFont,20);
    profilSelection.setPosition(sf::Vector2f(20,360));
    profilSelection.setColor(sf::Color(255,255,255));

    TextScene textScene2=TextScene();
    textScene2.addText( &node1et2 );
    textScene2.addText( &addLinkText );//title
    textScene2.addText( &aAndBValue );
    textScene2.addText( &profilSelection );

    sceneList.push_back(scene2);
    textSceneList.push_back(textScene2);

    

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

        //rendering the proper scene
        sceneList[mode].render(window,mouseClick);
        textSceneList[mode].render(window);
        
        
        nodeCoord[0] = XlocValue;
        nodeCoord[1] = YlocValue;

        if(nextButtonValue){
            mode=1;
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
