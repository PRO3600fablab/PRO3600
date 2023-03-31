#include <SFML/Graphics.hpp>
#include <iostream>
#include "Button.cpp"
#include "ScrollBar.cpp"
#include "InputBox.cpp"
#include "VectorMaths.cpp"
#include "ButtonSwitch.cpp"
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

    if (!arialFont.loadFromFile("./src/arial.ttf"))
    {
        std::cout<<"impossible de charger la font";
    };


    //creating button
    Button addNodeButton(14,sf::Color::White,false,10,200,80,40,"Add Node");
    addNodeButton.setFont(arialFont);
    Button nextButton(14,sf::Color::White,false,10,550,80,40,"Next Step");
    nextButton.setFont(arialFont);

    //Buttons for selecting 
    ButtonSwitch dogButtonRot(14,sf::Color::White,false,300,120,80,40,"Static","Not static");
    dogButtonRot.setFont(arialFont);
    ButtonSwitch dogButtonX(14,sf::Color::White,false,400,120,80,40,"Static","Not static");
    dogButtonX.setFont(arialFont);
    ButtonSwitch dogButtonY(14,sf::Color::White,false,500,120,80,40,"Static","Not static");
    dogButtonY.setFont(arialFont);

    // Coordinate of graphe node selection
    InputBox InputX(sf::Color::White,10,130, 80, 30, arialFont);
    InputBox InputY(sf::Color::White,140,130, 80, 30, arialFont);
    vector<int> nodeCoord;
    nodeCoord.resize(2);



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
    
    vector<sf::Text*> textList;
    textList.push_back( &nodes );
    textList.push_back( &titleTxt );
    textList.push_back( &xyCoordTxt );
    textList.push_back( &dogTxt );

    string nodesLtext ; 
    //


    

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

        bool pressedAddButton = addNodeButton.render(mouseClick,window);
        //bool pressed2 = testButton2.render(mouseClick,window);
        //testBar.render(mouseClick,window);

        nodeCoord[0] = InputX.render(mouseClick,window);
        nodeCoord[1] = InputY.render(mouseClick,window);
        dogButtonRot.render(mouseClick,window);
        dogButtonX.render(mouseClick,window);
        dogButtonY.render(mouseClick,window);

        for(int j = 0; j<textList.size();j++){
            window.draw(*textList[j]);
        };

        if(nextButton.render(mouseClick,window)){
            mode+=1;
        }

        window.display();
        
        
        if(pressedAddButton){
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