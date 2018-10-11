#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <stdexcept>


int64_t findInverse(int64_t n)
{
	if (n <= 0)
		return 1;
	
	return n * findInverse(n - 1);
}

bool dividesFactorial(int64_t n1, int64_t n2)
{
	int64_t factN1 = findInverse(n1);
	
	if (factN1 % n2 == 0)
		return true;
	
	return false;	
}


int main()
{
	std::cout << "Insert two numbers separated by a space (To stop just type any letter)" << std::endl;
	std::vector<std::pair<int64_t, int64_t>> numbers;
	std::string line;
	while(std::getline(std::cin, line))
	{
		if (!std::isdigit(line[0]))
			break;
		
		std::istringstream ss(line);
		std::vector<std::string> nString;
		std::string str;
		while (std::getline(ss, str, ' '))
		{
			nString.push_back(str);
		}
		
		if (nString.size() != 2)
			throw std::runtime_error("There needs to exist 2 number per line (Separated by ONLY one space).");
		
		int64_t n1 = std::atoi(nString[0].c_str());
		int64_t n2 = std::atoi(nString[1].c_str());
		
		if (n1 > 0 && n1 < pow(2, 31) && n2 > 0 && n2 < pow(2, 31))
			numbers.push_back(std::pair<int64_t, int64_t>(std::atoi(nString[0].c_str()), std::atoi(nString[1].c_str())));
		else
			throw std::runtime_error("Only non negative number and smaller than 2^31.");
	}
	
	if (numbers.size() < 1)
		throw std::runtime_error("No numbers where added.");
	
	for(std::pair<int64_t, int64_t> n : numbers)
	{
		if (dividesFactorial(n.first, n.second))
			std::cout << std::to_string(n.second) << " divides " << std::to_string(n.first) << "!" << std::endl;
		else
			std::cout << std::to_string(n.second) << " does not divide " << std::to_string(n.first) << "!" << std::endl;
	}
	
	return 0;
}
