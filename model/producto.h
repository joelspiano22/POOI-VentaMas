#include <iostream>
#include<vector>
using namespace std;

//CLASE PRODUCTO
class Producto
{
private:
	int 	codProducto;
	string 	nomPro;
	float 	prePro;
	int 	stkPro;
	int		codCat;
public:
	Producto()
	{
		
	}
	Producto(int codProducto,string nomPro,float prePro,int stkPro,int codCat)
	{
		this->codProducto = codProducto;
		this->nomPro = nomPro;
		this->prePro = prePro;
		this->stkPro = stkPro;
		this->codCat = codCat;
	}
	//Set
	void setCodigo(int codProducto)
	{
		this->codProducto = codProducto;
	}
	void setNom(string nom)
	{
		this->nomPro = nomPro;
	}
	void setPrecio(float prePro)
	{
		this->prePro = prePro;
	}
	void setCan(int stkPro)
	{
		this->stkPro = stkPro;
	}
	void setCodCat(int codCat)
	{
		this->codCat = codCat;
	}
	//Get
	int getCodigo()
	{
		return this->codProducto;
	}
	string getNom()
	{
		return this->nomPro;
	}
	float getPrecio()
	{
		return this->prePro;
	}
	int getCan()
	{
		return this->stkPro;
	}
	int getCodiCat()
	{
		return this->codCat;
	}
};
