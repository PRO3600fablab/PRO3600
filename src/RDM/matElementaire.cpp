#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
using namespace std;

//afficher la matrice de matrices élémentaires
void afficher(vector<vector<vector<vector<float>>>> K) {
    for(int m=0; m<3; m++){
        for(int n=0; n<3; n++){
            for(int i=0;i<4;i++) {
                for(int j=0;j<4;j++) {
                    cout << K[m][n][i][j] << "  ";
                }
                cout << endl;
            }
           cout << endl;
        }
        cout << "---------------------"<< endl<< endl;
    }
}

//fonction de construction de la matrice regroupant toutes les matrices élémentaires
 vector<vector<vector<vector<float>>>> matElementaire(vector<vector<vector<float>>>matLinkSpec, vector<vector<bool>> matLiaison){
//type poutre : 1 correspond à une section cylindrique 0 à une section carré

 vector<vector<vector<vector<float>>>> Ke(matLinkSpec.size(), vector<vector<vector<float>>>(matLinkSpec.size(), vector<vector<float>>(4, vector<float>(4, 0.0))));

for(int i=0; i<matLinkSpec.size(); i++){
    for(int j=0;j<matLinkSpec.size(); j++){
        if(matLiaison[i][j]){
            float typePoutre = matLinkSpec[i][j][0];
            float exter = matLinkSpec[i][j][1];
            float inter = matLinkSpec[i][j][2];
            float L = matLinkSpec[i][j][3];
            float theta = matLinkSpec[i][j][4];
            float E = matLinkSpec[i][j][5];
            float A(0);


               if(typePoutre !=0 && typePoutre!=1){ // cette partie de la condition sert à prévenir les erreurs d'arrondies (la valeur typePoutre est stockée en float au lieu de int)
                    typePoutre-=0.25;
                    if (typePoutre<0.5){
                        typePoutre=0;
                    }
                    else{
                        typePoutre=1;
                    }
                }

                if (typePoutre == 0){ // calcul aire section carrée
                    A = pow(exter,2)-pow(inter,2);
                }
                else if(typePoutre == 1) {//calcul aire section cylindrique
                    A= ((M_PI)/(4)) * (pow(exter,2)-pow(inter,2));
                }


                Ke[i][j][0][0] = ((E*A)/L)*pow(cos(theta),2);
                Ke[i][j][0][1] = ((E*A)/L)*cos(theta)*sin(theta);
                Ke[i][j][0][2] = ((E*A)/L)*-pow(cos(theta),2);
                Ke[i][j][0][3] = ((E*A)/L)*-cos(theta)*sin(theta);

                Ke[i][j][1][0] = ((E*A)/L)*cos(theta)*sin(theta);
                Ke[i][j][1][1] = ((E*A)/L)*pow(sin(theta),2);
                Ke[i][j][1][2] = ((E*A)/L)*-cos(theta)*sin(theta);
                Ke[i][j][1][3] = ((E*A)/L)*-pow(sin(theta),2);

                Ke[i][j][2][0] = ((E*A)/L)*-pow(cos(theta),2);
                Ke[i][j][2][1] = ((E*A)/L)*-cos(theta)*sin(theta);
                Ke[i][j][2][2] = ((E*A)/L)*pow(cos(theta),2);
                Ke[i][j][2][3] = ((E*A)/L)*cos(theta)*sin(theta);

                Ke[i][j][3][0] = ((E*A)/L)*-cos(theta)*sin(theta);
                Ke[i][j][3][1] = ((E*A)/L)*-pow(sin(theta),2);
                Ke[i][j][3][2] = ((E*A)/L)*cos(theta)*sin(theta);
                Ke[i][j][3][3] = ((E*A)/L)*pow(sin(theta),2);


        }
    }
}

return Ke;

}



/*

int main (){

vector<vector<bool>> matLiaison(3, vector<bool>(3,true));


vector<vector<vector<float>>>matLinkSpec(3, vector<vector<float>>(3,vector<float>(6, 0.0)));

matLinkSpec[0][0][0] = 0;
matLinkSpec[0][0][1] = 0.2;
matLinkSpec[0][0][2] = 0.1;
matLinkSpec[0][0][3] = 1;
matLinkSpec[0][0][4] = (M_PI/3);
matLinkSpec[0][0][5] = 1000;

matLinkSpec[0][1][0] = 0;
matLinkSpec[0][1][1] = 0.2;
matLinkSpec[0][1][2] = 0.1;
matLinkSpec[0][1][3] = 1;
matLinkSpec[0][1][4] = (M_PI/3);
matLinkSpec[0][1][5] = 0;

matLinkSpec[0][2][0] = 0;
matLinkSpec[0][2][1] = 0.2;
matLinkSpec[0][2][2] = 0.1;
matLinkSpec[0][2][3] = 1;
matLinkSpec[0][2][4] = (M_PI/3);
matLinkSpec[0][2][5] = 100000;

matLinkSpec[1][0][0] = 0;
matLinkSpec[1][0][1] = 0.2;
matLinkSpec[1][0][2] = 0.1;
matLinkSpec[1][0][3] = 1;
matLinkSpec[1][0][4] = (M_PI/3);
matLinkSpec[1][0][5] = 0;

matLinkSpec[1][1][0] = 0;
matLinkSpec[1][1][1] = 0.2;
matLinkSpec[1][1][2] = 0.1;
matLinkSpec[1][1][3] = 1;
matLinkSpec[1][1][4] = (M_PI/3);
matLinkSpec[1][1][5] = 1000;

matLinkSpec[1][2][0] = 0;
matLinkSpec[1][2][1] = 0.2;
matLinkSpec[1][2][2] = 0.1;
matLinkSpec[1][2][3] = 1;
matLinkSpec[1][2][4] = (M_PI/3);
matLinkSpec[1][2][5] = 1000;

matLinkSpec[2][0][0] = 0;
matLinkSpec[2][0][1] = 0.2;
matLinkSpec[2][0][2] = 0.1;
matLinkSpec[2][0][3] = 1;
matLinkSpec[2][0][4] = (M_PI/3);
matLinkSpec[2][0][5] = 1000;

matLinkSpec[2][1][0] = 0;
matLinkSpec[2][1][1] = 0.2;
matLinkSpec[2][1][2] = 0.1;
matLinkSpec[2][1][3] = 1;
matLinkSpec[2][1][4] = (M_PI/3);
matLinkSpec[2][1][5] = 1000;

matLinkSpec[2][2][0] = 0;
matLinkSpec[2][2][1] = 0.2;
matLinkSpec[2][2][2] = 0.1;
matLinkSpec[2][2][3] = 1;
matLinkSpec[2][2][4] = (M_PI/3);
matLinkSpec[2][2][5] = 1000;

afficher(matElementaire(matLinkSpec, matLiaison));

return 0;
}
*/