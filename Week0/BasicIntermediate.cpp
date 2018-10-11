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

std::vector<std::string> convertToBinary(const std::vector<int64_t> &intList)
{
	std::vector<std::string> binaryList;
	for (int64_t n : intList)
	{
		std::string binary;
		while (n > 0)
		{
			if(n%2 == 0)
				binary = "0" + binary;
			else
				binary = "1" + binary;

			n /= 2;
		}
		
		binaryList.push_back(binary);
	}
	
	return binaryList;
}

std::vector<std::string> onlyPalindromes(const std::vector<std::string> &binaryList)
{
	std::vector<std::string> binaryListPalindrome;
	
	for(std::string binary : binaryList)
	{
		bool palindrome = true;
		
		for (int i = 0; i < (int)(binary.size() / 2); i++)
		{
			if (binary[i] != binary[binary.size() - i - 1])
			{
				palindrome = false;
				break;
			}
		}
		
		if (palindrome)
			binaryListPalindrome.push_back(binary);
	}
	
	return binaryListPalindrome;
}



int main()
{
	std::vector<int64_t> intList;
	std::vector<std::string> binaryList;
	std::vector<std::string> binaryListPalindrome;
	
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

	std::cout << std::endl << "Binary representation: ";
	binaryList = convertToBinary(intList);
	printList(binaryList);
	
	std::cout << std::endl;

	std::cout << std::endl << "Binary representation (Palidromes): ";
	binaryListPalindrome = onlyPalindromes(binaryList);
	printList(binaryListPalindrome);
	
	std::cout << std::endl;
	
	return 0;
}