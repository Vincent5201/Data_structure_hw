#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct node
{
    char node;//node name
    int w;//node weight
};

class Graph{
    public:       
        int size;
        vector<vector<struct node>> data;
        Graph(int n);
        void insert(char a,char b, int we);//node a, node b, weight of them
        void insert();//an empty head_node which represents end
};
Graph::Graph(int n){
    size=0;
    insert();
}
void Graph::insert(){
    //insert an empty head_node which represents end
    vector<struct node> tmpv;
    struct node tmp;
    tmp.w = -2;
    tmpv.push_back(tmp);
    data.push_back(tmpv);
    size++;
}
void Graph::insert(char a,char b, int we){
    //find a then put b behind a
    int n = 0;
    while(data[n][0].w != -2 && data[n][0].node != a){
        n++;
    }
    if(data[n][0].node == a){
        //a exists
        struct node tmpb;
        tmpb.node=b;
        tmpb.w = we;
        data[n].push_back(tmpb);
    }else{
        //a doesn't exist
        data[n][0].node = a;
        data[n][0].w = -1;
        struct node tmpb;
        tmpb.node=b;
        tmpb.w = we;
        data[n].push_back(tmpb);
        insert();
    }

    //find b then put a behind b
    n = 0;
    while(data[n][0].w != -2 && data[n][0].node != b){
        n++;
    }
    if(data[n][0].node == b){
        //b exists
        struct node tmpa;
        tmpa.node=a;
        tmpa.w = we;
        data[n].push_back(tmpa);
    }else{
        //b doesn't exist
        data[n][0].node = b;
        data[n][0].w = -1;
        struct node tmpa;
        tmpa.node=a;
        tmpa.w = we;
        data[n].push_back(tmpa);
        insert();
    }
}

void swapC(char *a, char *b){
    char tmp = (*b);
    (*b) = (*a);
    (*a) = tmp;
}
void swapI(int *a, int *b){
    int tmp = (*b);
    (*b) = (*a);
    (*a) = tmp;
}
int main(){
    std::cout << "Enter file name: ";
    string name;
    ifstream ifs;
    ofstream ofs;
    std::cin >> name;
    ifs.open(name);
    ofs.open("output_p.txt");
    int n;
    ifs >> n;
    //make graph
    Graph g = Graph(n);
    for(int i=0;i<n;i++){
        char a, b;
        int w;
        ifs >> a >> b >> w;
        g.insert(a,b,w);
    }
    char start;
    ifs >> start;
    //make answer
    bool chosen[g.size-1];//means node is chosen
    for(int i=0;i<g.size-1;i++){
        chosen[i] = false;
    }
    char ans[n][2];//answers' 2 node
    int wans[n];//answers' weight
    int c = 1;//how many nodes are chosen;
    int m = 0;//which node is chosen
    n = 0;//how many edges are chosen
    int s = 0;
    while(start != g.data[s][0].node){
        s++;
    }//find start node
    chosen[s] = true;
    while(c<g.size-1){
        int choson_w = INT_MAX;
        char chosedA, chosedB;
        for(int i=0;i<g.size-1;i++){
            //for all node, if it is chosen, search its edges
            if(chosen[i] == true){
                for(int j=1;j<g.data[i].size();j++){
                    if(g.data[i][j].w < choson_w){
                        //check whether data[i][j] is chosen
                        int k = 0;
                        while(g.data[i][j].node != g.data[k][0].node){
                            k++;
                        }
                        if(chosen[k] == false){
                            //choose them
                            choson_w = g.data[i][j].w;
                            chosedA = g.data[i][0].node;
                            chosedB = g.data[i][j].node;
                            m = k;
                        }
                    }
                }
            }
        }
        chosen[m] = true;
        ans[n][0] = chosedA;
        ans[n][1] = chosedB;
        wans[n] = choson_w;
        c++;
        n++;
    }
    
    //sort
    for(int i=0;i<n;i++){
        if(ans[i][0] > ans[i][1]){
            swapC(&ans[i][0],&ans[i][1]);
        }
    }
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(wans[i] > wans[j]){
                swapC(&ans[i][0],&ans[j][0]);
                swapC(&ans[i][1],&ans[j][1]);
                swapI(&wans[i],&wans[j]);
            }
        }
    }

    //output
    for(int i=0;i<n;i++){
        ofs << ans[i][0] << " " << ans[i][1] << " " << wans[i] << endl;
        std::cout << ans[i][0] << " " << ans[i][1] << " " << wans[i] << endl;
    }
    ifs.close();
    ofs.close();
    return 0;
}