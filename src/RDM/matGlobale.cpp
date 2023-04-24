#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>
using namespace std;


//fonction assemblage de la matrice de rigidité globale version V3

void matriceGlobale(vector<vector<vector<vector<float>>>> &matElements,
                    vector<vector<bool>> &matLiaison,
                    vector<vector<vector<vector<float>>>> &K){
    int n = K.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (matLiaison[i][j]) {
                K[i][i][0][0] += matElements[i][j][0][0];
                K[i][i][0][1] += matElements[i][j][0][1];
                K[i][i][1][0] += matElements[i][j][1][0];
                K[i][i][1][1] += matElements[i][j][1][1];

                K[i][j][0][0] += matElements[i][j][0][2];
                K[i][j][0][1] += matElements[i][j][0][3];
                K[i][j][1][0] += matElements[i][j][1][2];
                K[i][j][1][1] += matElements[i][j][1][3];

                K[j][i][0][0] += matElements[i][j][2][0];
                K[j][i][0][1] += matElements[i][j][2][1];
                K[j][i][1][0] += matElements[i][j][3][0];
                K[j][i][1][1] += matElements[i][j][3][1];

                K[j][j][0][0] += matElements[i][j][2][2];
                K[j][j][0][1] += matElements[i][j][2][3];
                K[j][j][1][0] += matElements[i][j][3][2];
                K[j][j][1][1] += matElements[i][j][3][3];
            }
        }
    }
}


//afficher la matrice K
void afficher(vector<vector<vector<vector<float>>>> &K) {
    for(int i=0;i<K.size();i++) {
        for(int a=0; a<2; a++){
            for(int j=0;j<K.size();j++) {
                cout << K[i][j][a][0] << " " << K[i][j][a][1] << " ";
            }
            cout << endl;
        }
        }
}




