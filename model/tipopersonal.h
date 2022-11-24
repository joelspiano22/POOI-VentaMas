#include <iostream>
#include <vector>
using namespace std;

//CLASE TIPO_PERSONAL
class TipoPersonal
{
private:
	int codTipPer;
	string nomTipPer;
public:
	TipoPersonal()
	{
		
	}
	TipoPersonal(int codTipPer,string nomTipPer)
	{
		this->codTipPer = codTipPer;
		this->nomTipPer = nomTipPer;
	}
	//Set
	void setCodTipPer(int codTipPer)
	{
		this->codTipPer = codTipPer;
	}
	void setNomTipPer(string nomTipPer)
	{
		this-> nomTipPer = nomTipPer;
	}
	//Get
	int getCodTipPer()
	{
		return this->codTipPer;
	}
	string getNomTipPer()
	{
		return this->nomTipPer;
	}
};
