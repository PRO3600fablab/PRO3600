#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <array>
#include <cmath>
#include <valarray>
#include <Eigen/Dense>
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



//fonction permettant de retranscrire une matrice de matrice 2*2 plus simplement en matrice 2*2
vector<vector<float>> MatConvertion(vector<vector<vector<vector<float>>>> inMat){
    int taille(inMat.size());
    vector<vector<float>> outMat(taille*2,vector<float>(taille*2,0.0));
     for (int i = 0; i < taille ; i++) {
        for (int k = 0; k < 2; k++) {
                for (int j = 0; j < taille; j++) {
                    for (int l = 0; l < 2; l++) {
                        outMat[2*i+k][2*j+l] = inMat[i][j][k][l];
                    }
                }
            }
        }
        return outMat;
}



//fonction permettant de donner la transposée d'une matrice 
vector<vector<float>> transpose(vector<vector<float>>inMat){
    int ligne(inMat.size());
    int col(inMat[0].size());
    vector<vector<float>> outMat(col,vector<float>(ligne,0));

     for(int i = 0; i < ligne; i++) {
        for(int j = 0; j < col; j++) {
            outMat[j][i] = inMat[i][j];
        }
    }
    return outMat;
}




//fonction permettant de créer la sous matrice
vector<vector<float>> sousMatrice(vector<bool> U, vector<vector<float>> K) {
    
int ligneK2(0);
for (int i=0; i<K.size(); i++){ //détermine le nombre de ligne qu'aura la matrice K2
    if (U[i]!=true){
        ligneK2+=1;
    }
}

int count(-1);//ce compteur va nous permettre de recopier les éléments que l'on souhaite conserver à la bonne ligne dans matrice K2
vector<vector<float>> K2(ligneK2,vector<float>(K.size(),0.0));
    for (int i = 0; i < U.size() ; i++) {
    if (U[i]!=true){
        count+=1;
        for (int j=0; j<K[0].size(); j++){
            K2[count][j]=K[i][j];
            
        }

        }
    }

    int count2(-1);
    vector<vector<float>> K3 = transpose(K2);
    vector<vector<float>> K4 (ligneK2,vector<float>(ligneK2,7.0));
    
    for (int i = 0; i < U.size() ; i++) {
    if (U[i]!=true){
        count2+=1;
        for (int j=0; j<K3[0].size(); j++){
            K4[count2][j]=K3[i][j];   
        }
        }  
    }

return K4;
                
}




//fonction pour afficher les vecteurs :
void displayV(vector<float> V){
    int taille(V.size());
    for (int i(0); i<taille; i++){
        cout << V[i] << endl;
    }
}



//fonction pour afficher la matrice
void displayM(vector<vector<float>> M){
    for (int i(0); i<M.size(); i++){
        for (int j(0); j<M[i].size(); j++){
            cout << M[i][j] << "  ";    
        }
        cout << endl;
    }
}



//fonction permettant le calcul Matriciel 
vector<float> calculMat(vector<vector<float>> M, vector<float> U) {
    int ligne = M.size(); 
    int col = M[0].size();

    if (col != U.size()) {
        // vérifier que les dimensions de la matrice et du vecteur sont compatibles
        cout << "La dimension de la matrice M doit correspondre à la dimension du vecteur U.";
    }

    vector<float> result(ligne, 0.0);


    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < col; j++) {
            result[i] += M[i][j] * U[j];
        }
    }

    return result;
}




//fonction permettant de calculer les deplacements 
vector<float> deplacements(vector<bool>U, vector<float>F, vector<vector<vector<vector<float>>>>K )
{
    
    //créer le sous vecteur Déplacement 
    vector<float>U2 = sousVecteurDeplac(U);
    //créer le sous vecteur Force
    vector<float>F2 = sousVecteurForce(U,F);


    // retranscrire la matrice de matrice 2*2 (K) simplement en matrice 2*2 (Kintermediaire)
    vector<vector<float>>Kintermediaire = MatConvertion(K);
    //créer la sous matrice K2
    vector<vector<float>>K2 = sousMatrice(U,Kintermediaire);

    

    int ligne = K2.size();
    int col = K2[0].size();
    
    Eigen::MatrixXf matEigen(ligne, col);
    
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < col; j++) {
            matEigen(i, j) = K2[i][j];
        }
    }
    
    //inverser la matrice
    Eigen::MatrixXf matInverse = matEigen.inverse();

    // repasser en vector<vector<float>> pour pouvoir faire le calcul matricielle 
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < col; j++) {
            K2[i][j] = matInverse(i,j);
        }
    }

    cout << "la matrice inverse est égale à : " << endl;
    displayM(K2);
    

    //calcule de U2 = K2^-1 F2
        U2 = calculMat(K2,F2);
    //vector<float> U2 = calculMat(InvMat(taille,K2),F2);

    //reconstitution du vecteur déplacement U
    vector<float> U3(U.size(),0.0);
    for (int i=0; i<U.size(); i++){
        int count(-1);
        if(U[i]!=true){
            count+=1;
            U3[i]=U2[count];
        }
    }

    return U3;
}




int main (){
    cout << "test1" << endl;

    vector<bool>U(6);
    U[0]=false;
    U[1]=true;
    U[2]=false;
    U[3]=true;
    U[4]=false;
    U[5]=true;
  
    vector<float>F(6,2);
    F[0]=9;
    F[1]=3;
    F[2]=9;
    F[3]=3;
    F[4]=9;
    F[5]=3;

  
   vector<vector<vector<vector<float>>>> K(3, vector<vector<vector<float>>>(3, vector<vector<float>>(2, vector<float>(2, 1.0))));
   K[0][0][1][1]=-1;
   K[1][2][0][0]=-1;
   K[2][1][0][0]=-1;

    cout << endl << " sous vect Déplacement : " << endl;
    displayV(sousVecteurDeplac(U));
    cout << endl<< " sous vect Force : " << endl;
    displayV(sousVecteurForce(U,F));

    cout << endl <<"sous matrice : " << endl;
    vector<vector<float>>K2 = MatConvertion(K);
    vector<vector<float>>K3 = sousMatrice(U,K2);
    displayM(K3);
    cout << endl << "inverse de la matrice : " << endl; 

    cout << endl << "déplacements U2 : " << endl;
    vector<float> U2 = deplacements(U,F,K);
    displayV(U2);


   cout << "fin programme" << endl;
return 0;
}
