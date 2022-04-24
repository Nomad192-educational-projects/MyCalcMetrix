#ifndef BUISNESS_LOGIC_H
#define BUISNESS_LOGIC_H
#include <string>
#include <fstream>
#include <vector>

using namespace std;

enum compilation{
   OPEN_FILE,
   CALC_METR,
   LOAD_DATA
};

struct inMetrix{
    unsigned int republic;
    unsigned int column;
    unsigned int numberYears;
    unsigned int numberRepublics;
};
struct outMetrix{
    double min;
    double med;
    double max;
};

bool interfaceBundle(enum compilation comp, void *req, void *answer1, void *answer2, void *answer3,vector <vector<string>> *dataVector);

#endif // BUISNESS_LOGIC_H




