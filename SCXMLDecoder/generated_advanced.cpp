#include <iostream> 
#include <chrono> //c++ 11
#include <thread> //c++ 11
using  namespace std; 

enum State{ Idle, Rolling, Looping};


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
	switch(newState){ 
	 case Idle:
		 if (newState == Rolling){
			 InRolling();
		 	 currentState = Rolling;
			 std::cout<<"enter  Rolling"<<std::endl;
		}
		break;
	}
	 case Rolling:
		 if (newState == Idle){
			 InIdle();
		 	 currentState = Idle;
			 std::cout<<"enter  Idle"<<std::endl;
		}
		break;
	}
	 case Looping:
		 if (newState == Idle){
			 sleep_for(seconds(3));
			 InIdle();
		 	 currentState = Idle;
			 std::cout<<"enter  Idle"<<std::endl;
		}
		break;
	}

}


int main()
{ 
	cout << "Hello boiz\n ";
}

