#include <SFML/Graphics.hpp>
#include <iostream>
#include "./headers/Scene.h"
#include "./headers/TextScene.h"
#include "./headers/Button.h"
#include "./headers/ButtonSwitch.h"
#include "./headers/InputBox.h"
#include "VectorMaths.cpp"
#include <cmath>
#include "./../RDM/headers/assemblage.h"
using namespace std;

int main()
{
    
    // declaration des variables pour le modele
    // nombre de point
    int nbNode = 0;
    //liste des points
    vector<vector<float>> nodeList;
    vector<bool> nodeDOF;
    vector<float> nodeForce; // x and y coordinates
    // matrice d adjacence 
    vector<vector<bool>> adjaMat;
    // matrice des caracterisqtiques des adjacences
    // each link is caracterised by [i,a,b,L,teta,E]
    // i=0 for rectangle,1 for circle; a and b are dimensions; L is length beetwen nodes; teta is the angle between the two nodes;
    // and E is the young module
    vector<vector<vector<float>>> linkSpec;

    //result of matElementaire
    vector<vector<vector<vector<float>>>> resultMatElem;
    vector<float> assemblageMatrix;
    vector<vector<float>> graphForOpenscad;//x and y start x and y stop type inside diametre outside diametre
    
    
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
    Button addNodeButton(14,sf::Color::White,false,10,240,80,40,"Add Node",addNodeValuePtr);
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
    ButtonSwitch dogButtonX(14,sf::Color::White,false,320,120,80,40,"Static","Not static",dogXValuePtr);
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

    // Force 
    float xForceValue = 0;
    float yForceValue = 0;
    float * xForceValuePtr = &xForceValue;
    float * yForceValuePtr = &yForceValue;
    InputBox InputForceX(sf::Color::White,10,200, 80, 30, arialFont,xForceValuePtr);
    InputBox InputForceY(sf::Color::White,140,200, 80, 30, arialFont,yForceValuePtr);

    
    scene1.addWidget(&addNodeButton);
    scene1.addWidget(&nextButton);
    scene1.addWidget(&dogButtonX);
    scene1.addWidget(&dogButtonY);
    scene1.addWidget(&InputX);
    scene1.addWidget(&InputY);
    scene1.addWidget(&InputForceX);
    scene1.addWidget(&InputForceY);


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

    sf::Text xyForceTxt("X and Y force component :",arialFont,20);
    xyForceTxt.setPosition(sf::Vector2f(20,170));
    xyForceTxt.setColor(sf::Color(255,255,255));

    sf::Text dogTxt("Degree of liberty in X axis and Y axis",arialFont,20);
    dogTxt.setPosition(sf::Vector2f(300,80));
    dogTxt.setColor(sf::Color(255,255,255));

    

    //textlist for scene 1
    
    TextScene textScene1= TextScene();
    textScene1.addText(&nodes );
    textScene1.addText( &titleTxt );
    textScene1.addText( &xyCoordTxt );
    textScene1.addText( &dogTxt );
    textScene1.addText(&xyForceTxt);
    
    string nodesLtext ; 


    sceneList.push_back(scene1);
    textSceneList.push_back(textScene1);

    //image list for scene 1
    //vector<sf::Texture> imageSceneList1;
    sf::Texture xAxisDOLTexture; 
    sf::Sprite xAxisDOLSprite; 
    if (!xAxisDOLTexture.loadFromFile("./srcImage/XAxisDOL.png")){
        return -1;
    };
    xAxisDOLSprite.setTexture(xAxisDOLTexture);
    xAxisDOLSprite.setScale(0.5,0.5);
    xAxisDOLSprite.setPosition(300,160);

    sf::Texture yAxisDOLTexture; 
    sf::Sprite yAxisDOLSprite; 
    if (!yAxisDOLTexture.loadFromFile("./srcImage/YAxisDOL.png")){
        return -1;
    };
    yAxisDOLSprite.setTexture(yAxisDOLTexture);
    yAxisDOLSprite.setScale(0.5,0.5);
    yAxisDOLSprite.setPosition(500,160);


    //
    //
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
    InputBox firstParameterInput(sf::Color::White,10,260, 80, 30, arialFont,firstLinkParametreValuePtr);
    InputBox secondParameterInput(sf::Color::White,140,260, 80, 30, arialFont,secondLinkParametreValuePtr);
    firstParameterInput.changeInterval(0,32767);
    secondParameterInput.changeInterval(0,32767);


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

    sf::Text linkMatrixText("",arialFont,20);
    linkMatrixText.setPosition(sf::Vector2f(400,360));
    linkMatrixText.setColor(sf::Color(255,255,255));

    TextScene textScene2=TextScene();
    textScene2.addText( &node1et2 );
    textScene2.addText( &addLinkText );//title
    textScene2.addText( &aAndBValue );
    textScene2.addText( &profilSelection );
    textScene2.addText( &linkMatrixText);
    string linkMatrixString;

    sceneList.push_back(scene2);
    textSceneList.push_back(textScene2);

    //image list for scene 2
    //vector<sf::Texture> imageSceneList2;
    sf::Texture roundSectionTexture; 
    sf::Sprite roundSectionSprite; 
    if (!roundSectionTexture.loadFromFile("./srcImage/RoundSection.png")){
        return -1;
    };
    roundSectionSprite.setTexture(roundSectionTexture);
    roundSectionSprite.setScale(0.5,0.5);
    roundSectionSprite.setPosition(300,160);

    sf::Texture squareSectionTexture; 
    sf::Sprite squareSectionSprite; 
    if (!squareSectionTexture.loadFromFile("./srcImage/SquareSection.png")){
        return -1;
    };
    squareSectionSprite.setTexture(squareSectionTexture);
    squareSectionSprite.setScale(0.5,0.5);
    squareSectionSprite.setPosition(500,160);

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
        window.clear(sf::Color(140,140,140));

        //rendering the proper scene
        sceneList[mode].render(window,mouseClick);
        textSceneList[mode].render(window);
        if(mode==0){
            window.draw(xAxisDOLSprite);
            window.draw(yAxisDOLSprite);
        };
        if(mode==1){
            window.draw(roundSectionSprite);
            window.draw(squareSectionSprite);
        };

        nodeCoord[0] = XlocValue;
        nodeCoord[1] = YlocValue;

        if(nextButtonValue){
            mode=1;
            firstNode.changeInterval(1,nbNode);
            secondNode.changeInterval(1,nbNode);
            adjaMat.resize(nbNode);
            linkSpec.resize(nbNode);
            for(int j = 0; j<nbNode; j++){
                adjaMat[j].resize(nbNode);
                linkSpec[j].resize(nbNode);
                for(int k = 0; k<nbNode;k++){
                    linkSpec[j][k].resize(6);
                };
            };
        }
        
        window.display();
        
        
        if(addNodeValue){
            std::cout<<" Adding the node\n";
            nbNode+=1;
            // adding all the info of the node to the matrix
            //adjacence matrix
            nodeList.resize(nbNode);
            nodeList[nbNode-1].resize(2);
            nodeList[nbNode-1][0]=nodeCoord[0];
            nodeList[nbNode-1][1]=nodeCoord[1];

            //degre of freedom vector
            nodeDOF.resize(2*nbNode);
            nodeDOF[2*nbNode-2]=dogXValue;
            nodeDOF[2*nbNode-1]=dogYValue;

            //adding the force
            nodeForce.resize(2*nbNode);
            nodeForce[2*nbNode-2]=xForceValue;
            nodeForce[2*nbNode-1]=yForceValue;

        };

        if(addLinkValue){
            adjaMat[(int)firstNodeValue - 1][(int)secondNodeValue - 1] = true;
            adjaMat[(int)secondNodeValue - 1][(int)firstNodeValue - 1] = true;
            /* basic values
            for(int j=0;j<6;j++){
                linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][j]=1;
                linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][j]=1;
            }
            linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][2]=0.5;
            linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][2]=0.5;
            */
            // i a b L teta E
            linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][0]=1;
            linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][0]=1;
            linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][1]=firstLinkParametreValue;
            linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][1]=firstLinkParametreValue;
            linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][2]=secondLinkParametreValue;
            linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][2]=secondLinkParametreValue;
            // calculing distance
            float xcompo = pow((nodeList[(int)secondNodeValue - 1][0]-nodeList[(int)firstNodeValue - 1][0]),2);
            float ycompo = pow((nodeList[(int)secondNodeValue - 1][1]-nodeList[(int)firstNodeValue - 1][1]),2);
            float distance = sqrt(xcompo+ycompo);
            linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][3]=distance;
            linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][3]=distance;
            // calculing teta
            float dotProduct = nodeList[(int)secondNodeValue - 1][0]-nodeList[(int)firstNodeValue - 1][0];
            float cosangle = dotProduct/distance;
            float angleBeam = acos(cosangle);
            linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][4]=angleBeam;
            linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][4]=angleBeam;
            linkSpec[(int)firstNodeValue - 1][(int)secondNodeValue - 1][5]=210000;
            linkSpec[(int)secondNodeValue - 1][(int)firstNodeValue - 1][5]=210000;
        }
        if(removeLinkValue){
            adjaMat[(int)firstNodeValue - 1][(int)secondNodeValue - 1] = false;
            adjaMat[(int)secondNodeValue - 1][(int)firstNodeValue - 1] = false;
        }
        
        
        nodesLtext = " Nodes \n"+displayVect(nodeList);
        nodes.setString(nodesLtext);
        linkMatrixString = " Link matrix \n"+displayVect(adjaMat);
        linkMatrixText.setString(linkMatrixString);

        if(renderCalculsValueBool){
            assemblageMatrix=assemblage(linkSpec, adjaMat,nodeDOF,nodeForce);
            for(int i = 0; i<assemblageMatrix.size();i++){
                std::cout<<std::to_string(assemblageMatrix[i]);
                std::cout<<std::to_string(assemblageMatrix[i]);
                std::cout<<"\n";
            }

            //creating the vector 
            int nbLiaison = 0;
            for(int k1; k1<nbNode;k1++){
                for(int k2;k2<k1;k2++){
                    if(adjaMat[k1][k2]){
                        nbLiaison++;
                        graphForOpenscad.resize(nbLiaison);
                        graphForOpenscad[nbLiaison-1].resize(7);
                        graphForOpenscad[nbLiaison-1][0]=nodeList[k1][0];
                        graphForOpenscad[nbLiaison-1][1]=nodeList[k1][1];
                        graphForOpenscad[nbLiaison-1][2]=nodeList[k2][0];
                        graphForOpenscad[nbLiaison-1][3]=nodeList[k2][1];
                        graphForOpenscad[nbLiaison-1][4]=linkSpec[k1][k2][0];
                        graphForOpenscad[nbLiaison-1][5]=linkSpec[k1][k2][1];
                        graphForOpenscad[nbLiaison-1][6]=linkSpec[k1][k2][2];
                    }
                }
            }
        }
        
        
    }
    std::cout<<"Hello world";
    return 0;
}

