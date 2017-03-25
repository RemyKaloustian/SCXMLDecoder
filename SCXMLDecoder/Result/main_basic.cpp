#include <iostream> //c++ 11
#include <chrono> //c++ 11
#include <thread> //c++ 11
#include  "Result/generated_basic.h" 

using std::chrono::seconds;
using std::this_thread::sleep_for;
using  namespace std; 


int main()
{ 
	activate(Rolling);
	activate(Idle);
	
}

