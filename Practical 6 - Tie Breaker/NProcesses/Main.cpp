#include <iostream>
#include <vector>
#include <thread>

//Public variables
std::vector<std::thread*> threads;
std::vector<bool> in, last;
int threadCount = 10;
int lastIndex = 0;

//Methods
void cs(int index);

void main()
{
	for (int i = 0; i < threadCount; i++)
		in.push_back(false);

	//Copy over in to last
	last = in;

	for (int i = 0; i < threadCount; i++)
		threads.push_back(new std::thread(cs, i));

	int x = 0;
}

void cs(int index)
{
	while (true)
	{
		in[index] = true;
		last[index] = true;
		lastIndex = index;

		while (in[index] && last[index] && lastIndex == index)
		{
			continue;
		}

		std::cout << "Criticial section of thread: " << index << "\n";
		in[index] = false; //Exit
		last[index] = false;
	}
}
