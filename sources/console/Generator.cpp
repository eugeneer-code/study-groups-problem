#include "Generator.h"

Generator::Generator()
{
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );
    _gen = std::mt19937(seed);
    _dist100 = std::uniform_int_distribution<unsigned>(1, 100);
    _distImport = std::uniform_int_distribution<unsigned>(5, 20);
}

// Случайный генератор оценки
int Generator::generateMark() {
    unsigned num = _dist100(_gen);
    if(num < 5) return 2; // вероятность получения оценки 2: 5%
    else if(num < 20) return 3; // вероятность получения оценки 3: 15%
    else if(num < 70) return 4; // вероятность получения оценки 4: 50%
    else return 5; // вероятность получения оценки 5: 30%
}

// Важность направления
float Generator::generateImportance() {
    float num = _distImport(_gen);
    return num/10;
}