void int main()
{
	std::cout << combineStrings("day", "time");
	return 0;
}

void combineStrings(string s1, string s2)
{
	int biggerLenght = s1.lenght() ? s1.lenght() > s2.lenght() : s2.lenght();
	string finalS;
	for(int i = 0; i < biggerLenght; i++)
	{
		finalS += (finalS + s1[i]) ? i < s1.lenght();
		finalS += (finalS + s2[i]) ? i < s2.lenght();
	}
	
	return finalS;
}