#include <iostream>

#define swap(x, y) {int tmp = x; x = y; y = tmp;}

using namespace std;

class Graph{
    private:
        void double_node_capacity();
        void double_edge_capacity();
    public:
        int **edges,size_n,size_e,n,e,**nodes;
        Graph();
        void insert_node(int a);
        void insert_edge(int a,int b);
        bool check_adj(int a,int b);
        bool contain(int a);
};
Graph::Graph(){
    n = 0;
    e = 0;
    size_n = 1;
    size_e = 1;
    edges = new int*[sizeof(int*)*size_e];
    nodes = new int*[sizeof(int*)*size_n];
    for(int i=0;i<size_e;i++){
        edges[i] = new int[sizeof(int)*2];
    }
    for(int i=0;i<size_n;i++){
        nodes[i] = new int[sizeof(int)*2];
    }
}
void Graph::double_edge_capacity(){
    size_e*=2;
    int **new_edges = new int*[sizeof(int*)*size_e];
    for(int i=0;i<size_e;i++){
        new_edges[i] = new int[sizeof(int)*2];
    }
    for(int i=0;i<e;i++){
        for(int j=0;j<2;j++){
            new_edges[i][j] = edges[i][j];
        }
    }
    for(int i=0;i<e;i++){
        delete [] edges[i];
    }
    delete [] edges;
    edges = new_edges;
}
void Graph::double_node_capacity(){
    size_n*=2;
    int **new_nodes = new int*[sizeof(int*)*size_n];
    for(int i=0;i<size_n;i++){
        new_nodes[i] = new int[sizeof(int)*2];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<2;j++){
            new_nodes[i][j] = nodes[i][j];
        } 
    }
    for(int i=0;i<n;i++){
        delete [] nodes[i];
    }
    delete [] nodes;
    nodes = new_nodes;
}
void Graph::insert_node(int a){
    if(contain(a)){
        return;
    }
    if(n>=size_n){
        double_node_capacity();
    }
    nodes[n][0] = a;
    nodes[n][1] = n;
    n++;
}
void Graph::insert_edge(int a,int b){
    if(e>=size_e){
        double_edge_capacity();
    }
    edges[e][0] = a;
    edges[e][1] = b;
    e++;
    int p = -1,q = -1;
    int l = 0,h = n-1;
    while(l<=h){
        int m = (l+h)/2;
        if(nodes[m][0]<a){
            l = m + 1;
        }else if(nodes[m][0]>a){
            h = m - 1;
        }else{
            p = m;
            break;
        }
    }
    l = 0,h = n-1;
    while(l<=h){
        int m = (l+h)/2;
        if(nodes[m][0]<b){
            l = m + 1;
        }else if(nodes[m][0]>b){
            h = m - 1;
        }else{
            q = m;
            break;
        }
    }
    if(nodes[p][1] != nodes[q][1]){
        int t = nodes[q][1];
        for(int j=0;j<n;j++){
            if(nodes[j][1] == t){
                nodes[j][1] = nodes[p][1];
            }
        }
    }
}
bool Graph::check_adj(int a,int b){
    int p = -1,q = -1;
    int l = 0,h = n-1;
    while(l<=h){
        int m = (l+h)/2;
        if(nodes[m][0]<a){
            l = m + 1;
        }else if(nodes[m][0]>a){
            h = m - 1;
        }else{
            p = m;
            break;
        }
    }
    l = 0,h = n-1;
    while(l<=h){
        int m = (l+h)/2;
        if(nodes[m][0]<b){
            l = m + 1;
        }else if(nodes[m][0]>b){
            h = m - 1;
        }else{
            q = m;
            break;
        }
    }
    if(nodes[p][1] == nodes[q][1]){
        return true;
    }else{
        return false;
    }

}
bool Graph::contain(int a){
    for(int i=0;i<n;i++){
        if(nodes[i][0] == a){
            return true;
        }
    }
    return false;
}

void quicksort(int **a,int low,int high,int n);
int partition(int **a, int low, int high,int n);

int main(){
    int v,e;
    long long int ans = 0;
    cin >> v;
    cin >> e;
    getchar();
    int **data;  
    Graph g;
    
    data = (int**)malloc(e*sizeof(int*));
    for(int i=0;i<e;i++){
		data[i] = (int*)malloc(sizeof(int)*3);
	}
    for(int i=0;i<e;i++){
        cin >> data[i][0] >> data[i][1] >> data[i][2];
        getchar();
    }
    
    for(int i=0;i<e;i++){           
        g.insert_node(data[i][0]);      
        g.insert_node(data[i][1]);       
    }
    quicksort(g.nodes,0,g.n-1,0);
    quicksort(data,0,e-1,2);

    for(int i=0;i<e;i++){       
        if(!g.check_adj(data[i][0],data[i][1])){
            ans+=data[i][2];
            g.insert_edge(data[i][0],data[i][1]);
        }
    }
    cout << ans;
    for(int i=0;i<e;i++){
        delete [] data[i];
    }
    delete [] data;
    return 0;
}



void quicksort(int **a, int low, int high,int n) {
    if(low>=high){
        return;
    }
    int mid=partition(a,low,high,n);
    quicksort(a,low,mid-1,n);
    quicksort(a,mid+1,high,n);
    return;
}
int partition(int **a, int low, int high,int n) {
    int s=0,e=a[high][n];
    for(int i=0;i<high;i++){
        if(a[i][n]<=e){
            for(int j=0;j<=sizeof(a[0])/sizeof(a[0][0]);j++){
                swap(a[i][j],a[s][j]);
            }
            s++;
        }
    }
    for(int j=0;j<=sizeof(a[0])/sizeof(a[0][0]);j++){
        swap(a[high][j],a[s][j]);
    }
    return s;
}
