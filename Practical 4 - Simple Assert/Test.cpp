#include <assert.h>
#include <vector>

class Test
{
public:
	Test() {}

	void size(std::vector<int> v) //Tests that 6 numbers were passed
	{
		assert(v.size == 6);
	}

	void range(std::vector<int> v)
	{
		for (auto& val : v) //Loop through each value
		{
			assert(val >= 1 && val <= 46);
		}
	}

	void repeated(std::vector<int> v)
	{
		for (auto& a : v)
		{
			assert(std::count(v.begin(), v.end(), a) == 1); //Tests if there is only 1 occurance of (a) in the vector ie. no duplicates
		}
	}
};