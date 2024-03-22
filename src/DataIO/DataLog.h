#pragma once

#include <Point.h>


#include <string>
#include <vector>
#include <ctime>

enum logtype {
    DOT,
    LEARN,
    DIVERSITY
};

class DataLog {
private:
    std::string m_name;
    std::string m_dataPath;
    std::string m_outDir;
    std::string m_learnPath;
    std::string m_dotPath;
    std::string m_divPath;
    std::string m_dataName;
    std::string m_method;
    std::string m_params;
    std::time_t m_runTime;


    std::string DataName();

public:
    DataLog(const std::string &dataPath, const std::string &outDir, const std::string &method,
            const std::string &params);

    DataLog();

    void WriteHeader(const logtype &type);

    std::string NameGenerator();

    void LogEntry(const logtype &type, const std::string &entry);

    std::vector<Point> GetPoints();

    void MakeExpDir();

    static bool dot;
    static bool diversity;
    static int num_gens;
};

std::vector<Point> ReadDataFile(std::string& fPath);
