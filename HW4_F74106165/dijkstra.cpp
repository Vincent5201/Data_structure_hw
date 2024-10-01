#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(){
    std::cout << "Enter file name: ";
    string name;
    ifstream ifs;
    ofstream ofs;
    std::cin >> name;
    ifs.open(name);
    ofs.open("output_d.txt");
    int n;
    ifs >> n;
    //read file and make adjmatrix
    int data[26][26];
    for(int i=0;i<26;i++){
        for(int j=0;j<26;j++){
            data[i][j] = INT_MAX;
        }
    }
    int size = 26;
    for(int i=0;i<n;i++){
        char a, b;
        int w;
        ifs >> a >> b >> w;
        data[a-'a'][b-'a'] = w;
    }
    for(int i=0;i<size;i++){
        data[i][i] = 0;
    }
    char start;
    ifs >> start;

    //array of length from start to each point
    int length[size];
    char ch[size];
    for(int i=0;i<size;i++){
        length[i] = INT_MAX;
        ch[i] = 'a'+i;
    }
    length[start-'a'] = 0;//start point
    bool check = true;
    while(check){
        check = false;
        for(int i=0;i<size;i++){
            if(length[i]!=INT_MAX){//node i has gone
                for(int j=0;j<size;j++){
                    if(data[i][j]!=INT_MAX && data[i][j]+length[i] < length[j]){//node j can be reached from i and shorter                       
                        length[j] = data[i][j]+length[i];// change to small length
                        check = true;//if has change, do loop again
                    }
                }
            }
        }
    }
    //sort answer
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(length[i] > length[j]){
                char tmpc = ch[i];
                ch[i] = ch[j];
                ch[j] = tmpc;

                int tmp = length[i];
                length[i] = length[j];
                length[j] = tmp;
            }
        }
    }
    //cout
    for(int i=0;i<size;i++){
        if(length[i]!=INT_MAX){
            std::cout << ch[i] << " " << length[i] <<endl;
            ofs << ch[i] << " " << length[i] <<endl;
        }
    }
    ifs.close();
    ofs.close();
    return 0;
}