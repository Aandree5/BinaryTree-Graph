#include <iostream>
#include <vector>

template<typename T>
void printList(const std::vector<T> &list)
{	
	for (int i = 0; i < list.size(); i++)
	{
		if (i > 0)
			std::cout << " | ";
		std::cout << list[i];
	}
}


std::vector<int64_t> checkKapreker(std::vector<int64_t> &intList)
{
	std::vector<int64_t> kaprekarList;
	
	for(int64_t n : intList)
	{
		int64_t expN = n * n;
		std::vector<int> digits;
		int firstHalf = 0;
		int secondHalf = 0;
		
		while(expN > 0)
		{
			digits.push_back(expN % 10);
			
			expN = expN / 10;
		}
		
		int half = (int)(digits.size() / 2);
		
		int multiplyer = 1;
		for(int i = 0; i < half; i++)
		{
			
			firstHalf += digits[i] * multiplyer;
			secondHalf += digits[half + i] * multiplyer;
			
			multiplyer *= 10;
		}
			
		if(firstHalf + secondHalf == n)
			kaprekarList.push_back(n);
		
	}
	
	return kaprekarList;
}


int main()
{
	std::vector<int64_t> intList;
	std::vector<int64_t> kaprekarList;
	
	std::cout << "Enter numbers to get the binary representation of them. (To stop enter not a number)" << std::endl;
	while (true)
	{
		int64_t value;
		if (!(std::cin >> value))
			break;
		
		intList.push_back(value);
	}

	std::cout << std::endl << "Numbers inserted: ";
	printList(intList);
	
	std::cout << std::endl;

	std::cout << std::endl << "Kaprekar numbers: ";
	kaprekarList = checkKapreker(intList);
	printList(kaprekarList);
	
	std::cout << std::endl;
	
	return 0;
}