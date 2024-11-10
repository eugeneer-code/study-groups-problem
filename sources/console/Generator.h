#ifndef GENERATOR_H
#define GENERATOR_H
#include <random>
#include <chrono>

class Generator {
public:
    Generator();
    int generateMark();
    float generateImportance();
private:
    std::mt19937 _gen;
    std::uniform_int_distribution<unsigned> _dist100;
    std::uniform_int_distribution<unsigned> _distImport;
};


#endif //STUDY_GROUPS_PROBLEM_GENERATOR_H
