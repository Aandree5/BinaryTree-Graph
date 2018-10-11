#include <iostream>

std::string combineStrings(std::string s1, std::string s2)
{
	int biggerLenght = s1.length() > s2.length() ? s1.length() : s2.length();
	std::string finalS;
	for(int i = 0; i < biggerLenght; i++)
	{
		if (i < s1.length())
			finalS += s1[i];
		if (i < s2.length())
			finalS += s2[i];
	}
	
	return finalS;
}

int main()
{
	
	std::cout << combineStrings("day", "time") << std::endl;
	
	return 0;
}

