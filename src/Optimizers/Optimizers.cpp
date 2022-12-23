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

    // Operational flags




    /***
     * Deterimnes the variance of a population using the subset of of subSeries
     * @param subSeries
     * @param pop
     * @return
     */
    double ErrorSpread(const std::vector<Point> &subSeries, const std::vector<Contender> &pop) {
        double spread;
        double mean;
        double sum1 = 0;
        double sum2 = 0;
        double size = (double) pop.size();
//        std::vector<double> errors;
        for (Contender member: pop) {
            double fit = member.testFitness(subSeries);
            sum2 += fit;
            sum1 += std::pow(fit, 2);
//            errors.push_back(fit);
        }

        mean = sum2 / size;
        spread = sum1 - 2.0f * sum2 * mean + std::pow(mean, 2) * size;
        spread /= (double) pop.size() - 1;

//        spread = std::sqrt(spread);
        return spread;
    }

    void DataPicker(const int &trials, const std::vector<Point> &points, const std::vector<Contender> &pop) {
        std::random_device rand_dev;
        std::mt19937 rng(rand_dev());
        std::uniform_int_distribution<int> point_range(0, (int) points.size());

//        std::vector<std::vector<Point>> series;

        double best_spread = ErrorSpread(Contender::Points, pop);
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

        for (Contender member: pop)
            member.calcFitness();
    }

    void update(const std::string &message) {
        std::cout << "...." << message << std::endl;
    }


    void ProgTracker(const int &barWidth, const int &max_evals, Contender &best) {

        double progress = (double) Contender::getEvalCount() / (double) max_evals;


        std::string e = "E:" + std::to_string(Contender::getEvalCount());
        std::cout << e;
        int digits = (int) std::log10(max_evals) + 3;
        for (int i = 0; i < (digits - e.length()); i++)
            std::cout << " ";

        std::string fit = " F:" + std::to_string(best.getFitness());
        std::cout << fit;
        for (int i = 0; i < (12 - fit.length()); i++)
            std::cout << " ";
        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i <= pos) std::cout << "■";
