#include <iostream>
#include <string>
#include <queue>
#include <fstream>

using namespace std;
ofstream ofs;

//node of linklist
struct Node{
    int data;
    Node *left;
    Node *right;
};

class Bst{
    private:
        Node *start;
        void prefix(Node *tmp);
        void infix(Node *tmp);
        void postfix(Node *tmp);
        void level(Node *tmp);
    public:
        Bst();
        bool insert(int a);
        bool del(int a);
        bool search(int a);
        void pri();
};
Bst::Bst(){
    start = NULL;
}
bool Bst::insert(int a){
    if(start == NULL){
        //first node
        start = new Node();
        start->data = a;
        start->left = NULL;
        start->right = NULL;
    }else{
        Node *tmp = start;
        while(tmp!=NULL){
            if(a > tmp->data){
                if(tmp ->right!=NULL){
                    tmp = tmp->right;
                }else{
                    //insert a
                    tmp->right = new Node();
                    tmp = tmp->right;
                    tmp->data = a;
                    tmp->left = NULL;
                    tmp->right = NULL;
                    break;
                }
            }else if(a < tmp->data){
                if(tmp ->left!=NULL){
                    tmp = tmp->left;
                }else{
                    //inseart a
                    tmp->left = new Node();
                    tmp = tmp->left;
                    tmp->data = a;
                    tmp->left = NULL;
                    tmp->right = NULL;
                    break;
                }
            }else{
                //a == tmp->data
                //a exites
                return false;
            }
        }
    }
    return true;
}
bool Bst::search(int a){
    Node *tmp = start;
    while(tmp!=NULL){
        if(a > tmp->data){
            tmp = tmp->right;
        }else if(a < tmp->data){
            tmp = tmp->left;
        }else{
            //a == tmp->data
            return true;
        }
    }
    return false;
}
bool Bst::del(int a){
    Node *tmp = start;
    Node *last = tmp;//last one of tmp
    while(tmp!=NULL){
        if(a > tmp->data){
            last = tmp;
            tmp = tmp->right;
        }else if(a < tmp->data){
            last = tmp;
            tmp = tmp->left;
        }else{
            //a == tmp->data
            break;
        }
    }
    if(tmp == NULL){
        //a is not found
        return false;
    }
    if(tmp->right == NULL && tmp->left == NULL){
        //a is a leaf
        if(tmp == start){
            delete [] tmp;
            start = NULL;
        }else{
            if(last->right == tmp){
                last->right = NULL;
            }else{
                last->left = NULL;
            }
            delete [] tmp;
        }
        
    }else if(tmp->right != NULL && tmp->left != NULL){
        //a has 2 child
        Node *d_node = tmp;
        last = tmp;
        //find inorder succeser
        tmp = tmp->right;
        bool c = false;
        while (tmp->left!=NULL)
        {
            c = true;
            last = tmp;
            tmp = tmp->left;
        }
        d_node->data = tmp->data;
        if(c){
            last->left = tmp->right;
        }else{
            last->right = tmp->right;
        }
        delete [] tmp;
    }else{
        //a has 1 child
        if(tmp == start){
            if(tmp->right == NULL){
                start = tmp->left;        
            }else{
                start = tmp->right;
            }
        }else{
            if(tmp->right == NULL){
                if(last->right == tmp){
                    last->right = tmp->left;
                }else{
                    last->left = tmp->left;
                }
        
            }else{
                if(last->right == tmp){
                    last->right = tmp->right;
                }else{
                    last->left = tmp->right;
                }
            }
        }
        delete [] tmp;
    }
    return true;
}
void Bst::pri(){
    std::cout << "The tree in prefix order: ";
    ofs << "The tree in prefix order: ";
    prefix(start);
    ofs << endl;
    std::cout << endl;
    std::cout << "The tree in infix order: ";
    ofs << "The tree in infix order: ";
    infix(start);
    ofs << endl;
    std::cout << endl;
    std::cout << "The tree in post order: ";
    ofs << "The tree in post order: ";
    postfix(start);
    ofs << endl;
    std::cout << endl;
    std::cout << "The tree in level order: ";
    ofs << "The tree in level order: ";
    level(start);
    ofs << endl;
    std::cout << endl;
}
void Bst::prefix(Node *tmp){
    if(tmp!=NULL){
        std::cout << tmp->data << " ";
        ofs << tmp->data << " ";
        prefix(tmp->left);
        prefix(tmp->right);
    }
}
void Bst::postfix(Node *tmp){
    if(tmp!=NULL){
        postfix(tmp->left);
        postfix(tmp->right);
        std::cout << tmp->data << " ";
        ofs << tmp->data << " ";
    }
}
void Bst::infix(Node *tmp){
    if(tmp!=NULL){
        infix(tmp->left);
        std::cout << tmp->data << " ";
        ofs << tmp->data << " ";
        infix(tmp->right);
    }
}
void Bst::level(Node *tmp){
    queue<Node*> q;
    if(tmp!=NULL){
        q.push(tmp);
    }
    while(!q.empty()){
        if(q.front()!=NULL){
            std::cout << q.front()->data << " ";
            ofs << q.front()->data << " ";
            q.push(q.front()->left);
            q.push(q.front()->right);
        }
        q.pop();
    }
}
int main(){
    std::cout << "Enter file name: ";
    string name;
    ifstream ifs;
    std::cin >> name;
    ifs.open(name);
    ofs.open("output.txt");
    ofs << "File name: " << name << endl << endl;;
    
    std::cout << endl;
    std::cout << "(I)nsert a number.\n";
    std::cout << "(D)elete a number.\n";
    std::cout << "(S)earch a number.\n";
    std::cout << "(P)rint 4 kinds of orders.\n";
    std::cout << "(E)xit\n" << endl;
    ofs << "(I)nsert a number.\n";
    ofs << "(D)elete a number.\n";
    ofs << "(S)earch a number.\n";
    ofs << "(P)rint 4 kinds of orders.\n";
    ofs << "(E)xit\n" << endl;
    
    Bst tree;
    char c;
    ifs >> c;
    while(c!='e' && c!='E'){
        //choose operation
        switch (c){
            int n;
            case 'i':
            case 'I':
            std::cout << "Insert:\n";
            ofs << "Insert:\n";
                ifs >> n;
                while(n!=-1){
                    if(tree.insert(n)){
                        std::cout << "Number " << n << " is inserted." << endl;
                        ofs << "Number " << n << " is inserted." << endl;
                    }else{
                        ofs << "Error! Number " << n << " exists." << endl;
                        std::cout << "Error! Number " << n << " exists." << endl;
                    }
                    ifs >> n;
                }
                break;
            case 'd':
            case 'D':
                std::cout << "Delete:\n";
                ofs << "Delete:\n";
                ifs >> n;
                while(n!=-1){
                    if(tree.del(n)){
                        std::cout << "Number " << n << " is deleted." << endl;
                        ofs << "Number " << n << " is deleted." << endl;
                    }else{
                        ofs << "Number " << n << " is not exists." << endl;
                        std::cout << "Number " << n << " is not exists." << endl;
                    }
                    ifs >> n;
                }
                break;
            case 's':
            case 'S':
                std::cout << "Search:\n";
                ofs << "Search:\n";
                ifs >> n;
                while(n!=-1){
                    if(tree.search(n)){
                        std::cout << "Bingo! " << n << " is found." << endl;
                        ofs << "Bingo! " << n << " is found." << endl;
                    }else{
                        ofs << "Sorry! " << n << " is not found." << endl;
                        std::cout << "Sorry! " << n << " is not found." << endl;
                    }
                    ifs >> n;
                }
                break;
            case 'p':
            case 'P':
                std::cout << "Print:\n";
                ofs << "Print:\n";
                tree.pri();
                break;
            default:
                break;
        }
        std::cout << endl;
        std::cout << "(I)nsert a number.\n";
        std::cout << "(D)elete a number.\n";
        std::cout << "(S)earch a number.\n";
        std::cout << "(P)rint 4 kinds of orders.\n";
        std::cout << "(E)xit\n" << endl;
        ofs << endl;
        ofs << "(I)nsert a number.\n";
        ofs << "(D)elete a number.\n";
        ofs << "(S)earch a number.\n";
        ofs << "(P)rint 4 kinds of orders.\n";
        ofs << "(E)xit\n" << endl;
        ifs >> c;
    }
    std::cout << "Exit\n";
    ofs << "Exit\n";
    ofs.close();
    ifs.close();
    return 0;
}