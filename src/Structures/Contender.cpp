//
// Created by atlas1323 on 6/25/2022.
//

#include <Contender.h>
#include <Node.h>
#include <Point.h>

#include <cmath>
#include <functional>
#include <iostream>
#include <random>

// ################################################################################
// Static member variable initialization (where feasible)
// ################################################################################

int Contender::evaluations_ = 0;

std::random_device Contender::rand_dev_;
std::mt19937 Contender::rng_(Contender::rand_dev_());
std::uniform_int_distribution<int> Contender::coin_flip_(0, 1);

// ################################################################################
// Constructors and Destructor
// ################################################################################

/**
 * @brief Construct a new Contender::Contender object
 * 
 */
Contender::Contender() {
    size_ = 2;
    nodes_ = new Node[size_];
    randy(1);
    fitness_ = 0;

    // TODO: Make eq string
    // TODO: Calc fitness
}

/**
 * @brief Construct a new Contender:: Contender object
 * 
 * @param size size of node array
 * @param nodes node array to fill new contender
 */
Contender::Contender(const int& size, const Node *nodes) {
    // delete[] nodes_;
    size_ = size;
    nodes_ = new Node[size_];
    // for(int i = 0; i < size; i++)
    //     nodes_[i] = nodes[i];
    std::copy(nodes, nodes + size, this->nodes_);

}


/**
 * @brief Copy Constructor: Construct a new Contender::Contender object
 * 
 * @param that Contender to copy
 */
Contender::Contender(const Contender& that) {   
    this->size_ = that.size_;
    this->fitness_ = that.fitness_;
    this->nodes_ = new Node[that.size_];
    // for(int i = 0; i < that.size_; i++)
    //     this->nodes_[i] = that.nodes_[i];
    std::copy(that.nodes_, that.nodes_ + that.size_, this->nodes_);
    
}

Contender::Contender(Contender&& that) noexcept {
    this->size_ = that.size_;
    that.size_ = 0;
    this->fitness_ = that.fitness_;
    that.fitness_ = 0;
    this->nodes_ = that.nodes_;
    that.nodes_ = nullptr;
}

Contender::~Contender() {
    delete[] nodes_;
}

// ################################################################################
// Getters and setters
// ################################################################################

int Contender::getSize() const {
    return size_;
}

void Contender::setSize(int size) {
    size_ = size;
}

Node *Contender::getNodes() const {
    return nodes_;
}

void Contender::setNodes(Node *nodes) {
    nodes_ = nodes;
}

void Contender::setNode(Node& node, int index) {
    nodes_[index] = node;
}

std::string Contender::getEqString() {
    std::string equation = buildEqString_(1);

    return equation;
}

double Contender::getFitness() const {
    return fitness_;
}

std::string Contender::LogString() {
    std::string log = "";

    return log;
}

// ################################################################################
// Member functions
// ################################################################################

static double epsilon = 4.94065645841247e-324;


/**
 *
 * @param index
 * @param x
 * @return
 */
double Contender::EqParser(int index, const double& x) {
    switch (nodes_[index].key) {
        case VAR :
            return x;
        case VAL :
            return nodes_[index].value;
        case ADD :
            return EqParser(2 * index, x) + EqParser(2 * index + 1, x);
        case SUB :
            return EqParser(2 * index, x) - EqParser(2 * index + 1, x);
        case MLT :
            return EqParser(2 * index, x) * EqParser(2 * index + 1, x);
        case DIV : {
            // safe divide
            double divisor = EqParser(2*index + 1, x);
            return EqParser(2 * index, x) / (divisor ? divisor : epsilon);
        }
        case COS :
            return cos(EqParser(2 * index, x));
        case SIN :
            return sin(EqParser(2 * index, x));
        default :
            return nan("0.0");
    }
}

// std::function<double (double)> Contender::parseFun(int index)
// {
//     switch (nodes_[index].key) {
//         case VAR :
//             return [](double x){return x};
//         case VAL :
//             return nodes_[index].value;
//             return [](){return nodes_[index].value};
//         case ADD :
//             return EqParser(2 * index, x) + EqParser(2 * index + 1, x);
//         case SUB :
//             return EqParser(2 * index, x) - EqParser(2 * index + 1, x);
//         case MLT :
//             return EqParser(2 * index, x) * EqParser(2 * index + 1, x);
//         case DIV :
//             return EqParser(2 * index, x) / EqParser(2 * index + 1, x);
//         case COS :
//             return cos(EqParser(2 * index, x));
//         case SIN :
//             return sin(EqParser(2 * index, x));
//         default :
//             return 0;
//     }
// }


/**
 * \brief Grows the heap!!!!
 * @brief Grows the heap
 * @param depth
 */
