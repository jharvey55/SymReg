#include <iostream>

#include <Node.h>
#include <Contender.h>
#include <Optimizers.h>


void test()
{
    std::cout << "Welcome to SymReg" << std::endl;
        Contender add_contender;
        
        int small_size = 4;
        Node* add_nodes = new Node[small_size];
        add_nodes[1] = Node(ADD);
        add_nodes[2] = Node(VAR);
        add_nodes[3] = Node(VAL, 2.0f);
        
        add_contender = Contender(small_size, add_nodes);
        // add_contender = Contender();

        // delete[] cos_nodes;
        delete[] add_nodes;

        std::cout << add_contender.EqParser(1, 3.0f) << std::endl;
}

void cosTest() {
    // Contender cos_contender;
    int trig_size = 4;
    Node* cos_nodes = new Node[trig_size];
    cos_nodes[1] = Node(COS);
    cos_nodes[2] = Node(VAR);
    Contender cos_contender = Contender(trig_size, cos_nodes);
    
    delete[] cos_nodes; 

    std::cout << cos_contender.EqParser(1, 0.0f) << std::endl;

}

void sinTest() {
    Contender sin_contender;
    int trig_size = 4;
    Node* sin_nodes = new Node[trig_size];
    sin_nodes[1] = Node(SIN);
    sin_nodes[2] = Node(VAR);
    sin_contender = Contender(trig_size, sin_nodes);
    delete[] sin_nodes; 

    // std::cout << "Still stable :D" << std::endl;
    std::cout << sin_contender.EqParser(1, 0.0f) << std::endl;
    // std::cout << "Less stable :D" << std::endl;
}

void stringTest() {
    Contender sin_contender;
    int trig_size = 4;
    Node* sin_nodes = new Node[trig_size];
    sin_nodes[1] = Node(SIN);
    sin_nodes[2] = Node(VAR);
    sin_contender = Contender(trig_size, sin_nodes);
    delete[] sin_nodes;

    std::cout << "getting eq\n";
    std::cout << sin_contender.getEqString() << std::endl;

    int big_size = 32;
    Node* big_nodes = new Node[big_size];
    big_nodes[1] = Node(DIV);
    big_nodes[2] = Node(SIN);
    big_nodes[3] = Node(COS);
    big_nodes[4] = Node(SUB);
    big_nodes[8] = Node(MLT);
    big_nodes[16] = Node(VAL, 2.0f);
    big_nodes[17] = Node(VAR);
    big_nodes[6] = Node(ADD);
    big_nodes[12] = Node(VAR);
    big_nodes[13] = Node(VAL, M_PI);
    Contender bigEq = Contender(big_size, big_nodes);
    delete[] big_nodes;

    std::cout << bigEq.getEqString() << std::endl;
}

int main()
{
//        sinTest();
        stringTest();

}

