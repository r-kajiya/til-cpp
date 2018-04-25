#include "../../stopwatch/stopwatch.h"
#include <iostream>
#include <string>

void string_is_value ()
{
	std::string a;
	const int count = 10000000;
	a.reserve ( count + 1 );

	Stopwatch s;

	for ( int i = 0; i < count; i++ )
	{
		a += "i";
	}
	
	s.Stop ();

	std::cout << "sizeof (a) = " << sizeof ( a ) << std::endl;
	std::cout << "a.capacity() = " << a.capacity () << std::endl;
	std::cout << "a.length() = " << a.length () << std::endl;
}

int main ()
{
	string_is_value ();

	getchar ();

	return 0;
}


