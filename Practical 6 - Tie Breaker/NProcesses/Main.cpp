#include <iostream>
#include <vector>
#include <thread>

//Public variables
std::vector<std::thread*> threads;
std::vector<int> in, last;

//Change thread count to see amounts of threads working independantly
int threadCount = 6;

//Methods
void cs(int index);

void main()
{
	for (int i = 0; i < threadCount; i++)
		in.push_back(0);

	//Copy over in to last
	last = in;

	for (int i = 0; i < threadCount; i++)
		threads.push_back(new std::thread(cs, i));

	//Needed to keep the program from finishing
	while (true){}
}

void cs(int index)
{
	while (true)
	{
		for (int j = 0; j < threadCount - 1; j++)
		{
			in[index] = j;
			last[j] = index;

			for (int k = 0; k < threadCount - 1; k++)
			{
				while (last[j] == index && k != index)
				{

				}
			}
		}

		std::cout << "Criticial section of thread: " << index + 1 << std::endl;
		in[index] = 0; //Exit
	}
}
