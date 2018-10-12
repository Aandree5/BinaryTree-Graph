#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using LINE = vector<char>;
using MATRIX = vector<LINE>;

int main()
{
	vector<MATRIX> m = vector<MATRIX>();
	
	// READ FILE
	ifstream f;  
	f.open ("matrix.txt");
	string l;
	MATRIX tm = MATRIX();
	while (getline (f, l))
	{
		if(l == "")
		{
			m.push_back(tm);
			tm.clear();
		}
		else
		{
			LINE t = LINE();
			for(char c : l)
				if (c != ' ')
					t.push_back(c);

			tm.push_back(t);
		}
	}
	m.push_back(tm);
	f.close();
	
	
	// PRINT SPIRAL
	for(MATRIX sm : m)
	{
		int i, c = 0, l = 0, C = sm.size(), L = sm.size();
		
		while(c < C && l < L)
		{
			for(i = (l > c ? l : c); i < (l > c ? L : C); i++)
			{
				cout << sm[(l > c ? i : l)][(l > c ? l : i)] << " ";
			}
 			l > c ? C-- : l++;
			cout << endl;
		}
		
		cout << endl;
	}
	
	
// 		for(MATRIX sm : m)
// 	{
// 		int i, c = 0, l = 0, C = sm.size(), L = sm.size();
		
// 		while(c < C && l < L)
// 		{
// 			for(i = c; i < C; i++)
// 			{
// 				cout << sm[l][i] << " ";
// 			}
//  		l++;
// 			cout << endl;
// 		}
		
// 		cout << endl;
// 	}
	
	
	
	
	
	// TEST PRINT LOADED FILE
// 	int i = 0;
// 	for(vector<vector<char>> sm : m)
// 	{
// 		cout << to_string(i) << endl;
		
// 		for(vector<char> v : sm)
// 		{
// 			for (char c : v)
// 				cout << c;
// 			cout << endl;
// 		}
// 		cout << endl;
		
// 		i++;
// 	}
	
	
	
	return 0;
}
