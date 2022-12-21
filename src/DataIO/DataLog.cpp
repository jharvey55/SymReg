#include <DataLog.h>
//#include <Contender.h>
#include <Point.h>

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <filesystem>


bool DataLog::dot = false;
bool DataLog::diversity = false;
int DataLog::num_gens = 100;


std::string DataLog::DataName() {
    // retrieve substring of file name
    std::string filename = m_dataPath.substr(m_dataPath.find_last_of("/\\") + 1);

    // strip file extension
    std::string::size_type const spot(filename.find_last_of("."));
    std::string base_name = filename.substr(0, spot);

    return base_name;
}

DataLog::DataLog() {
    m_dataPath = "UNDEFINED";;
    m_dataName = "UNDEFINED";;

    m_method = "UNDEFINED";;
    m_params = "UNDEFINED";;
    m_runTime = time(0);
    m_name = "UNDEFINED";;
    m_outDir = "UNDEFINED";;
    m_learnPath = "UNDEFINED";;
    m_dotPath = "UNDEFINED";;
}

DataLog::DataLog(const std::string &dataPath, const std::string &outDir, const std::string &method,
                 const std::string &params) {

    // set up member variables
    m_dataPath = dataPath;
    m_dataName = DataName();

    m_method = method;
    m_params = params;
    m_runTime = time(0);
    m_name = NameGenerator();
    m_outDir = outDir;
    MakeExpDir();

    m_learnPath = m_outDir + "/" + m_name + "_learn.txt";
    m_dotPath = m_outDir + "/" + m_name + "_dot.txt";
    m_divPath = m_outDir + "/" + m_name + "_div.txt";


    // set up files
    std::fstream file1(m_learnPath, std::fstream::out);
    file1.close();
    WriteHeader(LEARN);

    if (dot) {
        std::fstream file2(m_dotPath, std::fstream::out);
        file2.close();
        WriteHeader(DOT);

        std::cout << m_name << std::endl;
    }

    if (diversity) {
        std::fstream file3(m_divPath, std::fstream::out);
        file3.close();
        WriteHeader(DIVERSITY);

        std::cout << m_name << std::endl;
    }
}

std::string DataLog::NameGenerator()
{
    // Target format: DataSet_Method_YYYY`MM`DD_HH`MM`SS.txt
    std::string name;
    struct tm newtime;
    std::time_t now = time(0);
    localtime_r(&now, &newtime);
    //std::tm* ltm = localtime(&now);

    // add data name
    name += m_dataName;
    name += "_";

    // add method
    name += m_method;
    name += "_";

    // add date
    name += std::to_string(newtime.tm_year + 1900);
    name += "`";
    name += std::to_string(newtime.tm_mon + 1);
    name += "`";
    name += std::to_string(newtime.tm_mday);
    name += "-";

    // add time
    name += std::to_string(newtime.tm_hour);
    name += "`";
    name += std::to_string(newtime.tm_min);
    name += "`";
    name += std::to_string(newtime.tm_sec);

//    name += ".txt";

    return name;
}

/// @brief Writes Header for files
void DataLog::WriteHeader(const logtype &type) {
    // Open file for writing
    std::string file_path;
    switch (type) {
        case DOT :
            file_path = m_dotPath;
            break;
        case LEARN:
            file_path = m_learnPath;
            break;
        case DIVERSITY:
            file_path = m_divPath;
            break;
    }
    std::fstream file(file_path, std::fstream::out | std::fstream::app);

    struct tm newtime;
    std::time_t now = time(0);
    localtime_r(&now, &newtime);

    if (file.is_open()) {
        file << "DataSet:\t" << m_dataName << "\n";
        file << "RunTime:\t" << 1900 + newtime.tm_year << "-" << 1 + newtime.tm_mon << "-" << newtime.tm_mday << " ";
        file << newtime.tm_hour << ":" << newtime.tm_min << ":" << newtime.tm_sec << "\n";
        file << "Method:\t" << m_method << "\n";
        file << "Params:\t" << m_params << "\n";
        file << "DataPath:\t" << m_dataPath << "\n";

        file << "\n################################################################################\n\n";
    }

    file.close();
}

//void DataLog::LogEntry(const std::string& entry)
//{
//    std::fstream file(m_logPath, std::fstream::out | std::fstream::app);
//
//    if (file.is_open())
//    {
//        file << entry << "\n";
//    }
//
//    file.close();
//}

void DataLog::LogEntry(const logtype &type, const std::string &entry) {
    std::string file_path;
    switch (type) {
        case DOT :
            file_path = m_dotPath;
            break;
        case LEARN:
            file_path = m_learnPath;
            break;
        case DIVERSITY:
            file_path = m_divPath;
            break;
        default:
            break;
    }

    std::fstream file(file_path, std::fstream::out | std::fstream::app);

    if (file.is_open()) {
        file << entry << "\n";
    }

    file.close();
}

/// <summary>
/// Reads in data from fPath.
///
/// </summary>
/// <param name="fPath">Path to the file to be read in</param>
/// <returns>a 2d double array contaning all the points</returns>
std::vector<Point> ReadDataFile(std::string& fPath)
{
    //Timer t = Timer("ReadInPoints");
    std::string line;

    // use vector to simplify heap usage
    std::vector<Point> points;

    std::ifstream MyReadFile(fPath);

    // read file line by line and add doubles to points
    while (getline(MyReadFile, line))
    {
        double lNum, rNum;
        std::string delimeter = "\t";
        lNum = stod(line.substr(0, line.find(delimeter)));
        rNum = stod(line.substr(line.find(delimeter), line.find("\r")));

        points.push_back(Point(lNum, rNum));
    }

    std::cout << points.size() << " points read in..." << std::endl;

    return points;
}

std::vector<Point> DataLog::GetPoints() {
    std::vector<Point> points = ReadDataFile(m_dataPath);
    return points;
}

void DataLog::MakeExpDir() {
    auto hold = std::filesystem::current_path();
    std::filesystem::current_path(m_outDir);
    std::filesystem::create_directory(m_name);
    m_outDir = m_outDir + m_name;
    if (!std::filesystem::is_directory(m_name))
        std::cout << "Failed to create directory: " << m_outDir << std::endl;
    else
        std::cout << "Successfully created directory: " << m_outDir << std::endl;

    std::filesystem::current_path(hold);
}