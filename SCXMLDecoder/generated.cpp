#include <iostream> 

enum State{ State_1, State_2};


void InState1()
{ 
	cout<<" InState1" << "\n";

}


void InState2()
{ 
	cout<<" InState2" << "\n";

}

State currentState = State_1;
int activate(State newState)
{ 
	switch(newState){ 
	 case State_1:
		 if (newState == State_2){
			 InState_2();
		 	 currentState = State_2;
			 std::cout<<"enter  State_2"<<std::endl;
		}
		break;
	}
	 case State_2:
		 if (newState == Final_1){
			 InFinal_1();
		 	 currentState = Final_1;
			 std::cout<<"enter  Final_1"<<std::endl;
		}
		break;
	}

}


int main()
{ 
	cout << "Hello peasants\n ";
}

