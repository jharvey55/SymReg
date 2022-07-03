#include <Optimizers.h>
#include <Node.h>
#include <Contender.h>
#include <DataLog.h>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace Optimizers {

    void RandomSearch(int num_points, const std::string& dPath, const std::string& oPath) {
        // TODO: Set up proper variables

        // TODO: Generate solutions


    }

    void OptLoop(const std::string& dPath, const std::string& oPath, const std::string& method, const std::string& params, const int& max_evals, const int& pop_size, const auto& generator) {
        // Generate Logging Tool
        DataLog logger = DataLog(dPath, oPath, method, params);

        // Read in test Data
        std::vector<Point> points = logger.GetPoints();

        // Initialize tracking variables TODO: Add remaining tracking variables
        int eval_count = 0;
        double best_fitness = 0;

        // Generate starting population
        std::vector<Contender> population;
        for (int i = 0; i < pop_size; i++)
            population.emplace_back();

        // Sort and log the best contender
        std::sort(population.begin(), population.end());
        logger.LogEntry(population[0].LogString());

        //


    }
}
