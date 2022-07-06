#include <Optimizers.h>
#include <Node.h>
#include <Contender.h>
#include <DataLog.h>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace Optimizers {
    void
    OptLoop(const std::string &dPath, const std::string &oPath, const std::string &method, const std::string &params,
            const int &max_evals, const int &pop_size,
            const std::function<std::vector<Contender>(std::vector<Contender>)> &generator) {
        std::cout << "Beginning " << method << " optimization loop...\n";

        // Generate Logging Tool
        std::cout << "Generating logging tool...\n";
        DataLog logger = DataLog(dPath, oPath, method, params);

        // Read in test Data
        std::cout << "Reading in data points...\n";
        Contender::Points = logger.GetPoints();

        // Initialize tracking variables TODO: Add remaining tracking variables
        std::cout << "Initializing tracking variables...\n";
        int eval_count = 0;
        Contender best;

        std::cout << "Generating starting population...\n";
        // Generate starting population
        std::vector<Contender> population;
        for (int i = 0; i < pop_size; i++) {
            population.emplace_back();
            population[i].calcFitness();
        }
        // Sort and log the best contender
        std::cout << "Sorting...\n";
        std::sort(population.begin(), population.end());

        logger.LogEntry(population[0].LogString());
        best = population[0];
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;


        while (Contender::getEvalCount() < max_evals) {

            // Generate new solutions
            population = generator(population);

            // Rank solutions
            std::sort(population.begin(), population.end());
//            std::cout << Contender::getEvalCount() << " : " << population[0].getFitness() << " : " << population[0].getEqString() << std::endl;

            if (population[0] < best) {
                best = population[0];
                logger.LogEntry(population[0].LogString());
                // TODO: Console output
                std::cout << Contender::getEvalCount() << " : " << best.getFitness() << " : " << best.getEqString()
                          << std::endl;
            }
        }

        std::cout << "\n\n\nCONCLUSION: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;
        best.treePrint();
        // Cleanup
        Contender::ResetEvaluationCount();

    }
}
