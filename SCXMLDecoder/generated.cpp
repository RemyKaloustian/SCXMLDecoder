#include <iostream> 

enum State{ Idle, Rolling};


void InIdle()
{ 
	cout<<" InIdle" << "\n";

}


void InRolling()
{ 
	cout<<" InRolling" << "\n";

}

State currentState = State_1;

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

}


int main()
{ 
	cout << "Hello peasants\n ";
}

