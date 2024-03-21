#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <random>
#include <set>

#include <Node.h>
#include "Contender.h"
#include <Optimizers.h>


std::string GetString(const std::string &prompt) {
    std::string str;
    std::cout << prompt << std::endl;
    std::getline(std::cin, str);
    if (str.empty())
        std::getline(std::cin, str);
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

    // Get number of evaluations to runa
    int max_evals = GetInt("Num Evals:");
    std::cout << max_evals << std::endl;
    params += " Evals:" + std::to_string(max_evals);

    // Get population size
    int pop_size = GetInt("Population size:");
    std::cout << pop_size << std::endl;
    params += " Pop:" + std::to_string(pop_size);



    // Method selection
    std::string method = GetString("Method Selection:");
    std::cout << method << std::endl;

    if (method == "Cross") {

        generator = [&](std::vector<Contender> &population) {
            double low = 5.0f;
            double high = 99.9f;
            std::random_device rdev;
            std::mt19937 rng(rdev());

            std::uniform_real_distribution<double> rdist(0.0f, 100.0f);


            int cutoff = (int) (0.5 * (double) population.size());
            int restPoint = (int) (0.95 * (double) population.size());
            double sum_fitness = 0.0f;
            for (int i = 0; i < cutoff; i++) {
                sum_fitness += 1.0f / population[i].getFitness();
            }

            for (int i = cutoff; i < restPoint; i += 2) {
                int index1 = Contender::ProportionalSelection(population, sum_fitness);
                int index2 = index1;
                while (index2 == index1) { index2 = Contender::ProportionalSelection(population, sum_fitness); }
                Contender::RandCrossover(population[index1], population[index2], population[i], population[i + 1]);

                double muteRate1 = Optimizers::interpolateMuteRate(low, high, population[i].getSize());
                if (rdist(rng) < muteRate1) {
                    population[i].randMutate();
                    population[i].calcFitness();
                }

                double muteRate2 = Optimizers::interpolateMuteRate(low, high, population[i].getSize());
                if (rdist(rng) < muteRate2) {
                    population[i + 1].randMutate();
                    population[i + 1].calcFitness();
                }
            }
        };
    } else if (method == "RMHC") {
        generator = [&](std::vector<Contender> &population) {
            int max = (int) population.size();
            int cutoff = (int) (0.95 * population.size());
            for (int i = 0; i < max; ++i) {
                if (i < cutoff) {
                    Contender temp = population[i];
                    temp.randMutate();
                    temp.calcFitness();
                    if (temp < population[i])
                        population[i] = temp;
                } else {
                    population[i] = Contender();
                    population[i].calcFitness();
                }
            }
        };
    } else if (method == "Random") {
        generator = [&](std::vector<Contender> &population) {
            for (auto &member: population) {
                member = Contender();
                member.calcFitness();
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
        double grad_percent = GetDouble("Graduation Percent:");
        std::cout << grad_percent << std::endl;
        params += " GradPercent:" + std::to_string(grad_percent);

        int num_tiers = GetInt("Number of num_tiers:");
        std::cout << num_tiers << std::endl;
        params += " Tier:" + std::to_string(num_tiers);

        int num_gens = GetInt("Generations between graduations:");
        std::cout << num_gens << std::endl;
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

    Experiment();

    return 0;
}

