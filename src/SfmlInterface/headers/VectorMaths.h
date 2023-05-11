#pragma once 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#include <iostream>
using namespace std;
/*

*/

string displayVect(vector<vector<float>> v){};
string displayVect(vector<vector<bool>> v){};
class VectorMaths{
    public:
    VectorMaths();
    

    void increaseMatrix(vector<vector<double> > matrix);

    void beginMatrix(vector<vector<double> > matrix, int n);
    
    void del(vector<vector<double> > matrix);
};
