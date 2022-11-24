#include <iostream>
#include<vector>
using namespace std;

class Acceso
{
private:
	string user;
	string contra;
public:
	Acceso()
	{
		
	}
	Acceso(string user, string contra)
	{
		this->user = user;
		this->contra = contra;
	}
	
	//set 
	void setUsuario(string user)
	{
		this->user=user;
	}
	void setContrasena(string contra)
	{
		this->contra=contra;
	}
	
	//get
	string getUsuario()
	{
		return this->user;
	}
	string getContrasena()
	{
		return this->contra;
	}
};
