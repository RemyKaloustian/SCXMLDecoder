#pragma once 
#include <iostream> 
using  namespace std; 

enum State{ Idle= 0, Rolling= 1};


void InIdle()
{ 
	cout<<" InIdle" << "\n";

}


void InRolling()
{ 
	cout<<" InRolling" << "\n";

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
	 case Rolling:
		 if (newState == Idle){
			 std::cout<<"enter  Idle"<<std::endl;
			 InIdle();
		 	 currentState = Idle;
		}
		
		break;
	}

}

