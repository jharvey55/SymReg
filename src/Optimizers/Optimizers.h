#pragma once

#include "Contender.h"

#include <vector>
#include <string>


namespace Optimizers {
    void OptLoop(const std::string &dPath, const std::string &oPath, const std::string &method,
                 const std::string &params, const int &max_evals, const int &pop_size,
                 const std::function<std::vector<Contender>(std::vector<Contender>)> &generator);

    void OptLoop(const std::string &dPath, const std::string &oPath, const std::string &method,
                 const std::string &params, const int &max_evals, const int &pop_size,
                 const std::function<void(std::vector<Contender> &)> &generator);

    double OptLoopRun(const std::string &dPath, const std::string &oPath, const std::string &method,
                      const std::string &params, const int &max_evals, const int &pop_size,
                      const std::function<std::vector<Contender>(std::vector<Contender>)> &generator);

    void HFC(const std::string &dPath, const std::string &oPath, const std::string &method,
             const std::string &params, const int &max_evals, const int &pop_size, const int &num_tiers,
             const double &grad_percent, const int &num_gens,
             const std::function<void(std::vector<Contender> &)> &generator);

    double interpolateMuteRate(double low, double high, int size, int cap);

    double interpolateMuteRate(const double &low, const double &high, const int &size);
}

