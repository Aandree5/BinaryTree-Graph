#include <iostream>
#include <vector>


std::string armstrongNumber(int n)
{
	int nCopy = n;
	std::vector<int> digits;
	
	while(nCopy > 0)
	{
		digits.push_back(nCopy % 10);

		nCopy = nCopy / 10;
	}
	
	int total = 0;
	for (int digit : digits)
	{
		total += digit * digit * digit;
	}
	
	if (total == n)
		return "Yes";
	else
		return "No";
}


int main()
{
	
	std::cout << "371: " << armstrongNumber(371) << std::endl;
	std::cout << "545: " << armstrongNumber(545) << std::endl;
	
	return 0;
}
