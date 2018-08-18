//#include <cstdlib>
#include <iostream>
#include <map>
#include <random>

//using namespace std;
int randNumGenerator(){

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0,19);
	int randNum = dis(gen);
	int finalResult;

	if(randNum<10){
		finalResult = 1;
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
	return finalResult;
}

int main(){
	std::map<int,int> numCount;
	
	numCount[1]=0;
	numCount[2]=0;
	numCount[3]=0;
	numCount[4]=0;
	numCount[5]=0;
	
#define TEST_TIME 1000 	
	for(int i=0;i<TEST_TIME;i++)
	{
		numCount[randNumGenerator()]++;
	}
	
	for(int i=1;i<=5;i++)
	{
		float probability;
		probability = (float)numCount[i]*100/TEST_TIME;
		std::cout<<"Probability of "<< i<< " is "<<probability<<"%" <<std::endl;
		
	}

}
