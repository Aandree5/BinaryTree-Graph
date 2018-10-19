#include <iostream>
#include <vector>

using namespace std;

vector<int> addPolinomials(vector<int> P1, vector<int> P2)
{
	vector<int> res;

	for (int m = 0; m < (P1.size() - 1) + (P2.size() - 1) + 1; m++)
		res.push_back(0);
	
	
	for (int i = 0; i < P1.size(); i++)
	{
		for (int j = 0; j < P2.size(); j++)
		{
			res[i+j] += P1[i] * P2[j];
		}
	}

	return res;
}


int main()
{
	vector<int> P1 = { 3, 1, 9 };
	vector<int> P2 = { 2, 1, 2, 1 };

	vector<int> P = addPolinomials(P1, P2);
	
	for (int m = 0; m < P.size(); m++)
		cout << P[m] << " ";
	
	cout << endl;


	return 0;
}


// WITH POINTERS (NOT WORKING)

// #include <iostream>
// #include <memory>

// using namespace std;

// unique_ptr<int[]>  addPolinomials(unique_ptr<int[]> &P1, unique_ptr<int[]> &P2)
// {
// 	unique_ptr<int[]> res(new int[((sizeof P1) - 1) + ((sizeof P2) - 1) + 1]);

// 	for (int m = 0; m < sizeof res; m++)
// 		res[m] = 0;
	
	
// 	for (int i = 0; i < sizeof P1; i++)
// 	{
// 		for (int j = 0; j < sizeof P2; j++)
// 		{
// 			res[i+j] += P1[i] * P2[j];
// 		}
// 	}

// 	return res;
// }


// int main()
// {
// 	unique_ptr<int[]> P1(new int[3]{ 3, 1, 9 });
// 	unique_ptr<int[]> P2(new int[4]{ 2, 1, 2, 1 });

// 	unique_ptr<int[]> P = addPolinomials(P1, P2);

	
// 	for (int m = 0; m < sizeof P; m++)
// 		cout << P[m] << " ";
	
// 	cout << endl;


// 	return 0;
// }
