#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
#include <valarray>
#include <Eigen/Dense>

#include "matElementaire.cpp"
#include "matGlobale.cpp"
#include "déplacements.cpp"

using namespace std;

vector<float> assemblage(vector<vector<vector<float>>>matLinkSpec,
                                 vector<vector<bool>> matLiaison,
                                 vector<bool>U,
                                 vector<float>F){


//crée la matrice de matrice élémentaire
vector<vector<vector<vector<float>>>> matE = matElementaire(matLinkSpec,matLiaison);

//créer la matrice K vide
 vector<vector<vector<vector<float>>>> K(matLiaison.size(), vector<vector<vector<float>>>(matLiaison.size(), vector<vector<float>>(2, vector<float>(2, 0.0))));

//crée la matrice globale K (fonction void)
matriceGlobale(matE, matLiaison, K);

//calculer les deplacements 
vector<float> deplacement = deplacements(U, F, K);

return deplacement;

}



int main(){
    cout << "test 1" << endl << endl;

    //création de la matrice de Liaison 
    vector<vector<bool>> matLiaison(3,vector<bool>(3,false));
    matLiaison[0][1]=true;
    matLiaison[1][2]=true;
    matLiaison[0][2]=true;

    //création de la matrice K 
    //vector<vector<vector<vector<float>>>> K(matLiaison.size(),vector<float>(matLiaison.size()(2,vector<float>(2,0.0))));

    //création de la matrice de Spec
    vector<vector<vector<float>>> matLinkSpec(3, vector<vector<float>>(3, vector<float>(6, 0.0)));

    matLinkSpec[0][1][0] = 0;
    matLinkSpec[0][1][1] = 0.2;
    matLinkSpec[0][1][2] = 0.1;
    matLinkSpec[0][1][3] = 1;
    matLinkSpec[0][1][4] = 0;
    matLinkSpec[0][1][5] = 1000;

    matLinkSpec[0][2][0] = 0;
    matLinkSpec[0][2][1] = 0.2;
    matLinkSpec[0][2][2] = 0.1;
    matLinkSpec[0][2][3] = 1;
    matLinkSpec[0][2][4] = M_PI/3;
    matLinkSpec[0][2][5] = 1000;

    matLinkSpec[1][2][0] = 0;
    matLinkSpec[1][2][1] = 0.2;
    matLinkSpec[1][2][2] = 0.1;
    matLinkSpec[1][2][3] = 1;
    matLinkSpec[1][2][4] = (2/3)*M_PI;
    matLinkSpec[1][2][5] = 1000;

    vector<bool>U(6,false);
    U[0]=true;
    U[1]=true;
    U[2]=true;

    vector<float>F(6,0.0);
    F[5]=10;

    displayV(assemblage(matLinkSpec, matLiaison, U, F));

    cout << "fin du programme" << endl;
    return 0;
}
