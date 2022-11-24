#include <iostream>
#include<vector>
using namespace std;

//CLASE VENTA
class Venta
{
private:
	int 	codVenta;
	int 	numVenta;
	int 	codCliente;
	string 	fechaVenta;
	string 	estVenta;
	float 	totVenta;
public:
	Venta()
	{
		
	}
	Venta(int codVenta,int numVenta,int codCliente,string fechaVenta,string estVenta,float totVenta)
	{
		this->codVenta=codVenta;
		this->numVenta=numVenta;
		this->codCliente=codCliente;
		this->fechaVenta=fechaVenta;
		this->estVenta=estVenta;
		this->totVenta=totVenta;
	}
	//Set
	void setCodVenta(int codVenta)
	{
		this->codVenta = codVenta;  
	}
	void setNumVenta(int numVenta)
	{
		this->numVenta = numVenta;  
	}
	void setCodCliente(int codCliente)
	{
		this->codCliente = codCliente;  
	}
	void setFechaVenta(string fechaVenta)
	{
		this->fechaVenta = fechaVenta;  
	}
	void setEstVenta(string estVenta)
	{
		this->estVenta = estVenta;  
	}
	void setTotVenta(float totVenta)
	{
		this->totVenta = totVenta;  
	}
	//Get
	int getCodVenta()
	{
		return this->codVenta;
	}
	int getNumVenta()
	{
		return this->numVenta;
	}
	int getCodCliente()
	{
		return this->codCliente;
	}
	string getFechaVenta()
	{
		return this->fechaVenta;
	}
	string getEstVenta()
	{
		return this->estVenta;
	}
	float getTotVenta()
	{
		return this->totVenta;
	}
};
