#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

static const int LOOP_COUNT = 100000000;

void main()
{
	auto start = system_clock::now();

	int i = 0;

	for (int count = 0; count < LOOP_COUNT; count++)
	{
		i += 20;
	}

	auto end = system_clock::now();

	auto diff = end - start;

	auto elapsed = duration_cast<milliseconds>(diff).count();

	cout << "int:" << elapsed << "ms" << endl;

	start = system_clock::now();

	double d = 0;

	for (int count = 0; count < LOOP_COUNT; count++)
	{
		d += 20;
	}
	
	end = chrono::system_clock::now();

	diff = end - start;

	elapsed = duration_cast<milliseconds>(diff).count();

	cout << "double:" << elapsed << "ms" << endl;

	getchar();
}