void Contender::growHeap() {
    // int temp_size = growthSize_(depth);
    int temp_size = size_*2;
    // Create new array
    Node* temp_nodes = new Node[temp_size];

    // Copy old items to new array
    std::copy(nodes_, nodes_ + size_, temp_nodes);
    // for(int i = 0; i < size_; i++)
    //     temp_nodes[i] = nodes_[i];

    size_ = temp_size;
    delete[] nodes_;
    nodes_ = temp_nodes;
    temp_nodes = nullptr;
    delete[] temp_nodes;
}


void Contender::randy(int index) {

    // Guard rail to keep variable from growing too large
    if (size_ >= 64 && index > 15)
    {
        if(coin_flip_(rng_))
            nodes_[index] = Node(VAR);
        else
            nodes_[index] = Node(VAL);
    }

    else {
        nodes_[index] = Node();
        
        // Check if node is terminus, move forward if not terminus
        if(nodes_[index].key != VAR && nodes_[index].key != VAL) {
            int l_child = 2*index;
            
            if(l_child >= size_) {
                growHeap(); // If not big enough, add next layer of depth

            }
            randy(l_child); // Recursively call for left child

            // CHeck if node has 2 children, continue if true
            if(nodes_[index].key != COS && nodes_[index].key != SIN) {
                // Guard for dividing by zero
                randy(l_child+1); // Recursively call for right child
            }
        }
    }

    
}


/**
 * @brief Updates the fitness of a contender
 * Calculates the rms of the contenders equation vs a test dataset (data)
 * 
 * @param data point array holding the data to test
 * @param num_points int representing the number of points in the dataset
 */
void Contender::calcFitness(const Point * data, int num_points) {
    double sum = 0.0f;
    double diff;
    for(int i = 0; i < num_points; i++) {
        diff = data[i].y - EqParser(1, data[i].x);
        sum += std::pow(diff, 2);
    }

    // Assign the rms to fitness
    fitness_ = std::sqrt(sum/num_points);
}

// ################################################################################
// Overloaded operators
// ################################################################################

/**
 * @brief Comparison operator: based on fitness
 * @param that
 * @return
 */
bool Contender::operator<(const Contender& that) {
    return this->fitness_ < that.fitness_;
}

/**
 * @brief Copy Assignment
 * 
 * @param that 
 * @return Contender& 
 */
Contender& Contender::operator=(const Contender& that) {
    if (this != &that) {
        delete[] this->nodes_;

        this->size_ = that.size_;
        this->fitness_ = that.fitness_;

        if (that.size_ > 0) {
            this->nodes_ = new Node[that.size_];
            // for(int i = 0; i < that.size_; i++)
            //     this->nodes_[i] = that.nodes_[i];
            std::copy(that.nodes_, that.nodes_ + that.size_, this->nodes_);
        }
        else {
            this->nodes_ = nullptr;
        }
    }
    return *this;
}

/**
 * @brief 
 * 
 * @param that 
 * @return Contender& 
 */
Contender& Contender::operator=(Contender&& that) noexcept{
    if (this != &that) {
        delete[] this->nodes_;
        this->nodes_ = that.nodes_;

        this->fitness_ = that.fitness_;
        this->size_ = that.size_;

        that.fitness_ = 0;
        that.size_ = 0;
        that.nodes_ = nullptr;
    }

    return *this;
}

// ################################################################################
// Static Member functions
// ################################################################################
/**
 * @brief finds the new size of the heap
 * @param depth
 * @return
 */
int Contender::growthSize_(const int& depth)
{
    return 2^depth;
}

std::string Contender::buildEqString_(int index) {
    switch (nodes_[index].key) {
        case VAR :
            return "x";
        case VAL :
            return std::to_string(nodes_[index].value);
        case ADD :
            return buildEqString_(2 * index) + " + " + buildEqString_(2 * index + 1);
        case SUB :
            return buildEqString_(2 * index) + " - " + buildEqString_(2 * index + 1);
        case MLT : {
            int left_node = 2 * index;
            int right_node = 2*index+1;
            std::string temp;

            if (nodes_[left_node].key == ADD || nodes_[left_node].key == SUB)
                temp += "(" + buildEqString_(left_node) + ")" ;
            else
                temp += buildEqString_(left_node);
            temp += "∙";
            if (nodes_[right_node].key == ADD || nodes_[right_node].key == SUB)
                temp += "(" + buildEqString_(right_node) + ")" ;
            else
                temp += buildEqString_(right_node);
            return temp;
        }
        case DIV : {
            int left_node = 2 * index;
            int right_node = 2*index+1;
            std::string temp;

            if (nodes_[left_node].key == ADD || nodes_[left_node].key == SUB)
                temp += "(" + buildEqString_(left_node) + ")" ;
            else
                temp += buildEqString_(left_node);
            temp += "/";
            if (nodes_[right_node].key == ADD || nodes_[right_node].key == SUB)
                temp += "(" + buildEqString_(right_node) + ")" ;
            else
                temp += buildEqString_(right_node);
            return temp;
        }
        case COS :
            return "cos(" + buildEqString_(2 * index) + ")";
        case SIN :
            return "sin(" + buildEqString_(2 * index) + ")";
        default :
            return "nan";
    }
}





