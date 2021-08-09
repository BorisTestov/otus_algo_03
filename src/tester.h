#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <cassert>

inline bool fileExists(const std::string &name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

class ITask {
public:
    virtual std::vector<std::string> Run(std::vector<std::string> data) = 0;
};

using ITaskPtr = std::shared_ptr<ITask>;

class Tester {
public:
    Tester() = delete;

    Tester(ITaskPtr task, const std::string &path) {
        this->task = task;
        this->path = path;
    }

    void RunTests(bool verbose = false, bool assertOnError = false) {
        int testNumber = 0;
        std::cout << "Tester started: " << std::endl;
        while (true) {
            std::cout << "_______________________________" << std::endl;
            std::string inFile = path + "/test." + std::to_string(testNumber) + ".in";
            std::string outFile = path + "/test." + std::to_string(testNumber) + ".out";
            if (!fileExists(inFile) || !fileExists(outFile))
                break;
            auto start = std::chrono::high_resolution_clock::now();
            bool result = RunTest(inFile, outFile, verbose, assertOnError);
            auto stop = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
            std::string testResult = "Passed";
            if (!result) {
                testResult = "Failed";
            }
            std::cout << "Test#" << testNumber << "\t" << testResult << "\t" << elapsed << "ms"
                      << std::endl;
            testNumber++;
        }
    }

private:
    bool RunTest(std::string infile, std::string outfile, bool verbose, bool assertOnError) {
        try {
            std::string line;
            // Read array of str from input file
            std::vector<std::string> inputData;
            std::ifstream inputFile(infile);
            while (std::getline(inputFile, line)) {
                line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                inputData.push_back(line);
            }
            // Read one line from output file
            std::vector<std::string> outputData;
            std::ifstream outputFile(outfile);
            while (std::getline(outputFile, line)) {
                line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
                line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
                outputData.push_back(line);
            }
            std::vector<std::string> actual = task->Run(inputData);
            if (verbose) {
                std::cout << "Input: " << vectorToString(inputData) << std::endl;
                std::cout << "Expected: " << vectorToString(outputData) << std::endl;
                std::cout << "Actual: " << vectorToString(actual) << std::endl;
            }
            bool result = true;
            assert(actual.size() == outputData.size());
            for (int i = 0; i < actual.size(); ++i) {
                result &= actual.at(i) == outputData.at(i);
            }
            if (assertOnError) {
                assert(result == true);  // For checking long list of test cases
            }
            return result;
        }
        catch (std::exception e) {
            std::cout << e.what() << std::endl;
            return false;
        }
    }

    std::string vectorToString(std::vector<std::string> data) {
        std::stringstream result;
        for (const auto &value: data) {
            result << value << " ";
        }
        return result.str();
    }

    ITaskPtr task;
    std::string path;
};