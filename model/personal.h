#include <iostream>
#include<vector>
using namespace std;

//CLASE PERSONAL
class Personal
{
private:
	int     codPersonal;
	string  nomApePer;
	int     dniPer;
	float   suePer;
	int 	codTipPer;
public:
	Personal()
	{
		
	}
	Personal(int codPersonal, string nomApePer, int dniPer, float suePer, int codTipPer)
	{
		this->codPersonal = codPersonal;
		this->nomApePer   = nomApePer;
		this->dniPer 	  = dniPer;
		this->suePer      = suePer;
		this->codTipPer   = codTipPer;
	}
	//Set
	void setCodPersonal(int codPersonal)
	{
		this->codPersonal = codPersonal;
	}
	void setNomApePer(string nomApePer)
	{
		this->nomApePer = nomApePer;
	}
	void setDniPer(int dniPer)
	{
		this->dniPer = dniPer;
	}
	void setSuePer(float suePer)
	{
		this->suePer = suePer;
	}
	void setCodTipPer(int codTipPer)
	{
		this->codTipPer = codTipPer;
	}
	//Get
	int getCodPersonal()
	{
		return this->codPersonal;
	}
	string getNomApePer()
	{
		return this->nomApePer;
	}
	int getDniPer()
	{
		return this->dniPer;
	}
	float getSuePer()
	{
		return this->suePer;
	}
	int getCodTipPer()
	{
		return this->codTipPer;
	}
};
