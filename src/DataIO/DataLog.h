#pragma once

#include <Point.h>
#include <Contender.h>

#include <string>
#include <vector>
#include <ctime>

class DataLog
{
private:
    std::string m_name;
    std::string m_dataPath;
    std::string m_logPath;
    std::string m_dataName;
    std::string m_method;
    std::string m_params;
    std::time_t m_runTime;

    std::string DataName();

public:
    DataLog(const std::string& dataPath, const std::string& outDir, const std::string& method, const std::string& params);
    void WriteHeader();
    std::string NameGenerator();
    void LogEntry(const std::string& entry);

    std::vector<Point> GetPoints();
};

std::vector<Point> ReadDataFile(std::string& fPath);
