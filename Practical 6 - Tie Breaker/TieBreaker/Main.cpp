#include <iostream>
#include <thread>

void cs1();
void cs2();
bool in1 = false, in2 = false, lastCs1 = false;

bool nProcess = false;
void main()
{
	if (nProcess == false)
	{
		//Petersons algorithm
		std::thread p1(cs1);
		std::thread p2(cs2);

		p1.join();
		p2.join();
	}
	else //Tie Breaker n Processes
	{

	}
}

void cs1()
{
	while (true)
	{
		in1 = true;
		lastCs1 = true;
		while (in2 && lastCs1)
		{
			continue;
		}
		std::cout << "In critical section of CS1 \n";
		in1 = false;
	}
}

void cs2()
{
	while (true)
	{
		in2 = true;
		lastCs1 = false;
		while (in1 && !lastCs1)
		{
			continue;
		}
		std::cout << "In critical section of CS2 \n";
		in2 = false;
	}
}