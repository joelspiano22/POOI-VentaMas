#include <iostream>
using namespace std;

string encriptacion(string txt)
{
	char encript;
	for(int i=0; i<txt.size(); i++)
	{
		encript = (txt[i] - 20);
		txt[i] = encript;
	}
	return txt;
}

string desencriptacion(string txt)
{
	char desencript;
	for(int i=0; i<txt.size(); i++)
	{
		desencript = (txt[i] + 20);
		txt[i] = desencript;
	}
	return txt;
}
