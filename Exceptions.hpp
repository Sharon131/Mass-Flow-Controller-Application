#ifndef EXCEPTIONS
#define EXCEPTIONS
#include<Windows.h>
#include<string>

using namespace std;

class Exception {
	string Message;

public:
	Exception();
	Exception(string newMessage);
	~Exception();

	string getMessage();
	
	void reportException();
};

#endif