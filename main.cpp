#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cmath>
#include <ctime>
#include <random>
#include <stdio.h>
#include <random>
#include <set>

#include <Node.h>
#include <Point.h>
#include "Contender.h"
#include <Optimizers.h>


void test() {
    std::cout << "Welcome to SymReg" << std::endl;
    Contender add_contender;

    int small_size = 4;
    Node *add_nodes = new Node[small_size];
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
    Node *cos_nodes = new Node[trig_size];
    cos_nodes[1] = Node(COS);
    cos_nodes[2] = Node(VAR);
    Contender cos_contender = Contender(trig_size, cos_nodes);

    delete[] cos_nodes;

    std::cout << cos_contender.EqParser(1, 0.0f) << std::endl;

}

void sinTest() {
    Contender sin_contender;
    int trig_size = 4;
    Node *sin_nodes = new Node[trig_size];
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
    Node *sin_nodes = new Node[trig_size];
    sin_nodes[1] = Node(SIN);
    sin_nodes[2] = Node(VAR);
    sin_contender = Contender(trig_size, sin_nodes);
    delete[] sin_nodes;

    std::cout << "getting eq\n";
    std::cout << sin_contender.getEqString() << std::endl;

    int big_size = 32;
    Node *big_nodes = new Node[big_size];
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

void stringTest2() {
    for (int i = 0; i < 5; i++) {
        Contender temp = Contender();
        std::cout << temp.getEqString() << std::endl;
    }

}

void loopTest1() {
    std::string rPath = "./resources/";
    std::string dPath = rPath + "datasets/data.txt";
    std::string oPath = rPath + "out/";

    std::function<std::vector<Contender>(std::vector<Contender>)> randGen = [](
            const std::vector<Contender> &population) {
        std::vector<Contender> temp;
        for (int i = 0; i < population.size(); i++) {
            temp.emplace_back();
            temp[i].calcFitness();
        }
        return temp;
    };

    std::function<void(std::vector<Contender> &)> randGen2 = [](
            std::vector<Contender> &population) {
        for (int i = 0; i < population.size(); i++) {
            population[i] = Contender();
            population[i].calcFitness();
        }
    };

    Optimizers::OptLoop(dPath, oPath, "Random", "params", 50'000, 100, randGen2);
    Optimizers::OptLoop(dPath, oPath, "Random", "params", 50'000, 100, randGen);

}

void loopTest2() {
    std::string rPath = "./resources/";
    std::string dPath = rPath + "datasets/data.txt";
    std::string oPath = rPath + "out/";
    int max_evals = 500'000;
    int pop_size = 500;

    std::function<std::vector<Contender>(std::vector<Contender>)> mutGen = [](
            const std::vector<Contender> &population) {
//        std::cout << Contender::getEvalCount() << std::endl;
        std::vector<Contender> output;
        int max = (int) population.size();
        int cutoff = (int) (0.95 * population.size());
        for (int i = 0; i < max; ++i) {
            if (i < cutoff) {
                Contender temp = population[i];
                temp.randMutate();
                temp.calcFitness();
                output.push_back(population[i] < temp ? population[i] : temp);
            } else {
                output.emplace_back();
                output[i].calcFitness();
            }
        }
        return output;
    };
    Optimizers::OptLoop(dPath, oPath, "RMHC", "params", max_evals, pop_size, mutGen);

}

void loopTest3() {
    std::string rPath = "./resources/";
    std::string dPath = rPath + "datasets/data.txt";
    std::string oPath = rPath + "out/";
    int max_evals = 100'000;
    int pop_size = 100;

    std::function<std::vector<Contender>(std::vector<Contender>)> mutGen = [](
            const std::vector<Contender> &population) {
//        std::cout << Contender::getEvalCount() << std::endl;
        std::vector<Contender> output;
        int max = (int) population.size();
        int cutoff = (int) (0.95 * population.size());
        for (int i = 0; i < max; ++i) {
            if (i < cutoff) {
                Contender temp = population[i];
                temp.randMutate();
                temp.calcFitness();
                output.push_back(population[i] < temp ? population[i] : temp);
            } else {
                output.emplace_back();
                output[i].calcFitness();
            }
        }
        return output;
    };

    std::function<std::vector<Contender>(std::vector<Contender>)> mutGen2 = [](
            const std::vector<Contender> &population) {
//        std::cout << Contender::getEvalCount() << std::endl;
        std::vector<Contender> output;
        int max = (int) population.size();
        int cutoff = (int) (0.2 * (double) population.size());
        for (int i = 0; i < max; ++i) {
            if (i < cutoff) {
                output.push_back(population[i]);
            } else {
                int index = i % cutoff;
//                std::cout << i << " : " << index << std::endl;
                Contender temp = population[index];
                temp.randMutate();
                temp.calcFitness();
                output.push_back(temp);
            }
        }
        return output;
    };

    std::function<std::vector<Contender>(std::vector<Contender>)> randGen = [](
            const std::vector<Contender> &population) {
        std::vector<Contender> temp;
        for (int i = 0; i < population.size(); i++) {
            temp.emplace_back();
            temp[i].calcFitness();
        }
        return temp;
    };


    int runs = 3;
    double ranAvg = 0.0f;
    double mutAvg = 0.0f;
    for (int i = 0; i < runs; i++) {
        std::cout << "Round: " << i << std::endl;
        ranAvg +=
                Optimizers::OptLoopRun(dPath, oPath, "Random", "params", max_evals, pop_size, randGen) / (double) runs;
        mutAvg += Optimizers::OptLoopRun(dPath, oPath, "RMHC", "params", max_evals, pop_size, mutGen) / (double) runs;
        std::cout << "\n" << std::endl;
    }

    std::cout << "Random: " << ranAvg << std::endl;
    std::cout << "Mutate: " << mutAvg << std::endl;

}

void CrossTest() {
    std::string rPath = "./resources/";
    std::string dPath = rPath + "datasets/data.txt";
    std::string oPath = rPath + "out/";

    std::function<void(std::vector<Contender> &)> crossover = [&](
            std::vector<Contender> &population) {
        std::random_device rdev;
        std::mt19937 rng(rdev());

        std::uniform_real_distribution<double> rdist(0.0f, 100.0f);

        double muteRate = 5.0f;
        int cutoff = (int) (0.5 * (double) population.size());
        int restPoint = (int) (0.95 * (double) population.size());
        double sum_fitness = 0.0f;
        for (int i = 0; i < cutoff; i++) {
            sum_fitness += 1.0f / population[i].getFitness();
        }

        for (int i = cutoff; i < restPoint; i += 2) {
//            std::cout << i << std::endl;
            int index1 = Contender::ProportionalSelection(population, sum_fitness);
            int index2 = index1;
            while (index2 == index1) { index2 = Contender::ProportionalSelection(population, sum_fitness); }
            Contender::RandCrossover(population[index1], population[index2], population[i], population[i + 1]);
//            if(rdist(rng) < muteRate){
//                population[i].randMutate();
//                population[i].calcFitness();
//                population[i+1].randMutate();
//                population[i+1].calcFitness();
//            }

        }

        for (int i = restPoint; i < (int) population.size() - 1; i++) {
            population[i] = Contender();
            population[i].calcFitness();
        }
    };

    Optimizers::OptLoop(dPath, oPath, "Cross", "params", 3'000'000, 500, crossover);

}

void hfcTest() {
    std::string rPath = "./resources/";
    std::string dPath = rPath + "datasets/data.txt";
    std::string oPath = rPath + "out/";

    std::function<void(std::vector<Contender> &)> crossover = [&](
            std::vector<Contender> &population) {
        std::random_device rdev;
        std::mt19937 rng(rdev());

        std::uniform_real_distribution<double> rdist(0.0f, 100.0f);

        double muteRate = 15.0f;
        int cutoff = (int) (0.5 * (double) population.size());
        int restPoint = (int) (0.95 * (double) population.size());
        double sum_fitness = 0.0f;
        for (int i = 0; i < cutoff; i++) {
//            sum_fitness += 1.0f/((double)(population[i].getSize())*0.01 + population[i].getFitness());
            sum_fitness += 1.0f / population[i].getFitness();

        }

        for (int i = cutoff; i < restPoint; i += 2) {
//            std::cout << i << std::endl;
            int index1 = Contender::ProportionalSelection(population, sum_fitness);
            int index2 = index1;
            while (index2 == index1) { index2 = Contender::ProportionalSelection(population, sum_fitness); }
            Contender::RandCrossover(population[index1], population[index2], population[i], population[i + 1]);
            if (rdist(rng) < muteRate) {
                population[i].randMutate();
                population[i].calcFitness();
                population[i + 1].randMutate();
                population[i + 1].calcFitness();
            }

        }
    };

//    Optimizers::OptLoop(dPath, oPath, "Cross", "params", 3'000'000, 500, crossover);

    Optimizers::HFC(dPath, oPath, "HFC-Cross", "params", 500'000, 500, 4, 0.5, 50, crossover);
}

void mutation() {
    int big_size = 32;
    Node *big_nodes = new Node[big_size];
    big_nodes[1] = Node(DIV);
    big_nodes[2] = Node(SIN);
    big_nodes[3] = Node(COS);
    big_nodes[4] = Node(SUB);
    big_nodes[8] = Node(MLT);
    big_nodes[16] = Node(VAL, 2.0f);
    big_nodes[17] = Node(VAR);
    big_nodes[9] = Node(VAL, 1.0f);
    big_nodes[6] = Node(ADD);
    big_nodes[12] = Node(VAR);
    big_nodes[13] = Node(VAL, M_PI);
    Contender bigEq = Contender(big_size, big_nodes);
    std::cout << bigEq.getSize() << std::endl;
    bigEq.treePrint();
//    bigEq.treePrint();
    bigEq.Mutate(16, SUB);
    bigEq.treePrint();

    std::cout << "Mut-again" << std::endl;

    bigEq.Mutate(16, ADD);
    std::cout << "DONE" << std::endl;
    std::cout << bigEq.getSize() << std::endl;
//    for(int i = 0; i < bigEq.getSize(); i++) {
//        std::cout << i << ": " << bigEq.getNode(i).nodeString(i) << std::endl;
//    }

    bigEq.treePrint();
}

int main() {
//        sinTest();
//        stringTest();
//        std::cout << "\n\n";
//        stringTest2();

//    loopTest1();
//    mutation();
//    loopTest1();
//    loopTest2();
//    loopTest3();
//    CrossTest()
    hfcTest();


//std::vector<std::vector<Point>> test;
//
//test.emplace_back();
////std::cout << test[0][0].x << std::endl;
//std::cout << test.size() << std::endl;
//test[0].push_back(Point(4.0, 2.0));
//std::cout << test[0][0].x << std::endl;

    return 0;
}

