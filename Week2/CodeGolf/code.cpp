#include <iostream>
#include <fstream>

using namespace std;

char p[25];
char t[25];

int main()
{
	ifstream f("plain.txt");
	string s;
	int x = 0;
	while (getline(f, s))
		for (int l = 0; l < 5; l++)
			p[x++] = s[l];
	
	cout << "Generations? ";
	cin >> x;
	
	for(int h = 0; h < x; h++)
	{
		for(int i = 0; i < 25; i++)
				t[i] = p[i] == 'H' & (p[i - 1] == 'I' || p[i + 1] == 'I' || p[i - 5] == 'I' || p[i + 5] == 'I') ? 'I' : (p[i] != 'I' ? 'H': 'F');
	
		for(int i = 0; i < 25; i++)
				p[i] = t[i];
	}
	
	for(int i = 0; i < 25; i++)
		cout << p[i] << ((i + 1) % 5 == 0 ? "\n" : " ");
	
	return 0;
}