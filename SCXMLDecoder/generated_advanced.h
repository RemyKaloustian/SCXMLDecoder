#pragma once 
#include <iostream> 
#include <chrono> //c++ 11
#include <thread> //c++ 11

using std::chrono::seconds;
using std::this_thread::sleep_for;
using  namespace std; 

enum State{ Idle= 0, Rolling= 1, Looping= 2};


void InIdle()
{ 
	cout<<" InIdle" << "\n";

}


void InRolling()
{ 
	cout<<" InRolling" << "\n";

}


void InLooping()
{ 
	cout<<" InLooping" << "\n";

}

State currentState = Idle;

int activate(State newState)
{ 
	switch(currentState){ 
	 case Idle:
		 if (newState == Rolling){
			 std::cout<<"enter  Rolling"<<std::endl;
			 InRolling();
		 	 currentState = Rolling;
		}
		break;
	
	 case Idle:
		 if (newState == Looping){
			 std::cout<<"enter  Looping"<<std::endl;
			 InLooping();
		 	 currentState = Looping;
		}
		break;
	
	 case Rolling:
		 if (newState == Idle){
			 std::cout<<"enter  Idle"<<std::endl;
			 InIdle();
		 	 currentState = Idle;
		}
		break;
	
	 case Looping:
		 if (newState == Idle){
			 sleep_for(seconds(3));
			 std::cout<<"enter  Idle"<<std::endl;
			 InIdle();
		 	 currentState = Idle;
		}
		break;
	
	}

}

