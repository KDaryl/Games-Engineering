#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <fstream>

void countLettersAndNumbers(std::vector<std::string>& file, std::pair<int, int>& count);

void main()
{
	std::pair<int, int> count, first_count, second_count;
	std::vector<std::string> readFile;

	std::ifstream file("Random Letters.txt");
	std::string line; //The line to read in

	//Read in every line and push it to the vector
	while (std::getline(file, line))
	{
		readFile.push_back(line);
	}


	const int half_size = readFile.size() / 2; //Get shalf the size of the array
	std::vector<std::string> first_half(readFile.begin(), readFile.begin() + half_size);
	std::vector<std::string> second_half(readFile.begin() + half_size, readFile.end());
	std::thread t1(countLettersAndNumbers, std::ref(first_half), std::ref(first_count)); //Count the letters and numbers in the first half of the file
	std::thread t2(countLettersAndNumbers, std::ref(second_half), std::ref(second_count)); //Count the letters and numbers in the second half of the file
	t1.join();
	t2.join();
	//Wait for both threads to finishthen add the results
	count.first = first_count.first + second_count.first;
	count.second = first_count.second + second_count.second;

	std::cout << "There are " << count.first << " letters in the file and " << count.second << " numbers in the file" << "\n";
	system("PAUSE");
}

//Counts the amount of letters and numbers in the file
void countLettersAndNumbers(std::vector<std::string>& file, std::pair<int, int>& count)
{
	//Loop through every line in the file
	for (auto& line : file)
	{
		//If the line is a number, increase the number value, else if it is a string, increase the first value
		isdigit(line[0]) ? count.second++ : count.first++;
	}
}