//            else if (i == pos) std::cout << "■";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %          \r";
        std::cout.flush();
    }

    void HFCProgTracker(const int &barWidth, const int &max_evals, const int &generation,
                        std::vector<std::vector<Contender>> &population) {


        std::cout << "Generation: " << generation << ", " << Contender::getEvalCount() << std::endl;
        int num_tiers = (int) population.size();

        int full_pop = 0;

        for (int tier = num_tiers - 1; tier >= 0; tier--) {
            std::cout << "\t" << tier << "::" << population[tier].size();
            full_pop += (int) population[tier].size();
            if (!population[tier].empty())
                std::cout << ":: " << population[tier][0].getFitness() << " : " << population[tier][0].getSize();
            std::cout << std::endl;
        }

        double progress = (double) Contender::getEvalCount() / (double) max_evals;

        std::cout << "\n[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i <= pos) std::cout << "■";
//            else if (i == pos) std::cout << "■";
            else std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %";


        if (max_evals > Contender::getEvalCount()) {
            for (int i = 0; i < num_tiers + 2; i++) {
                std::cout << "\r";
                std::cout << "\x1b[A";
            }
            std::cout.flush();
        }

    }

    void
    OptLoop(const std::string &dPath, const std::string &oPath, const std::string &method, const std::string &params,
            const int &max_evals, const int &pop_size,
            const std::function<std::vector<Contender>(std::vector<Contender>)> &generator) {
        std::cout << "Beginning " << method << " optimization loop...\n";

        // Generate Logging Tool
        std::cout << "Generating logging tool...\n";
        Contender::logger = DataLog(dPath, oPath, method, params);

        // Read in test Data
        std::cout << "Reading in data points...\n";
        Contender::Points = Contender::logger.GetPoints();

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

        Contender::logger.LogEntry(LEARN, population[0].LogString());
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
                Contender::logger.LogEntry(LEARN, population[0].LogString());
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
        std::cout << "\n\nBGA: Beginning " << method << " optimization loop" << std::endl;

        // Generate Logging Tool
        update("Generating logging tool");
        Contender::logger = DataLog(dPath, oPath, method, params);

        // Read in test Data
        update("Reading in data points");
        Contender::Points = Contender::logger.GetPoints();

        // Initialize tracking variables TODO: Add remaining tracking variables
        update("Initializing tracking variables");
        Contender best;

        update("Generating starting population");
        // Generate starting population
        std::vector<Contender> population;
        for (int i = 0; i < pop_size; i++) {
            population.emplace_back();
            population[i].calcFitness();
        }
        // Sort and log the best contender
        update("Sorting");
        std::sort(population.begin(), population.end());

        Contender::logger.LogEntry(LEARN, population[0].LogString());
        best = population[0];
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;

        update("Beginning loop");
        int generation = 0;
        while (Contender::getEvalCount() < max_evals) {
            ProgTracker(80, max_evals, best);

            if (DataLog::diversity) {
                if (generation % DataLog::num_gens == 0)
                    Contender::PopDiversity(population, Contender::Points);
            }

            // Generate new solutions
            generator(population);

            // Rank solutions
            std::sort(population.begin(), population.end());
//            std::cout << Contender::getEvalCount() << " : " << population[0].getFitness() << " : " << population[0].getEqString() << std::endl;

            if (population[0] < best) {
                best = population[0];
                Contender::logger.LogEntry(LEARN, population[0].LogString());

//                std::cout << Contender::getEvalCount() << " : " << best.getFitness() << " : " << best.getEqString()
//                          << std::endl;
            }

            generation++;
        }
        ProgTracker(80, max_evals, best);
        std::cout << "\n\n\nCONCLUSION: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;
//        best.treePrint();
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
        Contender::logger = DataLog(dPath, oPath, method, params);

        // Read in test Data
//        std::cout << "Reading in data points...\n";
        Contender::Points = Contender::logger.GetPoints();

        Contender best;

        // Generate starting population
        std::vector<Contender> population;
        for (int i = 0; i < pop_size; i++) {
            population.emplace_back();
            population[i].calcFitness();
        }

        std::sort(population.begin(), population.end());

        Contender::logger.LogEntry(LEARN, population[0].LogString());
        best = population[0];
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;

        int generation = 0;
        while (Contender::getEvalCount() < max_evals) {

            if (DataLog::diversity) {
                if (generation % DataLog::num_gens == 0)
                    Contender::PopDiversity(population, Contender::Points);
            }

            // Generate new solutions
            population = generator(population);

            // Rank solutions
            std::sort(population.begin(), population.end());

            if (population[0] < best) {
                best = population[0];
                Contender::logger.LogEntry(LEARN, population[0].LogString());

            }
            generation++;
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
             const double &grad_percent, const int &num_gens,
             const std::function<void(std::vector<Contender> &)> &generator) {

        std::cout << "\n\n################################################################################"
                  << std::endl;
        std::cout << "HFC experiment: " << method << std::endl;

        // Set up tracking variables
        update("setting up tracking variables");
        Contender::logger = DataLog(dPath, oPath, method, params);
        Contender::Points = Contender::logger.GetPoints();
        const std::vector<Point> safe_state = Contender::Points;

        std::vector<std::vector<Contender>> population;


        update("creating population tiers");
        // Create the population layers
        for (int i = 0; i < num_tiers; i++)
            population.emplace_back();

        // INitial population and starting best contender
        update("Initial population and starting best contender");
        for (int i = 0; i < pop_size; i++) {
            population[0].emplace_back();
            population[0][i].calcFitness();
        }
        std::sort(population[0].begin(), population[0].end());
        Contender best = population[0][0];

        Contender::logger.LogEntry(LEARN, best.LogString());
        std::cout << "INITIAL: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;
        bool dp = false;

        if (dp) {
            DataPicker(25, safe_state, population[0]);
            best.calcFitness();
        }

        int generation = 0;

        // Main Optimization Loop
        while (Contender::getEvalCount() < max_evals) {
//            ProgTracker(70, max_evals);
            HFCProgTracker(80, max_evals, generation, population);
            if (DataLog::diversity) {
                if (generation % DataLog::num_gens == 0)
                    Contender::PopDiversity(population);
            }

            // Logic tree for tiers
            if (generation % num_gens == 0) {
//                std::cout << "Generation: " << generation << ", " << Contender::getEvalCount() << std::endl;
                // Promote from tier below to current tier when appropriate
                bool runOnce = dp;
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

//                        std::cout << "\t" << tier << "::" << population[tier].size() << ":: "
//                                  << population[tier][0].getFitness() << " : " << population[tier][0].getEqString()
//                                  << std::endl;
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
//                std::cout << "\t" << 0 << ": " << population[0][0].getFitness() << " : "
//                          << population[0][0].getEqString() << "\n\n" << std::endl;
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
                            Contender::logger.LogEntry(LEARN, best.LogString());
//                            std::cout << Contender::getEvalCount() << "::" << tier << "::" << generation << ":: "
//                                      << best_fit << " : " << best.getEqString()
//                                      << std::endl;
                        }
                    }
                }
            }

//            std::cout << generation << std::endl;
            generation++;

        }
        HFCProgTracker(80, max_evals, generation, population);

        std::cout << "\n\n\nCONCLUSION: " << Contender::getEvalCount() << " : " << best.getFitness() << " : "
                  << best.getEqString() << std::endl;
//        best.treePrint();
        // Cleanup
        Contender::ResetEvaluationCount();

    }

    double interpolateMuteRate(double low, double high, int size, int cap) {
        if (size > cap)
            return high;
        else {
            double range = high - low;
            double step = range * ((double) size / (double) cap);
            return step + low;
        }
    }

    double interpolateMuteRate(const double &low, const double &high, const int &size) {
//        std::cout << "Interpolating" << std::endl;
        double step = 1.0f - 8.0f / (double) size;
        double rate = low + step * (high - low);
//        if(size > 500) {
//            std::cout << "\n\n\n\n\n\n##############" << std::endl;
//            std::cout << "STEP: " << step << std::endl;
//            std::cout << "HIGH: " << high << std::endl;
//            std::cout << "LOW: " << high << std::endl;
//            std::cout << "SIZE: " << size << std::endl;
//            std::cout << "RANGE: " << high - low << std::endl;
//            std::cout << "Rate: " << rate << std::endl;
//        }
        return rate;
    }


}
