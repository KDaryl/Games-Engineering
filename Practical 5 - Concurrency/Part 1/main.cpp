#include <iostream>
#include <thread>
#include <queue>

void produce(int n);
void consume();
std::queue<int> q;
int amount_produced = 0, amount_to_produced = 10;

void main()
{
	std::thread t1(produce, amount_to_produced);
	std::thread t2(consume);
	t1.join(); //Wait for thread 1 to finish
	t2.join(); //Wait for thread 2 to finish
	std::cout << "Finished producing and consuming" << std::endl;
	system("PAUSE");
}

void produce(int n)
{
	//Produce n amount of times
	for (int i = 0; i < n; i++)
	{
		q.push(i); //Add to the queue
		amount_produced++; //Increase variable
		std::cout << "Producing something" << "\n";
	}
}

void consume()
{
	while (true)
	{
		//Only loop when eevrything is consumed
		while (amount_produced == amount_to_produced)
		{
			//While the queue is not empty, consume  whatever is in it
			while (!q.empty())
			{
				q.pop(); //Remove from the front of the queue
				std::cout << "Consuming something" << "\n";
			}

			//When its finished, break out
			break;
		}
	}
}