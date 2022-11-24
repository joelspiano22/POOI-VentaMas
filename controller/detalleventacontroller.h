#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include"../model/detalleventa.h"
#include"../controller/ventacontroller.h"
#include"../controller/productocontroller.h"
#include<fstream>
using namespace std;

void registroDetalleVenta();
void agregarDetalleVenta();
void buscarDetalleVenta();
void modificarDetalleVenta();
void eliminarDetalleVenta();
void listarDetalleVenta();

//TIPO_PERSONAL CONTROLLER
class DetalleVentaController
{
private:
	vector<DetalleVenta> vectorDetalleVenta;
public:
	DetalleVentaController()
	{
		archivodetalle();
	}
	//Agregar objetos al arreglo
	void add(DetalleVenta obj)
	{
		vectorDetalleVenta.push_back(obj);
	}
	
	DetalleVenta get(int pos)
	{
		return vectorDetalleVenta[pos];
	}
	
	int size()
	{
		return vectorDetalleVenta.size();
	}
	
	/*int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorDetalleVenta[size() - 1].getCodVenta() + 1;
		}
	}*/
	
	DetalleVenta buscar(int dato)
	{
		DetalleVenta objError;
		objError.setCodVenta(-1);
		for(DetalleVenta x:vectorDetalleVenta)
		{
			if(dato == x.getCodVenta())
			{
				return x;	
			}			
		}
		return objError;
	}
	
	DetalleVenta buscarpro(int dato)
	{
		DetalleVenta objError;
		objError.setCodProducto(0);
		for(DetalleVenta x:vectorDetalleVenta)
		{
			if(dato == x.getCodVenta())
			{
				return x;	
			}			
		}
		return objError;
	}
	
