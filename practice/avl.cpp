#include <iostream>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

struct Node{
    int data,h,bf;
    Node *left;
    Node *right;
    Node *parent;
};

class Avl{
    private:
        void balance(Node *node);
        void RR(Node *node);
        void LL(Node *node);
        void RL(Node *node);
        void LR(Node *node);
        void setBF(Node *node);
        void setH(Node *node);
        void connect(Node *parent,bool direction, Node *child);
        void becomeEx(Node *node);
    public:
        Node *start;
        int n;
        Avl();
        ~Avl();
        bool insert(int a,Node *node);
        bool del(int a);
        bool search(int a);
        bool check(Node *node);
        void level(Node *tmp);
};
Avl::Avl(){
    n = 0;
    start = new Node();
    start->data = -1;
    start->h = 0;
    start->parent = NULL;
}
Avl::~Avl() {
    queue<Node*> q;
    if (start != nullptr) {
        q.push(start);
    }
    while (!q.empty()) {
        Node *node = q.front();
        q.pop();
        if (node->left != nullptr) {
            q.push(node->left);
        }
        if (node->right != nullptr) {
            q.push(node->right);
        }
        delete node;
    }
}
bool Avl::check(Node *node){
    while(node->data != -1){
        int hh;
        if(node->left->h > node->right->h){
            hh = node->left->h + 1;
        }else{
            hh = node->right->h + 1;
        }
        if(node->bf >= 2 || node->bf <= -2){
            std::cout << node->data << "d ";
            return false;
        }else if(node->bf != node->left->h - node->right->h){
            std::cout << "a";
            return false;
        }else if(node->h != hh){
            std::cout << "b";
            return false;
        }else if((node->right->data!= -1 && node->data > node->right->data) || node->data < node->left->data){
            std::cout << "c";
            return false;
        }else{
            return check(node->left) && check(node->right);
        }
    }
    return true;
}
inline void Avl::connect(Node *parent,bool direction, Node *child){
    if(direction == true){
        parent->right = child;
    }else{
        parent->left = child;
    }
    child->parent = parent;
}
void Avl::level(Node *tmp){
    queue<Node*> q;
    ofstream ofs;
    ofs.open("out.txt");
    int n = 0;
    if(tmp!=NULL){
        q.push(tmp);
    }
    while(!q.empty()){
        if(q.front()!=NULL){
            if(q.front()->parent!=NULL){
                ofs << q.front()->data << "+" << q.front()->parent->data << " "; 
            }
            q.push(q.front()->left);
            q.push(q.front()->right);
        }
        q.pop();
    }
    ofs.close();
}
inline void Avl::setH(Node *node){
    if(node->data != -1){
        if(node->left->h > node->right->h){
            node->h = node->left->h + 1;
        }else{
            node->h = node->right->h + 1;
        }
    }else{
        node->h = 0;
    }
}
inline void Avl::setBF(Node *node){
    node->bf = node->left->h - node->right->h;
}
inline void Avl::becomeEx(Node *node){
    delete [] node->left;
    delete [] node->right;
    node->left = NULL;
    node->right = NULL;
    node->data = -1;
    node->h = 0;
}
bool Avl::insert(int a,Node *node){
    if(node->data == -1){
        n++;
        node->data = a;
        node->bf = 0;
        node->h = 1;
        node->left = new Node();
        node->right = new Node();
        node->left->data = -1;
        node->right->data = -1;
        node->left->h = 0;
        node->right->h = 0;
        node->right->parent = node;
        node->left->parent = node;
        return true;
    }else{
        if(node->data > a){
            insert(a,node->left);
        }else if(node->data < a){
            insert(a,node->right);
        }else{
            return false;
        }
        setBF(node);
        setH(node);
        if(node->bf == 2 || node->bf == -2){         
            balance(node);       
        }
        return true;
    }
}
void Avl::balance(Node *node){ 
    if(node->bf == 2){
        if(node->left->bf >= 0){
            LL(node);
        }else{
            LR(node);
        }
    }else{
        if(node->right->bf <= 0){
            RR(node);
        }else{
            RL(node);
        }
    }
}
void Avl::RR(Node *node){
    Node *parent = node->parent;
    Node *right = node->right;
    connect(node,true,right->left);
    connect(right,false,node);
    if(parent == NULL){
        start = right;
        right->parent = NULL;
    }else{
        connect(parent,parent->right == node,right);
    }
    setH(node);
    setH(right);
    setBF(node);
    setBF(right);
}
void Avl::LL(Node *node){
    Node *parent = node->parent;
    Node *left = node->left;
    connect(node,false,left->right);
    connect(left,true,node);
    if(parent == NULL){
        left->parent = NULL;
        start == left;
    }else{
        connect(parent,parent->right == node,left);
    }
    setH(node);
    setH(left);
    setBF(node);
    setBF(left);
}
void Avl::LR(Node *node){
    Node *parent = node->parent;
    Node *left = node->left;
    Node *left_right = node->left->right;
    connect(left,true,left_right->left);
    connect(node,false,left_right->right);
    connect(left_right,false,left);
    connect(left_right,true,node);
    if(parent == NULL){
        start = left_right;
        left_right->parent = NULL;
    }else{
        connect(parent,parent->right == node,left_right);
    } 
    setH(node);
    setH(left);
    setH(left_right);
    setBF(left);
    setBF(node);
    setBF(left_right);
}
void Avl::RL(Node *node){
    Node *parent = node->parent;
    Node *right = node->right;
    Node *right_left = node->right->left;
    connect(right,false,right_left->right);
    connect(node,true,right_left->left);
    connect(right_left,false,node);
    connect(right_left,true,right);
    if(parent == NULL){
        start = right_left;
        right_left->parent = NULL;
    }else{
        connect(parent,parent->right == node,right_left);
    }
    setH(node);
    setH(right);
    setH(right_left);
    setBF(right);
    setBF(node);
    setBF(right_left);
}
bool Avl::del(int a){
    Node *tmp = start;
    while(tmp->data != -1){
        if(a > tmp->data){
            tmp = tmp->right;
        }else if(a < tmp->data){
            tmp = tmp->left;
        }else{
            break;
        }
    }
    if(tmp->data == -1){
        return false;
    }
    n--;
    if(tmp->right->data == -1 && tmp->left->data == -1){
        if(tmp == start){
            start->data = -1;
            start->h = 0;
        }else{
            becomeEx(tmp);
            do{
                tmp = tmp->parent;
                setBF(tmp);
                setH(tmp);
                if(tmp->bf == 2 || tmp->bf == -2){          
                    balance(tmp);
                }
            }while(tmp->parent != NULL);
        }
    }else if(tmp->right->data != -1 && tmp->left->data != -1){
        Node *d_node = tmp;
        tmp = tmp->right;
        bool c = false;
        while (tmp->left->data != -1)
        {
            c = true;
            tmp = tmp->left;
        }
        d_node->data = tmp->data;
        connect(tmp->parent,!c,tmp->right);
        d_node = tmp;
        do{
            tmp = tmp->parent;
            setBF(tmp);
            setH(tmp);
            if(tmp->bf == 2 || tmp->bf == -2){              
                balance(tmp);  
            }
        }while(tmp->parent != NULL);
        delete [] d_node;
    }else{ 
        if(tmp == start){
            if(tmp->right->data == -1){
                start = tmp->left;                            
            }else{
                start = tmp->right;
            }
            start->parent = NULL; 
            delete [] tmp;
        }else{
            if(tmp->right->data == -1){
                connect(tmp->parent,tmp->parent->right == tmp,tmp->left);
            }else{
                connect(tmp->parent,tmp->parent->right == tmp,tmp->right);
            }
            Node *d_node = tmp;
            do{
                tmp = tmp->parent;
                setBF(tmp);
                setH(tmp);
                if(tmp->bf == 2 || tmp->bf == -2){          
                    balance(tmp); 
                }   
            }while(tmp->parent != NULL);
            delete [] d_node;
        }
    }
    return true;
}

int main(){
    ifstream ifs;
    ifs.open("in.txt");
    string input;
    Avl tree;
    int node;
    ifs >> input;
    ifs >> input;
    while(input != "quit"){
        ifs >> node;
        if(input == "insert"){
            tree.insert(node,tree.start); 
        }else if(input == "delete"){
            tree.del(node);
        }
        ifs >> input;
    }
    if(tree.check(tree.start)){
        cout << node << " true" << endl;
    }else{
        cout << node << " false" << endl;
    }
    tree.level(tree.start);
    delete [] tree.start;
    ifs.close();
    return 0;
}