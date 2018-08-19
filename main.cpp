#include "myClass.h"
using namespace std;

int main(int argc, char** argv) {

    myClass MyClass;

    for(int i=0;i<50;i++){
        MyClass.randNumGenerator();
    }
    cout<<"Show the last 100 result after the randNumGenerator is called less than 100 times----------------------------------"<<endl;
    list<int> lastOneHundredNums = MyClass.getLastOneHundredRecord();
    int index=0;
    for(list<int>::iterator it = lastOneHundredNums.begin(); it!=lastOneHundredNums.end();++it){
      cout<<"#"<<index<<":"<<*it<<endl;
      index++;
    }

    for(int i=0;i<10000;i++){
        MyClass.randNumGenerator();
    }

    cout<<"Show the last 100 result after the randNumGenerator is called over 100 times----------------------------------"<<endl;
    lastOneHundredNums = MyClass.getLastOneHundredRecord();
    index=0;
    for(list<int>::iterator it = lastOneHundredNums.begin(); it!=lastOneHundredNums.end();++it){
      cout<<"#"<<index<<":"<<*it<<endl;
      index++;
    }

    cout<<"Show the percentage of each number----------------------------------"<<endl;
    for(int i=1;i<=5;i++){
        cout<<i<<":"<<MyClass.percentageOf(i)<<endl;
    }

    cout<<"Test the method readLastNumAndWriteToFile()----------------------------------"<<endl;
    MyClass.readLastNumAndWriteToFile("test.txt"); 
    return 0;
}
