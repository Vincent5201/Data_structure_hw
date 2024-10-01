#include <iostream>
#include <fstream>

using namespace std;

void path(const int m, const int p);
void setDirc();
void printStack();

int maze[17][17];/*question*/
int mark[17][17] = {0};/*recoed whether have been or not*/
int steps = 0;/*total steps*/
ofstream ofs;

/*Items class*/
class Items {
public:
    int x, y;
    int dir;
    Items(){
        x = -1;
        y = -1;
        dir = -1;
    }
    Items(int i, int j, int n)
    {
        x = i;
        y = j;    
        dir = n;
    }
    void print(){
        cout << x << "," << y << "\n";
        ofs << x << "," << y << "\n";
    }
};

/*stack class*/
class MyStack{
private:
    int ntop,capacity;
    Items *stack;
    void doubleCapacity();
public:
    MyStack(){
        ntop = -1;
        capacity = 1;
        stack = new Items[capacity*sizeof(Items)];
    }
    void push(Items temp);
    void pop();
    bool empty();
    int size();
    Items top();
};
void MyStack::doubleCapacity(){
    capacity *= 2;                            
    Items *newStack = new Items[capacity*sizeof(Items)];       
    for (int i = 0 ; i < capacity/2; i++) {  
        newStack[i] = stack[i];
    }
    delete [] stack;              
    stack = newStack;             
}
void MyStack::push(Items temp){

    if (ntop == capacity - 1) {    
        doubleCapacity();
    }
    stack[++ntop] = temp;            
}
void MyStack::pop(){
    if (empty()) {          
        cout << "Stack is empty.\n";
        return;
    }
    ntop--;                           
}
bool MyStack::empty(){
    return (ntop == -1);
}
Items MyStack::top(){

    if (empty()) {    
        cout << "Stack is empty.\n";
        return Items(-1,-1,-1);
    }
    return stack[ntop];   
}
int MyStack::size(){
    return ntop+1;        
}

/*direction struct*/
typedef struct { 
int a; /*row*/ 
int b; /*col*/
} offsets; 

offsets direction[9];/*direction*/
MyStack myAns = MyStack();/*clear path*/
MyStack myRecord = MyStack();/*full path*/

int main(){
    /*set data*/
    string input = "test_case_2.txt";
    ifstream ifs(input,ios::in);	
    string s;  
    int i=0;
    while (getline(ifs, s)) {
        for(int j=0;j<17;j++){
            maze[i][j] = s[j]-'0';
        }
        i++;
    }
    ifs.close();	
    setDirc();
    /*start*/
    ofs.open("output.txt");
    path(15,16);
    ofs.close();
    return 0;
}


void path(const int m, const int p){  
    mark[1][0] = 1;
    mark[1][1] = 1;
    Items temp(1, 1, 0);
    myAns.push(temp); 
    while (!myAns.empty()){
        temp = myAns.top(); 
        myRecord.push(temp);       
        myAns.pop(); 
        int i = temp.x, j = temp.y, d = temp.dir, c = 0;;
        while (d < 9){ 
            /*move forward*/
            int g = i + direction[d].a; 
            int h = j + direction[d].b;
            if ((g == m) && (h == p)) { 
                /* successful output*/ 
                cout << "0:1,0" << endl;
    			ofs << "0:1,0" << endl;
                printStack();
                steps++;
                cout << steps << ":" << i << "," << j << endl; /*last two squares*/
                ofs << steps << ":" << i << "," << j << endl;
                steps++;
                cout << steps << ":" << m << "," << p << endl;
                ofs << steps << ":" << m << "," << p << endl;
                cout << "successfully escaped!!" << endl;
                ofs << "successfully escaped!!" << endl;
                return;
            }
            if ((maze[g][h] == 0) && (mark[g][h] == 0)) { 
                /*move to (g, h)*/
                mark[g][h] = 1;
                temp.x = i; temp.y = j; temp.dir = d;
                myAns.push(temp); 
                if(temp.x!=myRecord.top().x || temp.y!=myRecord.top().y){
                    myRecord.push(temp);
                }
                i = g; j = h; d = 0,c = 0; 
            }
            else{ 
                /*try next direction*/
                c++;
                d++;
            } 
            if(c == 9){
                /* all directions fail*/
                temp.x = i; temp.y = j; temp.dir = d;
                myRecord.push(temp);
            }
        }
    }
    /*output fail*/
    cout << "0:1,0" << endl;
    ofs << "0:1,0" << endl;
    printStack();
    steps++;
    cout << steps << ":" << 1 << "," << 0 << endl;
    ofs << steps << ":" << 1 << "," << 0 << endl;
    cout << "fail to escape." << endl;
    ofs << "fail to escape." << endl;
    return;
}

void setDirc(){
    int as[9] = {0,0,1,1,1,0,-1,-1,-1};
    int bs[9] = {0,1,1,0,-1,-1,-1,0,1};
    for(int i=0;i<9;i++){
        direction[i].a = as[i];
        direction[i].b = bs[i];
    }
}

void printStack(){
    int n = myRecord.size();
    steps = n;
    Items tmp[n];
    /*reverse stack*/
    for(int i=0;i<n;i++){
        tmp[i] = Items();
    }
    while(!myRecord.empty()){
        tmp[n-1] = myRecord.top();
        myRecord.pop();
        n--;
    }
    for(int i=0;i<steps;i++){
        cout << (i+1) << ":";
        ofs << (i+1) << ":";
        tmp[i].print();
    }
    return;
}

