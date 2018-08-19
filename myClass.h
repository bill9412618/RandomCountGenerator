#include <iostream>
#include <time.h>
#include <map>
#include <list>
#include <random>
#include <fstream>
#include <chrono>
#include <queue>
using namespace std;

class myClass {
public:
    myClass();

    int randNumGenerator();
    void updateStatisticData(int num);
    void updateLastOneHundredRecord(int num);
    list<int> getLastOneHundredRecord();
    float percentageOf(int num);
    void readLastNumAndWriteToFile(string filename);

private:
    list<int> lastOneHundredNums;
    map<int,double> numCounter;
    map<int,double> numPercentage;
    double totalNumGenerated;
};
