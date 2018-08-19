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
      std::this_thread::sleep_for(chrono::milliseconds(1));

    }
}


int main(int argc, char** argv) {
    producerThreadNum=0;
    myClass MyClass;

    std::thread producer1(producerFunction,std::ref(MyClass),1000);
    std::thread producer2(producerFunction,std::ref(MyClass),1000);
    std::thread producer3(producerFunction,std::ref(MyClass),1000);
    std::thread producer4(producerFunction,std::ref(MyClass),1000);
    std::thread producer5(producerFunction,std::ref(MyClass),1000);

    std::thread consumer(consumerFunction,std::ref(MyClass));

    producer1.join();
    producer2.join();
    producer3.join();
    producer4.join();
    producer5.join();

    consumer.join();

    for(int i=1;i<=5;i++){
      cout<<"percentage of "<<i<<" : "<<MyClass.percentageOf(i)<<endl;
    }

    return 0;
}
