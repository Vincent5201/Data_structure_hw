how to use:
    just enter a proper file's file name

struct: Node
    it is used do implement linklist

class: Bst
    means Binary Search Tree, ans has a Node start to record the root of the tree
    private:
        Node *start
            root of tree
        void prefix(Node *tmp)
            print prefix order of "tmp"
        void infix(Node *tmp)
            print infix order of "tmp"
        void postfix(Node *tmp)
            print postfix order of "tmp"
        void level(Node *tmp)
            print level order of "tmp"
    public:
        Bst()
            initialize
        bool insert(int a)
            return whether you repeated insert int "a" or not ans insert int "a" into tree 
        bool del(int a)
            return whether int "a" is in tree or not and delete int "a" in tree 
        bool search(int a)
            return whether int "a" is in tree or not
        void pri()
            print the prefix, infix, postfix, and level order of the tree