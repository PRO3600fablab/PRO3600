#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

void display(vector<float>V)
{
    for(int i=0; i<V.size(); i++){
        cout << V[i] << endl;
    }
}

vector<float> VectContrainte(vector<float> VectDepl, float cp, float E) 
{
    cp=0.33;
    E=210000;
    //matrice permettant le calcul de contrainte 
    vector<vector<float>> m(3,vector<float>(2));
    m[0][0] = E*(1-cp)/((1+cp)*(1-2*cp)); 
    m[0][1] = E*(cp)/((1+cp)*(1-2*cp));
    m[1][0] = E*(cp)/((1+cp)*(1-2*cp));
    m[1][1] = E*(cp)/((1+cp)*(1-2*cp));
    m[2][0] = E*(cp)/((1+cp)*(1-2*cp));
    m[2][1] = E*(1-cp)/((1+cp)*(1-2*cp)); 


    vector<float> VectCont(3*(VectDepl.size()/2)); // le vecteur contrainte finale aura 3*nb noeud composantes 
    vector<float> TempVectDepl(2);

    for (int k=0; k<VectDepl.size(); k+=2){
        TempVectDepl[0]=VectDepl[k];
        TempVectDepl[1]=VectDepl[k+1];

        for (int i=0; i<3; i++) {
            for (int j = 0; j < 2; j++) {
                VectCont[(k/2)*3+i] += m[i][j] * TempVectDepl[j]; 
            }
        }
    }

    return VectCont;
    
}

/*
int main() {

    cout << "début" << endl;
    
    vector<float> B(4,1);
    B[0] = 1;
    B[1] = 2;
    B[2] = 3;
    B[3] = 4;


    display(VectContrainte(B,1,1));

    cout << "fin" << endl;
    }
    */
    