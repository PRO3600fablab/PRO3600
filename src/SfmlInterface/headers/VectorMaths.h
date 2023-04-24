#pragma once 

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>


#include <iostream>
using namespace std;
/*

*/

string displayVect(vector<vector<float>> v){};
    
class VectorMaths{
    public:
    VectorMaths();
    

    void increaseMatrix(vector<vector<double> > matrix);

    void beginMatrix(vector<vector<double> > matrix, int n);
    
    void del(vector<vector<double> > matrix);
};
