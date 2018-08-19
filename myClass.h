#include <iostream>
#include <time.h>
#include <map>
#include <list>
#include <random>
#include <fstream>
#include <chrono>
#include <queue>
#include <mutex>
#include <set>
#include <thread>
using namespace std;

typedef struct{
  unsigned long timeStamp;
  int randNum;
}node;

class mycomparison
{
public:
		bool operator()(const node& lhs, const node& rhs) const
		{
			return lhs.timeStamp>rhs.timeStamp;
		}
};

class myClass {
public:
    myClass();

    int randNumGenerator();
    void updateStatisticData(int num);
    void updateLastOneHundredRecord(int num);
    list<int> getLastOneHundredRecord();
    float percentageOf(int num);
    void readLastNumAndWriteToFile(string filename);
    bool isQueueEmpty();

    //void setProducerThreadNum(int diffThreadNum);
    //int getProducerThreadNum();

private:
    list<int> lastOneHundredNums;
    map<int,double> numCounter;
    map<int,double> numPercentage;
    double totalNumGenerated;
    std::mutex mutexForQueue;
    std::mutex mutexForRandNumGenerator;
    //queue<node> dataQueue;
    priority_queue<node,std::vector<node>,mycomparison> dataQueue;


    //std::mutex mutexForCountingThreadNum;
    //int producerThreadNum;
};
