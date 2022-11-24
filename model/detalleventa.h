#include <iostream>
#include<vector>
using namespace std;

//CLASE VENTA
class DetalleVenta
{
private:
	int 	codVenta;
	int 	codProducto;
	float 	precioVenta;
	int 	cantidad;
	float	importe;
public:
	DetalleVenta()
	{
		
	}
	DetalleVenta(int codVenta,int codProducto,float precioVenta,int cantidad,float importe)
	{
		this->codVenta=codVenta;
		this->codProducto=codProducto;
		this->precioVenta=precioVenta;
		this->cantidad=cantidad;
		this->importe=importe;
	}
	//Set
	void setCodVenta(int codVenta)
	{
		this->codVenta=codVenta;
	}
	void setCodProducto(int codProducto)
	{
		this->codProducto=codProducto;
	}
	void setPrecioVenta(float precioVenta)
	{
		this->precioVenta=precioVenta;
	}
	void setCantidad(int cantidad)
	{
		this->cantidad=cantidad;
	}
	void setImporte(float importe)
	{
		this->importe=importe;
	}
	//Get 
	int getCodVenta()
	{
		return this->codVenta;
	}
	int getCodProducto()
	{
		return this->codProducto;
	}
	float getPrecioVenta()
	{
		return this->precioVenta;
	}
	int getCantidad()
	{
		return this->cantidad;
	}
	float getImporte()
	{
		return this->importe;
	}
};
