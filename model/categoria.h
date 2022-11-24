#include <iostream>
#include<vector>
using namespace std;

//CLASE CATEGORIA
class Categoria
{
private:
	int codCat;
	string nomCat;
public:
	Categoria()
	{
		
	}
	Categoria(int codCat,string nomCat)
	{
		this->codCat = codCat;
		this->nomCat = nomCat;
	}
	//Set
	void setCodCat(int codCat)
	{
		this-> codCat = codCat;
	}
	void setNomCat(string nomCat)
	{
		this-> nomCat = nomCat;
	}
	//Get
	int getCodCat()
	{
		return this->codCat;
	}
	string getNomCat()
	{
		return this->nomCat;
	}
};
