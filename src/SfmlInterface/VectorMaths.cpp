#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
/*

*/

string displayVect(vector<vector<float>> v){
    string answer = "";
        for(int k = 0; k<v.size();k++){
            //cout<<"[";
            answer +="node "+std::to_string(k)+" : [ ";
            for(int i = 0;i<(v[k]).size();i++){
                //cout<<v[k][i];
                //cout<<" ";
                answer += std::to_string(v[k][i]);
                answer +=" ";
                if(i!=(v[k]).size()-1){
                    answer+="; ";
                }
            }
            //cout<<"]";
            answer +="]";
            //cout<<"\n";
            answer +="\n";

        }
        //cout<<"\n";
        answer +="\n";
        return answer;
    };
    
string displayVect(vector<vector<bool>> v){
    string answer = "";
        for(int k = 0; k<v.size();k++){
            //cout<<"[";
            answer +="node "+std::to_string(k)+" : [ ";
            for(int i = 0;i<(v[k]).size();i++){
                //cout<<v[k][i];
                //cout<<" ";
                answer += std::to_string(v[k][i]);
                answer +=" ";
                if(i!=(v[k]).size()-1){
                    answer+="; ";
                }
            }
            //cout<<"]";
            answer +="]";
            //cout<<"\n";
            answer +="\n";

        }
        //cout<<"\n";
        answer +="\n";
        return answer;
    };

class VectorMaths{
    public:
    VectorMaths(){}
    

    void increaseMatrix(vector<vector<double> > matrix){
        // we increase the 2d vector by one on each dimension
        int n = matrix.size();
        matrix.resize(n+1);
        for(int i = 0; i < n+1; i++){
            matrix[i].resize(n+1);
        }
    };

    void beginMatrix(vector<vector<double> > matrix, int n){
        // we initiale a nxn matrix ( 2d vector)
        matrix.resize(n);
        for(int i = 0; i < n; i++){
            matrix[i].resize(n);
        }
    };
    void del(vector<vector<double> > matrix){
        for(int i = 0; i < matrix.size(); i++){
        }

    }
};