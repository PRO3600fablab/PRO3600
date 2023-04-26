#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
#include <valarray>
#include <Eigen/Dense>

#include <matElementaire.cpp>
#include<matGlobale.cpp>
#include<déplacements.cpp>

using namespace std;

vector<vector<float>> assemblage(vector<vector<vector<float>>>matLinkSpec,
                                 vector<vector<bool>> matLiaison,
                                 vector<bool>U,
                                 vector<float>F){

//crée la matrice de matrice élémentaire
vector<vector<vector<vector<float>>>> matElementaire = matElementaire(&matLinkSpec,&matLiaison);

//crée une matrice vide qui va recevoir la matrice K
vector<vector<vector<vector<float>> K(matLiaison.size(),0.0);

//crée la matrice globale K (fonction void)
matriceGlobale(&matElements, &matLiaison, &K);

//calculer les deplacements 
vector<float> deplacement = deplacements(U, F, K);

return deplacement;

}




int main(){
    cout << "test 1" << endl << endl;
    return 0;
}