int main (){

const int m=4;

//déclaration K :
vector<vector<vector<vector<float>>>> K(m, vector<vector<vector<float>>>(m, vector<vector<float>>(2, vector<float>(2, 0.0))));


//déclaration de la matrice de liaison
vector<vector<bool>>matLiaison(m,vector<bool>(m,0));

matLiaison[0][0] = false;
matLiaison[0][1] = true;
matLiaison[0][2] = true;
matLiaison[0][3] = true;

matLiaison[1][1] = false;
matLiaison[1][2] = false;
matLiaison[1][3] = true;

matLiaison[2][2] = false;
matLiaison[2][3] = true;

matLiaison[3][3] = false;

//déclaration de la matrice des éléments
vector<vector<vector<vector<float>>>> matElements(m, vector<vector<vector<float>>>(m, vector<vector<float>>(4, vector<float>(4))));

//élément 11
matElements[0][0][0][0] = 0;
matElements[0][0][0][1] = 0;
matElements[0][0][0][2] = 0;
matElements[0][0][0][3] = 0;
matElements[0][0][1][0] = 0;
matElements[0][0][1][1] = 0;
matElements[0][0][1][2] = 0;
matElements[0][0][1][3] = 0;
matElements[0][0][2][0] = 0;
matElements[0][0][2][1] = 0;
matElements[0][0][2][2] = 0;
matElements[0][0][2][3] = 0;
matElements[0][0][3][0] = 0;
matElements[0][0][3][1] = 0;
matElements[0][0][3][2] = 0;
matElements[0][0][3][3] = 0;

//élément 12
matElements[0][1][0][0] = 1;
matElements[0][1][0][1] = 1;
matElements[0][1][0][2] = 1;
matElements[0][1][0][3] = 1;
matElements[0][1][1][0] = 1;
matElements[0][1][1][1] = 1;
matElements[0][1][1][2] = 1;
matElements[0][1][1][3] = 1;
matElements[0][1][2][0] = 1;
matElements[0][1][2][1] = 1;
matElements[0][1][2][2] = 1;
matElements[0][1][2][3] = 1;
matElements[0][1][3][0] = 1;
matElements[0][1][3][1] = 1;
matElements[0][1][3][2] = 1;
matElements[0][1][3][3] = 1;


//élément 13
matElements[0][2][0][0] = 1;
matElements[0][2][0][1] = 1;
matElements[0][2][0][2] = 1;
matElements[0][2][0][3] = 1;
matElements[0][2][1][0] = 1;
matElements[0][2][1][1] = 1;
matElements[0][2][1][2] = 1;
matElements[0][2][1][3] = 1;
matElements[0][2][2][0] = 1;
matElements[0][2][2][1] = 1;
matElements[0][2][2][2] = 1;
matElements[0][2][2][3] = 1;
matElements[0][2][3][0] = 1;
matElements[0][2][3][1] = 1;
matElements[0][2][3][2] = 1;
matElements[0][2][3][3] = 1;

//élément 14
matElements[0][3][0][0] = 1;
matElements[0][3][0][1] = 1;
matElements[0][3][0][2] = 1;
matElements[0][3][0][3] = 1;
matElements[0][3][1][0] = 1;
matElements[0][3][1][1] = 1;
matElements[0][3][1][2] = 1;
matElements[0][3][1][3] = 1;
matElements[0][3][2][0] = 1;
matElements[0][3][2][1] = 1;
matElements[0][3][2][2] = 1;
matElements[0][3][2][3] = 1;
matElements[0][3][3][0] = 1;
matElements[0][3][3][1] = 1;
matElements[0][3][3][2] = 1;
matElements[0][3][3][3] = 1;


//élément 22
matElements[1][1][0][0] = 0;
matElements[1][1][0][1] = 0;
matElements[1][1][0][2] = 0;
matElements[1][1][0][3] = 0;
matElements[1][1][1][0] = 0;
matElements[1][1][1][1] = 0;
matElements[1][1][1][2] = 0;
matElements[1][1][1][3] = 0;
matElements[1][1][2][0] = 0;
matElements[1][1][2][1] = 0;
matElements[1][1][2][2] = 0;
matElements[1][1][2][3] = 0;
matElements[1][1][3][0] = 0;
matElements[1][1][3][1] = 0;
matElements[1][1][3][2] = 0;
matElements[1][1][3][3] = 0;

//élément 23
matElements[1][2][0][0] = 0;
matElements[1][2][0][1] = 0;
matElements[1][2][0][2] = 0;
matElements[1][2][0][3] = 0;
matElements[1][2][1][0] = 0;
matElements[1][2][1][1] = 0;
matElements[1][2][1][2] = 0;
matElements[1][2][1][3] = 0;
matElements[1][2][2][0] = 0;
matElements[1][2][2][1] = 0;
matElements[1][2][2][2] = 0;
matElements[1][2][2][3] = 0;
matElements[1][2][3][0] = 0;
matElements[1][2][3][1] = 0;
matElements[1][2][3][2] = 0;
matElements[1][2][3][3] = 0;

//élément 24
matElements[1][3][0][0] = 1;
matElements[1][3][0][1] = 1;
matElements[1][3][0][2] = 1;
matElements[1][3][0][3] = 1;
matElements[1][3][1][0] = 1;
matElements[1][3][1][1] = 1;
matElements[1][3][1][2] = 1;
matElements[1][3][1][3] = 1;
matElements[1][3][2][0] = 1;
matElements[1][3][2][1] = 1;
matElements[1][3][2][2] = 1;
matElements[1][3][2][3] = 1;
matElements[1][3][3][0] = 1;
matElements[1][3][3][1] = 1;
matElements[1][3][3][2] = 1;
matElements[1][3][3][3] = 1;

//élément 33
matElements[2][2][0][0] = 0;
matElements[2][2][0][1] = 0;
matElements[2][2][0][2] = 0;
matElements[2][2][0][3] = 0;
matElements[2][2][1][0] = 0;
matElements[2][2][1][1] = 0;
matElements[2][2][1][2] = 0;
matElements[2][2][1][3] = 0;
matElements[2][2][2][0] = 0;
matElements[2][2][2][1] = 0;
matElements[2][2][2][2] = 0;
matElements[2][2][2][3] = 0;
matElements[2][2][3][0] = 0;
matElements[2][2][3][1] = 0;
matElements[2][2][3][2] = 0;
matElements[2][2][3][3] = 0;

//élément 34
matElements[2][3][0][0] = 1;
matElements[2][3][0][1] = 1;
matElements[2][3][0][2] = 1;
matElements[2][3][0][3] = 1;
matElements[2][3][1][0] = 1;
matElements[2][3][1][1] = 1;
matElements[2][3][1][2] = 1;
matElements[2][3][1][3] = 1;
matElements[2][3][2][0] = 1;
matElements[2][3][2][1] = 1;
matElements[2][3][2][2] = 1;
matElements[2][3][2][3] = 1;
matElements[2][3][3][0] = 1;
matElements[2][3][3][1] = 1;
matElements[2][3][3][2] = 1;
matElements[2][3][3][3] = 1;

//élément 44
matElements[3][3][0][0] = 0;
matElements[3][3][0][1] = 0;
matElements[3][3][0][2] = 0;
matElements[3][3][0][3] = 0;
matElements[3][3][1][0] = 0;
matElements[3][3][1][1] = 0;
matElements[3][3][1][2] = 0;
matElements[3][3][1][3] = 0;
matElements[3][3][2][0] = 0;
matElements[3][3][2][1] = 0;
matElements[3][3][2][2] = 0;
matElements[3][3][2][3] = 0;
matElements[3][3][3][0] = 0;
matElements[3][3][3][1] = 0;
matElements[3][3][3][2] = 0;
matElements[3][3][3][3] = 0;

//construction de la matrice globale :
matriceGlobale (matElements,matLiaison,K);


afficher(K);

return 0;
}

