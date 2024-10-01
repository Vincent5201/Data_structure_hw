prim.cpp:
    introduece:
        use a 2-dimention vector(imitate linklist) to represent graph and implememt Prim's algorithm

    how to use:
        just enter a proper file's file name

    code:
        struct node:
            used to implememt graph
            char node;
                node name
            int w;
                node weight
                example:
                    if w is head_node, w = -1, 
                    if w is empty, w = -2,
                    else w means weight between it and its head_node
    
        class Graph:
            int size;
                amount of node
            vector<vector<struct node>> data;
                implememt graph's conection
                example:
                    {head_node_1, node linked with head_node_1...},
                    {head_node_2, node linked with head_node_2...},
                    {head_node_3, node linked with head_node_3...},
                    {head_node_4, node linked with head_node_4...},
                    {head_node_5, node linked with head_node_5...},
                    {empty head_node}
            Graph(int n);
                initialize
            void insert(char a,char b, int we);
                insert an edge an its weight
            void insert();
                insert an empty node to represent end

        void swapC(char *a, char *b);
        void swapI(int *a, int *b);
            use to swap two char and two int;

dijkstra.cpp:
    introduece:
        use a adjmatrix to store data, represent graph and implememt Dijkstra’s algorithm

    how to use:
        just enter a proper file's file name

    code:
        int main():
            int data[][]:
                adjmatrix to store data, represent graph
            int length[]:
                used to implememt Dijkstra’s algorithm

    