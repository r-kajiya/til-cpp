// 64bit環境想定

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct NonPack
{
	short s;
	char c;
	double d;
	int i;
};

#pragma pack(1)
struct Pack
{
	short s;
	char c;
	double d;
	int i;
};

int main()
{
	cout << "char:" << sizeof(char) << "byte" << endl;
	cout << "short:" << sizeof(short) << "byte" << endl;
	cout << "int:" << sizeof(int) << "byte" <<endl;
	cout << "double:" << sizeof(double) << "byte" << endl;
	cout << "NonPack:" << sizeof(NonPack) << "byte" << endl;
	cout << "Pack:" << sizeof(Pack) << "byte" << endl;

	const int LOOP_COUNT = 1000000000;

	system_clock::time_point start, end;

	start = system_clock::now();

	NonPack *non_pack = new NonPack;

	for (int i = 0; i < LOOP_COUNT; i++)
	{
		if (non_pack != nullptr)
		{
			non_pack->s++;
			non_pack->c++;
			non_pack->d++;
			non_pack->i++;
		}
	}

	delete non_pack;

	end = system_clock::now();

	auto elapse = duration_cast<milliseconds>(end - start).count();

	cout << "NonPack Access Time:" << elapse << "ms" << endl;

	start = system_clock::now();

	Pack *pack = new Pack;

	for (int i = 0; i < LOOP_COUNT; i++)
	{
		if (pack != nullptr)
		{
			pack->s++;
			pack->c++;
			pack->d++;
			pack->i++;
		}
	}

	delete pack;

	end = system_clock::now();

	elapse = duration_cast<milliseconds>(end - start).count();

	cout << "Pack Access Time:" << elapse << "ms" << endl;

	getchar();

    return 0;
}

