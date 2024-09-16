#include <iostream>
// #include <cstdlib> - system services

using namespace std;

int recursive_sum(int m, int n)
{
	if (m == n)
		return n;
	return m + recursive_sum(m + 1, n);
}

// Sum numbers between m and n
int main()
{
	int	m, m_cpy, n, sum;

	cout << "Enter the min number m ";
	cin >> m;
	cout << endl << "Enter the max number n ";
	cin >> n;

	m_cpy = m;

	cout << endl << " Recursive Sum is: " << recursive_sum(m, n) << endl;

	m = m_cpy;

	sum = 0;
	for (m; m <= n; m++)
		sum += m;

	cout << " Sum is: " << sum << endl;

	// system("pause>0");
}
