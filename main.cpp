#include "myClass.h"
using namespace std;

int producerThreadNum;
std::mutex mutexForCountingThreadNum;

int getProducerThreadNum()
{
  std::unique_lock<mutex> locker(mutexForCountingThreadNum);
  int currentProducerThreadNum = producerThreadNum;
  locker.unlock();

  return currentProducerThreadNum;

}
void setProducerThreadNum(int diffThreadNum){
  std::unique_lock<mutex> locker(mutexForCountingThreadNum);
  producerThreadNum= producerThreadNum+diffThreadNum;
  locker.unlock();
}


void producerFunction(myClass& MyClass, int number){
  setProducerThreadNum(1);
  for(int i=0;i<number;i++){
    MyClass.randNumGenerator();
  }
  setProducerThreadNum(-1);

}

void consumerFunction(myClass& MyClass){
    while(!MyClass.isQueueEmpty()|| getProducerThreadNum()!=0)
    {
      MyClass.readLastNumAndWriteToFile("log.txt");
    }
}


int main(int argc, char** argv) {
    producerThreadNum=0;
    myClass MyClass;

    std::thread producer(producerFunction,std::ref(MyClass),1000);
    std::thread consumer(consumerFunction,std::ref(MyClass));

    producer.join();
    consumer.join();

    for(int i=1;i<=5;i++){
      cout<<"percentage of "<<i<<" : "<<MyClass.percentageOf(i)<<endl;
    }

    return 0;
}
