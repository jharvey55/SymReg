#include <Optimizers.h>
#include <Node.h>
#include "Contender.h"
#include <DataLog.h>

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <random>
#include <cmath>
#include <set>

namespace Optimizers {


    /***
     * Deterimnes the variance of a population using the subset of of subSeries
     * @param subSeries
     * @param pop
     * @return
     */
    double ErrorSpread(const std::vector<Point> &subSeries, const std::vector<Contender> &pop) {
        double spread = 0;
        double mean = 0;
        double sum1 = 0;
        double sum2 = 0;
//        std::vector<double> errors;
        for (Contender member: pop) {
            double fit = member.testFitness(subSeries);
            mean += fit;
            sum1 += std::pow(fit, 2);
//            errors.push_back(fit);
        }

        sum2 = mean * -2.0f;

        mean /= (double) pop.size();

        sum2 *= mean;

//        for(double e : errors) {
//            spread += std::pow((e-mean), 2);
//        }

        spread = sum1 + sum2 + std::pow(mean, 2) * (double) pop.size();

        spread /= (double) pop.size() - 1;

//        spread = std::sqrt(spread);
        return spread;
    }

    void DataPicker(const int &trials, const std::vector<Point> &points, const std::vector<Contender> &pop) {
        std::random_device rand_dev;
        std::mt19937 rng(rand_dev());
        std::uniform_int_distribution<int> point_range(0, (int) points.size());

//        std::vector<std::vector<Point>> series;

        double best_spread = 0;
        double spread;

        for (int trial = 0; trial < trials; trial++) {
            std::vector<Point> series;
            int n = point_range(rng);
            std::set<int> indices;
            while (indices.size() < n) {
                indices.insert(point_range(rng));
            }

            for (int i = 0; i < (int) indices.size(); i++)
                series.push_back(points[i]);

            spread = ErrorSpread(series, pop);
            if (spread > best_spread) {
                best_spread = spread;
                Contender::Points = series;
            }

        }
    }

    // Operational flags

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

        logger.LogEntry(LEARN, population[0].LogString());
        best = population[0];
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;

        std::cout << "Beginning loop...\n";
        while (Contender::getEvalCount() < max_evals) {

            // Generate new solutions
            population = generator(population);

            // Rank solutions
            std::sort(population.begin(), population.end());
//            std::cout << Contender::getEvalCount() << " : " << population[0].getFitness() << " : " << population[0].getEqString() << std::endl;

            if (population[0] < best) {
                best = population[0];
                logger.LogEntry(LEARN, population[0].LogString());
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

    // This was an attempt at tracking the progress of the solution
    void progressBar(int max, int current) {
        int barWidth = 70;
        float progress = (float) current / (float) max;
        std::cout << '\r';
        std::string pbar = "\r";
//        std::cout << "\r[";
        pbar += "[";
//        std::cout.flush();

        int pos = (int) ((float) barWidth * progress);
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) { pbar += "="; }
            else if (i == pos) { pbar += ">"; }
            else { pbar += " "; }
//            std::cout.flush();
        }
        pbar += "]";
        pbar += std::to_string((int) (progress * 100.0f));
        pbar += " %";
//        std::cout << "] " << int(progress * 100.0) << " %";
        std::cout << pbar;
        std::cout.flush();
    }


