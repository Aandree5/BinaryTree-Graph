#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using LINE = vector<char>;
using MATRIX = vector<LINE>;

int main()
{
	vector<MATRIX> m;
	
	// READ FILE
	ifstream f;  
	f.open ("matrix.txt");
	if (f.is_open())
	{
		string l;
		MATRIX tm;
		while (getline (f, l))
		{
			LINE t;
			
			if(l == "")
			{
				m.push_back(tm);
				tm.clear();
			}
			else
			{
				for(char c : l)
					if (c != ' ')
						t.push_back(c);

				tm.push_back(t);
			}
		}
		
		m.push_back(tm);
		f.close();
	}
	
	
	// PRINT SPIRAL
	for(MATRIX sm : m)
	{
		int i, c, l = 0;
		int C, L = sm.size();
		while(c < C && l < L)
		{
// 			for(i = l; i < C; i++)
// 			{
// 				cout << to_string(sm[c][i]);
// 			}
			cout << endl << to_string(sm.size());
			cout << sm[0][0] << endl;
 			l++;
		}
	}
	
	
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
