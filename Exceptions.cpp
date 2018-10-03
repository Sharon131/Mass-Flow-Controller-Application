#include "Exceptions.hpp"

Exception::Exception():
	Message("Problemy z aplikacj�. Spr�buj uruchomi� ponownie.")
{
	;
}

Exception::Exception(string newMessage):
	Message(newMessage)
{
	;
}

Exception::~Exception()
{
	;
}

string Exception::getMessage()
{
	return Message;
}

void Exception::reportException()
{
	MessageBox(NULL, Message.c_str(), "Uwaga!", MB_ICONEXCLAMATION);
}
