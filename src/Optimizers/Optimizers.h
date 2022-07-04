#pragma once

#include <Contender.h>

#include <vector>
#include <string>


namespace Optimizers {
    void OptLoop(const std::string& dPath, const std::string& oPath, const std::string& method, const std::string& params, const int& max_evals, const int& pop_size, const std::function<std::vector<Contender>(std::vector<Contender>)>& generator);
//    void OptLoop(const std::string& dPath, const std::string& oPath, const std::string& method, const std::string& params, const int& max_evals, const int& pop_size, const std::function<void(std::vector<Contender>)>&  generator;

    }

