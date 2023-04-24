#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
#include <valarray>
using namespace std;


//fonction permettant de créer le sous vecteur de déplacements 
vector<float> sousVecteurDeplac(vector<bool>V){
    int count(0);
        for (int i(0); i < V.size(); i++){
            if (V[i]!=true){ // true signifie qu'il y a une laison (donc pas de déplacements possible)
                count+=1;
            } 
        }
    vector<float> V2(count, 0.0);//créer un vecteur de cont dimension initialisés à 0
    return V2; 
}



//fonction permettant de créer le sous vecteur de Force 
vector<float> sousVecteurForce(vector<bool>V, vector<float>F){
    int count(0);
    vector<float> F2;
        for (int i(0); i < V.size(); i++){
            if (V[i]!=true){
                count+=1;
                F2.push_back(F[i]);
            }
        }
    return F2;
}



//fonction permettant de créer la sous matrice 
vector<vector<float>> sousMatrice(vector<bool>V,vector<vector<vector<vector<float>>>> K)
{
   int count(0);
      vector<vector<float>> K2(0);
        for (int ligne(0); ligne<V.size(); ligne++){
            if (V[ligne]!=true){
                    for (int a(0); a<2; a++){
                        for (int colone(0); colone<V.size(); colone++){
                            for (int b(0); b<2; b++){
                                
                                for(int push(0); push<count; push++){
                                    K2[push].push_back(0.0);
                                }
                                count+=1;
                                vector<float> nouvelle_ligne(count, 0.0);
                                K2.push_back(nouvelle_ligne);
                                K2[count][2*colone-1+a]=K[ligne][colone][a][b];//il faut réaliser l'opération 2*c-1+a car initialement la matrice est une matrice de matrice 2*2 que l'on remet dans une 2*2 
                            }
                        }
                    }
            
            }
        }
        return K2 ;
}



//fonction pour afficher les vecteurs :
void displayV(vector<float>V){
    int taille(V.size());
    for (int i(0); i<taille; i++){
        cout << V[i] << endl;
    }
}



//fonction pour afficher la matrice
void displayM(vector<vector<float>> M){
    int taille(M.size());
    for (int i(0); i<taille; i++){
        for (int j(0); j<taille; j++){
            cout << M[i][j];    
        }
        cout << endl;
    }
}



//fonction permettant d'inverser une matrice
vector<vector<float>> InvMat(int NbElement, vector<vector<float>> &Mat)
{
    vector<vector<float>> temp(NbElement, vector<float>(NbElement, 0.0));

    for(int i=0; i<NbElement; i++)
    {
        for(int j=0; j<NbElement; j++)
        {
            temp[i][i] = 1.0/Mat[i][i];
            if(j!=i)
            {
                temp[i][j] = -Mat[i][j]/Mat[i][i];
            }
            for(int k=0; k<NbElement; k++)
            {
                if(k!=i)
                {
                    temp[k][i] = Mat[k][i]/Mat[i][i];
                }
                if(j!=i && k!=i)
                {
                    temp[k][j] = Mat[k][j] - Mat[i][j]*Mat[k][i]/Mat[i][i];
                }
            }
        }
        for(int i=0; i<NbElement; i++)
        {
            for(int j=0; j<NbElement; j++)
            {
                Mat[i][j] = temp[i][j];
            }
        }
    }
    return temp;
}


/*
//fonction permettant de calculer les deplacements 
vector<float> deplacements(vector<bool>U, vector<float>F, vector<vector<vector<vector<float>>>>K )
{
    
    //créer le sous vecteurs déplacements simplifié U2 
    vector<float>U2 = sousVecteurDeplac(U);
    vector<float>F2 = sousVecteurForce(U,F);

    //créer la sous matrice
    vector<vector<float>>K2 = sousMatrice(U,K);


    int degreHyperStat;
    //calculer le deg Hyper Stat 

    if (degreHyperStat < 0){
        cout << "Le système n'est pas résolvable (hypo-statique)" << endl;
        cout << "Veuillez contraindre d'avantage votre sytème"<< endl;
    }


    //inverser la matrices K2
    int taille(K2.size());
    vector<vector<float>> K3 = InvMat(taille,K2);
    

    //calcule de U2 = K2^-1 F2

    //reconstitution du vecteur déplacement U

}
*/


int main (){
    cout << "test1" << endl;
    vector<bool>U(6);
    U[0]=false;
    U[1]=true;
    U[2]=false;
    U[3]=true;
    U[4]=false;
    U[5]=true;
    cout << "test2"<< endl;
    vector<float>F(6,2);
    F[0]=9;
    F[1]=3;
    F[2]=9;
    F[3]=3;
    F[4]=9;
    F[5]=3;

  /*
    vector<vector<vector<vector<float>>>>K;
    cout << "test3"<< endl;
    K[0][0][0][0]=1;
    K[0][0][0][1]=1;
    K[0][0][1][0]=1;
    K[0][0][1][1]=1;
    cout << "test zeub" << endl;
    K[0][1][0][0]=1;
    K[0][1][0][1]=1;
    K[0][1][1][0]=1;
    K[0][1][1][1]=1;

    K[1][0][0][0]=1;
    K[1][0][0][1]=1;
    K[1][0][1][0]=1;
    K[1][0][1][1]=1;

    K[1][1][0][0]=1;
    K[1][1][0][1]=1;
    K[1][1][1][0]=1;
    K[1][1][1][1]=1;
    cout << "test4" << endl;
  
    vector<vector<float>> M(2, vector<float>(2,0.0));
    M[0][0]=0.0;
    M[0][1]=1.2;
    M[1][0]=2.3;
    M[1][1]=2.2;
    displayM(M);
  */

    cout << " sous vect Déplacement : " << endl;
    displayV(sousVecteurDeplac(U));
    cout << " sous vect Force : " << endl;
    displayV(sousVecteurForce(U,F));
   // displayM(sousMatrice(U,K));

   cout << "test6" << endl;
return 0;
}