    void
    OptLoop(const std::string &dPath, const std::string &oPath, const std::string &method, const std::string &params,
            const int &max_evals, const int &pop_size, const std::function<void(std::vector<Contender> &)> &generator) {
        std::cout << "Beginning " << method << " optimization loop...\n";

        // Generate Logging Tool
        std::cout << "Generating logging tool...\n";
        DataLog logger = DataLog(dPath, oPath, method, params);

        // Read in test Data
        std::cout << "Reading in data points...\n";
        Contender::Points = logger.GetPoints();

        // Initialize tracking variables TODO: Add remaining tracking variables
        std::cout << "Initializing tracking variables...\n";
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

        logger.LogEntry(LEARN, population[0].LogString());
        best = population[0];
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;

        std::cout << "Beginning loop...\n";
        while (Contender::getEvalCount() < max_evals) {

            // Generate new solutions
            generator(population);

            // Rank solutions
            std::sort(population.begin(), population.end());
//            std::cout << Contender::getEvalCount() << " : " << population[0].getFitness() << " : " << population[0].getEqString() << std::endl;

            if (population[0] < best) {
                best = population[0];
                logger.LogEntry(LEARN, population[0].LogString());
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


    /**
     *
     * @param dPath: Path to dataset
     * @param oPath:
     * @param method
     * @param params
     * @param max_evals
     * @param pop_size
     * @param generator
     * @return
     */
    double
    OptLoopRun(const std::string &dPath, const std::string &oPath, const std::string &method, const std::string &params,
               const int &max_evals, const int &pop_size,
               const std::function<std::vector<Contender>(std::vector<Contender>)> &generator) {
//        std::cout << "Beginning " << method << " optimization loop...\n";

        // Generate Logging Tool
//        std::cout << "Generating logging tool...\n";
        DataLog logger = DataLog(dPath, oPath, method, params);

        // Read in test Data
//        std::cout << "Reading in data points...\n";
        Contender::Points = logger.GetPoints();

        Contender best;

        // Generate starting population
        std::vector<Contender> population;
        for (int i = 0; i < pop_size; i++) {
            population.emplace_back();
            population[i].calcFitness();
        }

        std::sort(population.begin(), population.end());

        logger.LogEntry(LEARN, population[0].LogString());
        best = population[0];
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;

        while (Contender::getEvalCount() < max_evals) {

            // Generate new solutions
            population = generator(population);

            // Rank solutions
            std::sort(population.begin(), population.end());

            if (population[0] < best) {
                best = population[0];
                logger.LogEntry(LEARN, population[0].LogString());

            }
        }

        std::cout << "\nCONCLUSION: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;
//        best.treePrint();
        // Cleanup
        Contender::ResetEvaluationCount();
        return best.getFitness();

    }

    /**
     * HFC: Hierarchical Fair Competition Loop
     *
     *
     * @param dPath : Path to the dataset
     * @param oPath : Path for logfile
     * @param method : String naming the optimization method used
     * @param params : String of parameters used in optimization method
     * @param max_evals : Cap evaluations used
     * @param pop_size : Population size used
     * @param generator : Lambda function for generating new solutions
     */
    void HFC(const std::string &dPath, const std::string &oPath, const std::string &method,
             const std::string &params, const int &max_evals, const int &pop_size, const int &num_tiers,
             const float &grad_percent, const int &num_gens,
             const std::function<void(std::vector<Contender> &)> &generator) {

        // TODO: Pass filled in logger, turn generation into variable


        // Set up tracking variables
        DataLog logger = DataLog(dPath, oPath, method, params);
        Contender::Points = logger.GetPoints();
        const std::vector<Point> safe_state = Contender::Points;

        std::vector<std::vector<Contender>> population;

        // Create the population layers
        for (int i = 0; i < num_tiers; i++)
            population.emplace_back();

        // INitial population and starting best contender
        for (int i = 0; i < pop_size; i++) {
            population[0].emplace_back();
            population[0][i].calcFitness();
        }
        std::sort(population[0].begin(), population[0].end());
        Contender best = population[0][0];

        logger.LogEntry(LEARN, best.LogString());
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;

        DataPicker(25, safe_state, population[0]);
        best.calcFitness();

        int generation = 0;

        // Main Optimization Loop
        while (Contender::getEvalCount() < max_evals) {
            // Logic tree for tiers
            if (generation % num_gens == 0) {
                std::cout << "Generation: " << generation << ", " << Contender::getEvalCount() << std::endl;
                // Promote from tier below to current tier when appropriate
                bool runOnce = true;
                for (int tier = num_tiers - 1; tier > 0; tier--) {

                    // see if it is appropriate to promote (i.e. don't promote to second tier if first number of generations not met)
                    if (generation >= tier * num_gens) {
                        int source = tier - 1;
                        // Graduate top grad percent and remove from current tier
                        int cutoff = (int) (grad_percent * (float) population[source].size());

                        if (runOnce) {
                            DataPicker(15, safe_state, population[source]);
                            best.calcFitness();
                            runOnce = false;
                        }

                        std::sort(population[source].begin(), population[source].end());

                        // Handle top population growth
                        if (tier == num_tiers - 1 && population[tier].size() >= pop_size) {
//                            std::cout << "Oh no" << std::endl;
                            std::sort(population[tier].begin(), population[tier].end());
                            population[tier].resize(pop_size);
                            population[tier].erase(population[tier].end() - cutoff, population[tier].end());
                        }

                        for (int i = 0; i < cutoff; i++)
                            population[tier].push_back(population[source][i]);
//                        population[source].erase(population[source].begin(), population[source].begin()+cutoff);
                        population[source].clear();

                        // Sort parent tier
                        std::sort(population[tier].begin(), population[tier].end());

                        std::cout << "\t" << tier << "::" << population[tier].size() << ":: "
                                  << population[tier][0].getFitness() << " : " << population[tier][0].getEqString()
                                  << std::endl;
                    }
                }

                // Reset base tier with new random population
                if (population[0].empty()) {
                    for (int i = 0; i < pop_size; i++) {
                        population[0].emplace_back();
                        population[0][i].calcFitness();

                    }
                }

//                population[0].clear();
//                for (int i = 0; i < pop_size; i++) {
//                    population[0].emplace_back();
//                    population[0][i].calcFitness();
//
//                }

                std::sort(population[0].begin(), population[0].end());
                std::cout << "\t" << 0 << ": " << population[0][0].getFitness() << " : "
                          << population[0][0].getEqString() << std::endl;
            }

            for (int tier = 0; tier < num_tiers; tier++) {
                // Optimize tier if it's populated
                if (!population[tier].empty()) {
//                    std::cout << tier << std::endl;

                    generator(population[tier]);
                    std::sort(population[tier].begin(), population[tier].end());

                    // Check for tier best and update if found
                    if (population[tier][0] < best) {
                        double best_fit = best.testFitness(safe_state);
                        double con_fit = population[tier][0].testFitness(safe_state);
                        if (con_fit < best_fit) {
                            best = population[tier][0];
                            logger.LogEntry(LEARN, best.LogString());
                            std::cout << Contender::getEvalCount() << "::" << tier << "::" << generation << ":: "
                                      << best_fit << " : " << best.getEqString()
                                      << std::endl;
                        }
                    }
                }
            }

//            std::cout << generation << std::endl;
            generation++;

        }
        std::cout << "\n\n\nCONCLUSION: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;
        best.treePrint();
        // Cleanup
        Contender::ResetEvaluationCount();

    }
}
