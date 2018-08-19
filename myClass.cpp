#include "myClass.h"

myClass::myClass() {
    totalNumGenerated=0;
    lastOneHundredNums.clear();

    for(int i=1;i<=5;i++){
        numCounter[i]=0;
    }

    for(int i=1;i<=5;i++){
        numPercentage[i]=0;
    }
}

int myClass::randNumGenerator(){
    std::unique_lock<std::mutex> locker1(mutexForRandNumGenerator);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 19);
    int randNum;
    randNum = dis(gen);
    locker1.unlock();

    int finalResult;
    if(randNum<10){
        finalResult =1;
    }
    else if(randNum>=10 && randNum<15){
        finalResult =2;
    }
    else if(randNum>=15 && randNum<18){
        finalResult =3;
    }
    else if(randNum>=18 && randNum<19){
        finalResult =4;
    }
    else{
        finalResult =5;
    }
    updateLastOneHundredRecord(finalResult);
    updateStatisticData(finalResult);

    node newNode;
    newNode.timeStamp = std::chrono::system_clock::now().time_since_epoch()/std::chrono::milliseconds(1);
    newNode.randNum = finalResult;
    std::unique_lock<mutex> locker2(mutexForQueue);
    dataQueue.push(newNode);
    locker2.unlock();

    return finalResult;
}

void myClass::updateLastOneHundredRecord(int num){
    if(lastOneHundredNums.size()<100){
        lastOneHundredNums.push_back(num);
    }
    else{
        lastOneHundredNums.pop_front();
        lastOneHundredNums.push_back(num);
    }
}

list<int> myClass::getLastOneHundredRecord(){
  return lastOneHundredNums;
}

void myClass::updateStatisticData(int num){
    numCounter[num]++;
    totalNumGenerated++;
}

float myClass::percentageOf(int num){
    return (numCounter[num]*100)/totalNumGenerated;
}

bool myClass::isQueueEmpty(){
      std::unique_lock<std::mutex> locker(mutexForQueue);
      bool isQueueEmpty = dataQueue.empty();
      locker.unlock();
      return isQueueEmpty;
}

void myClass::readLastNumAndWriteToFile(string filename)
{
/*
    int lastNum = lastOneHundredNums.back();

     __int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
*/
    std::unique_lock<std::mutex> locker(mutexForQueue);
    if(!dataQueue.empty()){
      //node tmp = dataQueue.front();
      node tmp = dataQueue.top();
      dataQueue.pop();

      ofstream myFile;
      myFile.open(filename, std::ofstream::out | std::ofstream::app);
      string outputContent = "timeStamp: "+to_string(tmp.timeStamp)+" lastNum: "+to_string(tmp.randNum);
      myFile<<outputContent<<endl;
      myFile.close();
      locker.unlock();
    }
    else{
      locker.unlock();
    }
}
