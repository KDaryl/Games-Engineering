#pragma once
#include <assert.h>
#include <vector>

class Test
{
public:
	Test() {}

	void size(std::vector<int> v); //Tests that 6 numbers were passed

	void range(std::vector<int> v);

	void repeated(std::vector<int> v);
};