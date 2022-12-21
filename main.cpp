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

//    DataLog::dot = true;
//    DataLog::diversity = true;
//    DataLog::num_gens = 10;

    std::function<void(std::vector<Contender> &)> randGen2 = [](
            std::vector<Contender> &population) {
        for (int i = 0; i < population.size(); i++) {
            population[i] = Contender();
            population[i].calcFitness();
        }
    };


    std::function<void(std::vector<Contender> &)> crossover = [&](
            std::vector<Contender> &population) {
        std::random_device rdev;
        std::mt19937 rng(rdev());

        std::uniform_real_distribution<double> rdist(0.0f, 100.0f);

        double low = 5.0f;
        double high = 75.0f;
        int cap = 48;
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


            double muteRate1 = Optimizers::interpolateMuteRate(low, high, population[i].getSize(), cap);
            if (rdist(rng) < muteRate1) {
                population[i].randMutate();
                population[i].calcFitness();
            }

            double muteRate2 = Optimizers::interpolateMuteRate(low, high, population[i].getSize(), cap);
            if (rdist(rng) < muteRate2) {
                population[i + 1].randMutate();
                population[i + 1].calcFitness();
            }
        }
    };

    Optimizers::OptLoop(dPath, oPath, "Cross", "params", 50'000, 100, crossover);

//    Optimizers::HFC(dPath, oPath, "HFC-Rand", "params", 50'000, 200, 4, 0.5, 50, crossover);

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


std::string GetString(const std::string &prompt) {
    std::string str;
    std::cout << prompt << std::endl;
    std::getline(std::cin, str);
    std::cout << "String: " << str << std::endl;
    if (str[str.length() - 1] == '\r')
        str.resize(str.length() - 1);

    return str;
}

int GetInt(const std::string &prompt) {
    int var;
    std::cout << prompt << std::endl;
    std::cin >> var;
    std::cin.ignore(1, '\n');

    return var;
}

char GetChar(const std::string &prompt) {
    char var;
    std::cout << prompt << std::endl;
    std::cin >> var;
    std::cin.ignore(1, '\n');

    return var;
}

double GetDouble(const std::string &prompt) {
    double var;
    std::cout << prompt << std::endl;
    std::cin >> var;
    std::cin.ignore(1, '\n');

    return var;
}

void Experiment() {

    std::string params = "";
    std::function<void(std::vector<Contender> &)> generator;

    std::string dPath = GetString("Dataset Path:");
    std::cout << dPath << std::endl;
    std::cout << (int) dPath[dPath.length() - 1] << std::endl;

    // Read in oPath
    std::string oPath = GetString("Datalog Path:");
    std::cout << oPath << std::endl;
    std::cout << (int) oPath[oPath.length() - 1] << std::endl;

    char do_dot = GetChar("Create dot log(y/n)?");
    DataLog::dot = do_dot == 'y';
    std::cout << do_dot << std::endl;
    params += "DotLog:" + std::to_string(do_dot);


    char do_div = GetChar("Create diversity log(y/n)?");
    DataLog::diversity = do_div == 'y';
    std::cout << do_div << std::endl;
    params += " DivLog:" + std::to_string(do_div);

    if (DataLog::diversity) {
        // Get number of evaluations to runa
        int div_gens = GetInt("Diversity log frequency");
        DataLog::num_gens = div_gens;
        params += " DivFreq:" + std::to_string(div_gens);
    }

    // Get number of evaluations to runa
    int max_evals = GetInt("Num Evals:");
    params += " Evals:" + std::to_string(max_evals);

    // Get population size
    int pop_size = GetInt("Population size:");
    params += " Pop:" + std::to_string(pop_size);

    // Method selection
    std::string method = GetString("Method Selection:");

    if (method == "Cross") {


        double low = 5.0f;
        double high = 75.0f;
        int cap = 48;

        generator = [&](std::vector<Contender> &population) {
            std::random_device rdev;
            std::mt19937 rng(rdev());

            std::uniform_real_distribution<double> rdist(0.0f, 100.0f);


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

                double muteRate1 = Optimizers::interpolateMuteRate(low, high, population[i].getSize(), cap);
                if (rdist(rng) < muteRate1) {
                    population[i].randMutate();
                    population[i].calcFitness();
                }

                double muteRate2 = Optimizers::interpolateMuteRate(low, high, population[i].getSize(), cap);
                if (rdist(rng) < muteRate2) {
                    population[i + 1].randMutate();
                    population[i + 1].calcFitness();
                }
            }
        };
    } else if (method == "RMHC") {

    } else if (method == "Random") {
        generator = [](std::vector<Contender> &population) {
            for (int i = 0; i < population.size(); i++) {
                population[i] = Contender();
                population[i].calcFitness();
            }
        };
    } else {
        std::cout << "Invalid method" << std::endl;
        return;
    }

    // Method selection
    std::string loop = GetString("Loop Selection:");

    method = loop + "-" + method;

    if (loop == "HFC") {
        double grad_percent;
        std::cout << "Graduation Percent:\n";
        std::cin >> grad_percent;
        std::cin.ignore(1, '\n');
        params += " GradPercent:" + std::to_string(grad_percent);

        int num_tiers;
        std::cout << "Number of num_tiers:\n";
        std::cin >> num_tiers;
        std::cin.ignore(1, '\n');
        params += " Tier:" + std::to_string(num_tiers);

        int num_gens;
        std::cout << "Generations between graduations:\n";
        std::cin >> num_gens;
        std::cin.ignore(1, '\n');
        params += " GradGen:" + std::to_string(num_gens);

        Optimizers::HFC(dPath, oPath, method, params, max_evals, pop_size, num_tiers, grad_percent, num_gens,
                        generator);
    } else if (loop == "BGA") {
        Optimizers::OptLoop(dPath, oPath, method, params, max_evals, pop_size, generator);
    } else {
        std::cout << "Invalid loop chosen" << std::endl;
        return;
    }


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
//    hfcTest();
    Experiment();
//    std::cout << Optimizers::interpolateMuteRate(0.0f, 10.0f, 32, 64) << std::endl;
//    std::cout << Optimizers::interpolateMuteRate(0.0f, 10.0f, 48, 64) << std::endl;
//    std::cout << Optimizers::interpolateMuteRate(0.0f, 10.0f, 16, 64) << std::endl;



//std::vector<std::vector<Point>> test;
//
//test.emplace_back();
////std::cout << test[0][0].x << std::endl;
//std::cout << test.size() << std::endl;
//test[0].push_back(Point(4.0, 2.0));
//std::cout << test[0][0].x << std::endl;

    return 0;
}