	bool modificar(DetalleVenta ObjOld,DetalleVenta ObjNew)
	{
		for(int i=0;i<vectorDetalleVenta.size();i++)
		{
			if(ObjOld.getCodVenta() == vectorDetalleVenta[i].getCodVenta())
			{
				vectorDetalleVenta[i].setCodProducto(ObjNew.getCodProducto());
				return true;
			}
		}
		
		return false;
	}
	
	
	void archivodetalle()
	{
		ifstream archivoDetalleVentas;
		archivoDetalleVentas.open("archivodetalleventa.csv", ios::in);
		string linea;
		char delimitador = ';';
		while(getline(archivoDetalleVentas,linea)){
			stringstream stream(linea);
			string codVenta, codProducto, cantidad,precioVenta,importe;
			getline(stream,codVenta,delimitador);
			getline(stream,codProducto,delimitador);
			getline(stream,cantidad,delimitador);
			getline(stream,precioVenta,delimitador);
			getline(stream,importe,delimitador);
			int cod=stoi(codVenta);
			int c = stoi(codProducto);
			float pre = stof(precioVenta);
			int ca= stoi(cantidad);
			float im=stof(importe);
			
			DetalleVenta Venta(cod,c,pre,ca,im);
			add(Venta);
		}
	}
	/*float TotalVenta(int cod){
			float total =0;
			for(int i=0;i<size();i++){
				if(cod == vectorDetalleVenta[i].getCodVent()){
					total = total + vectorDetalleVenta[i].getPrecioVent();
				}
			}
			return total;
		}
	*/
	int getPostArray(DetalleVenta obj)
	{
		for(int i = 0;i<vectorDetalleVenta.size();i++)
		{
			if(obj.getCodVenta() == vectorDetalleVenta[i].getCodVenta())			
			{
				return i;
			}
		}
		return -1;
	}
	void eliminar(DetalleVenta objEncontrado)
	{
		vectorDetalleVenta.erase(vectorDetalleVenta.begin() + getPostArray(objEncontrado));
	}
	void grabarEnArchivo(DetalleVenta obj)
	{
		try
		{
			fstream archivoDetalleVenta;
			archivoDetalleVenta.open("archivodetalleventa.csv",ios::app);
			if(archivoDetalleVenta.is_open())
			{
				archivoDetalleVenta<<obj.getCodVenta()<<";"<<obj.getCodProducto()<<";"<<obj.getPrecioVenta()<<";"<<obj.getCantidad()<<";"<<obj.getImporte()<<";"<<endl;
				archivoDetalleVenta.close();
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
	void grabarModificarEliminar()
	{
		try
		{
			fstream archivoDetalleVenta;
			archivoDetalleVenta.open("archivodetalleventa.csv",ios::out);
			if(archivoDetalleVenta.is_open())
			{
				for(DetalleVenta x:vectorDetalleVenta)
				{	
					archivoDetalleVenta<<x.getCodVenta()<<";"<<x.getCodProducto()<<";"<<x.getPrecioVenta()<<";"<<x.getCantidad()<<";"<<x.getImporte()<<";"<<endl;
				}
				archivoDetalleVenta.close();					
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}	
	/*void cargarDatosDelArchivoAlVector()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[4];
			fstream	archivoDetalleVenta;
			archivoDetalleVenta.open("archivodetalleventa.csv",ios::in);
			if(archivoDetalleVenta.is_open())
			{
				while(!archivoDetalleVenta.eof() && getline(archivoDetalleVenta,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					DetalleVenta objDetalleVenta(stoi(temporal[0]),stoi(temporal[1]),
												 stof(temporal[2]),stoi(temporal[3]),stof(temporal[4]));
					add(objDetalleVenta);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}*/
};


DetalleVentaController* detalleVentaController = new DetalleVentaController();
//REGISTRO DETALLE_VENTA
void registroDetalleVenta()
{
	int opt;
	do
	{
		cout<<"OPCIONES DE DETALLE VENTA\n";
		cout<<"-------------------"<<endl;
		cout<<"Listar Detalle de Venta*******[1]\n";
		cout<<"Salir*************************[2]\n";
		cout<<"Ingrese una opción [1-2]:";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");listarDetalleVenta();break;
		case 2:cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-6]\t!!\n";cout<<endl;
		}
	} while(opt!=2);
}
/*void agregarDetalleVenta()
{
	string  flag;
	int 	codVenta;
	int 	codProducto;
	int		cantidad;
	float 	precioVenta;
	float 	importe;
	int 	opt1;
	int		opt2;
	do
	{
		codVenta = detalleVentaController->getCorrelativo();
		cout<<"<<<<<<<<<< CODIGO DEL DETALLE DE VENTA ("<<codVenta<<") >>>>>>>>>>\n";
		cout<<"-----------------------------------------------------\n\n";
		cin.ignore();
		cout<<"Codigo de Producto: ";
		cin>>codProducto;
		cout<<"Cantidad: ";
		cin>>cantidad;
		cout<<"precio de venta: ";
		cin>>precioVenta;
		
		for (int i=0;i<ventaController->size();i++)
		{
			cout<<ventaController->get(i).getCodVenta()<<endl;
		}
		cout<<"Ingrese una opcion: ";
		cin>>opt1;
		
		for (int i=0;i<productoController->size();i++)
		{
			cout<<productoController->get(i).getCodigo()<<endl;
		}
		cout<<"Ingrese una opcion: ";
		cin>>opt2;
		
		cout<<"Continuar(S/s):";
		cin>>flag;
		//Crear el objeto de tipo alumno
		DetalleVenta objDetalleVenta(codVenta,codProducto,precioVenta, cantidad, importe);
		//Agregar el objeto al arreglo
		detalleVentaController->add(objDetalleVenta);
		//grabar en archivo
		detalleVentaController->grabarEnArchivo(objDetalleVenta);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}*/

void buscarDetalleVenta()
{
	/*int codVenta;
	cout<<"Ingrese codigo a buscar:";
	cin>>codVenta;
	DetalleVenta objEncontrado = detalleVentaController->buscar(codVenta);
	if(objEncontrado.getCodProducto() != -1)
	{
		cout<<"Detalle Venta encontrado:\n";
		cout<<"Codigo de Venta: "<<objEncontrado.getCodVenta()<<endl;
		cout<<"Codigo de Producto "<<objEncontrado.getCodProducto()<<endl;
		cout<<"Cantidad: "<<objEncontrado.getCantidad()<<endl;
		cout<<"Precio de Producto: "<<objEncontrado.getPrecioVenta()<<endl;
		cout<<"Importe de la Venta: "<<objEncontrado.getImporte()<<endl;
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");*/
}
void modificarDetalleVenta()
{
	/*int codVenta;
	cout<<"Ingrese codigo a buscar:";
	cin>>codVenta;
	DetalleVenta objEncontrado = detalleVentaController->buscar(codVenta);
	if(objEncontrado.getCodProducto() != -1)
	{
		cout<<"Detalle Venta encontrado:\n";
		cout<<"Codigo de Venta: "<<objEncontrado.getCodVenta()<<endl;
		cout<<"Codigo de Producto "<<objEncontrado.getCodProducto()<<endl;
		cout<<"Cantidad: "<<objEncontrado.getCantidad()<<endl;
		cout<<"Precio del Producto: "<<objEncontrado.getPrecioVenta()<<endl;
		cout<<"Importe del Producto: "<<objEncontrado.getImporte()<<endl;
		//Modificación
		int 	codProducto;
		int 	cantidad;
		float 	precioVenta;
		float	importe;
		
		cin.ignore();
		cout<<"Modificar Codigo de Producto:";
		cin>>codProducto;
		cout<<"Modificar cantidad:";
		cin>>cantidad;
		cout<<"Modificar precio de venta:";
		cin>>precioVenta;
		importe=cantidad*precioVenta;
		DetalleVenta objNew(objEncontrado.getCodVenta(),codProducto,cantidad,precioVenta,importe);
		
		bool estado = detalleVentaController->modificar(objEncontrado,objNew);
		if(estado == true)								
		{
			cout<<"Registro modificado satisfactoriamente\n";	
			//grabar en archivo
			detalleVentaController->grabarModificarEliminar();
		}
		else
		{
			cout<<"No se Modifico el registro\n";	
		}
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");*/
}
void eliminarDetalleVenta()
{
	/*int codVenta;
	cout<<"Ingrese codigo a eliminar:";
	cin>>codVenta;
	DetalleVenta objEliminar = detalleVentaController->buscar(codVenta);
	if(objEliminar.getCodProducto() != -1)
	{
		detalleVentaController->eliminar(objEliminar);	
		cout<<"Registro Eliminado Satisfactoriamente!\n";
		//Grabar en archivo
		detalleVentaController->grabarModificarEliminar();
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");	*/	
}
void listarDetalleVenta()
{
	cout<<"\t Codigo de venta   Nombre de producto     Precio unitario      Cantidad        Total de Venta\n";
	cout<<"\t---------------------------------------------------------------------------------------------\n";
	for(int i = 0;i<detalleVentaController->size();i++)
	{
		cout<<"\t\t"<<detalleVentaController->get(i).getCodVenta()<<"\t\t"<<productoController->getNomPro(detalleVentaController->get(i).getCodProducto())<<"\t"
			"\t\t"<<detalleVentaController->get(i).getCantidad()<<"\t"
			<<"\t\t"<<detalleVentaController->get(i).getPrecioVenta()<<"\t"
			"\t"<<detalleVentaController->get(i).getPrecioVenta()<<endl;
	}
	system("pause");
	system("cls");
}
