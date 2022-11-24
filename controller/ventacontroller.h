#pragma once
#include <iostream>
#include <vector>
#include <string>
#include"../model/venta.h"
#include"../controller/clientecontroller.h"
#include"../controller/productocontroller.h"
#include "../controller/detalleventacontroller.h"
#include<fstream>
using namespace std;

//Funciones de registro venta
void registroVenta();
void agregarVenta();
void buscarVenta();
void modificarVenta();
void eliminarVenta();
void listarVenta();

//VENTA CONTROLLER
class VentaController
{
private:
	vector<Venta> vectorVenta;/*Crear el arreglo de objetos*/	
public:
	VentaController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arreglo
	void add(Venta obj)
	{
		vectorVenta.push_back(obj);
	}
	
	Venta get(int pos)
	{
		return vectorVenta[pos];
	}
	
	int size()
	{
		return vectorVenta.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorVenta[size() - 1].getCodVenta() + 1;
		}
	}
	
	int getCorrelativ()
	{
		if(size() == 0)
		{
			return 100001;
		}
		else
		{
			return 	vectorVenta[size() - 1].getCodVenta() + 100001;
		}
	}
	
	Venta buscar(int dato)
	{
		Venta objError;
		objError.setFechaVenta("Error");
		for(Venta x:vectorVenta)
		{
			if(dato == x.getCodVenta())
			{
				return x;	
			}			
		}
		return objError;
	}
	
	bool modificar(Venta ObjOld,Venta ObjNew)
	{
		for(int i=0;i<vectorVenta.size();i++)
		{
			if(ObjOld.getCodVenta() == vectorVenta[i].getCodVenta())
			{
				vectorVenta[i].setNumVenta(ObjNew.getNumVenta());
				vectorVenta[i].setCodCliente(ObjNew.getCodCliente());
				vectorVenta[i].setFechaVenta(ObjNew.getFechaVenta());
				vectorVenta[i].setEstVenta(ObjNew.getEstVenta());
				vectorVenta[i].setTotVenta(ObjNew.getTotVenta());
				return true;
			}
		}
		return false;
	}
	int getPostArray(Venta obj)
	{
		for(int i = 0;i<vectorVenta.size();i++)
		{
			if(obj.getCodVenta() == vectorVenta[i].getCodVenta())			
			{
				return i;
			}
		}
		return -1;
	}
	void eliminar(Venta objEncontrado)
	{
		vectorVenta.erase(vectorVenta.begin() + getPostArray(objEncontrado));
	}
	void grabarEnArchivo(Venta obj)
	{
		try
		{
			fstream archivoVenta;
			archivoVenta.open("factura.csv",ios::app);
			if(archivoVenta.is_open())
			{
				archivoVenta<<obj.getCodVenta()<<";"<<obj.getNumVenta()<<";"
					<<obj.getCodCliente()<<";"<<obj.getFechaVenta()<<";"
					<<obj.getEstVenta()<<";"<<obj.getTotVenta()<<";"<<endl;
				archivoVenta.close();					
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
			fstream archivoVenta;
			archivoVenta.open("factura.csv",ios::out);
			if(archivoVenta.is_open())
			{
				for(Venta x:vectorVenta)
				{	
					archivoVenta<<x.getCodVenta()<<";"<<x.getNumVenta()<<";"
						<<x.getCodCliente()<<";"<<x.getFechaVenta()<<";"
						<<x.getEstVenta()<<";"<<x.getTotVenta()<<";"<<endl;
				}
				archivoVenta.close();					
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}	
	void cargarDatosDelArchivoAlVector()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[6];
			fstream	archivoVenta;
			archivoVenta.open("factura.csv",ios::in);
			if(archivoVenta.is_open())
			{
				while(!archivoVenta.eof() && getline(archivoVenta,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Venta objVenta(stoi(temporal[0]),stoi(temporal[1]),stoi(temporal[2]),temporal[3],temporal[4],stof(temporal[5]));
					
					add(objVenta);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};


VentaController* ventaController = new VentaController();
DetalleVentaController* detalleVController = new DetalleVentaController();

//REGISTRO Venta
void registroVenta()
{
	int opt;
	do
	{
		cout<<"\t\t************OPCIONES DE VENTA************\n";
		cout<<"\t\t*****************************************\n";
		cout<<"\t\t 1. Agregar Venta   | 4. Eliminar Venta  \n";
		cout<<"\t\t 2. Buscar Venta    | 5. Listar Venta    \n";
		cout<<"\t\t 3. Modificar Venta | 6. Regresar al menu\n";
		cout<<"\t\tIngrese una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agregarVenta();break;
		case 2:system("cls");buscarVenta();break;
		case 3:system("cls");modificarVenta();break;
		case 4:system("cls");eliminarVenta();break;
		case 5:system("cls");listarVenta();break;
		case 6:cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-6]\t!!\n";cout<<endl;
		}
	} while(opt!=6);
}
void agregarVenta()
{
	string  flag;
	int 	codVenta;
	string	fechaVenta;
	int		numVenta;
	float 	totalVenta=0;
	string	estadoVenta="VENTA REGISTRADA";
	int 	opt;
	int 	opt2;
	string	palabra;
	string	palabra2;
	string	flagCliN,flagProN;
	vector  <string> found;
	vector  <string> found2;
	int 	count;
	int 	can;
	float	importe;
	int 	contador=1;
	do
	{
		codVenta = ventaController->getCorrelativo();
		numVenta = ventaController->getCorrelativ();
		cout<<"<<<<<<<<<< CODIGO DE LA VENTA ("<<codVenta<<") >>>>>>>>>>\n";
		cout<<"--------------------------------------------\n";
		cout<<"<<<<<<<< N° DE LA VENTA ("<<numVenta<<") >>>>>>>>\n\n";
		cin.ignore();
		cout<<"Fecha de venta: ";
		getline(cin,fechaVenta);
		
		cout<<"Busque el cliente que desea agregar: ";
		cin>>palabra;
		
		if(clienteController->buscarNombreCli(palabra)==true)
		{
			cout<<"Ingrese una opcion: ";
			cin>>opt;
			cout<<endl;
		}
		else{
			cout<<"Cliente no encontrado \n";
			cout<<"¿Desea buscar nuevamente? \n";
			cin>>flagCliN;
			if(flagCliN=="S"||flagCliN=="s")
			{
				system("cls");
				agregarVenta();
			}
			else{
				system("cls");
				agregarVenta();
			}
		}
		
		cout<<"Busque el producto que desea agregar: ";
		cin>>palabra2;
		
		if(productoController->buscarNombrePro(palabra2)==true)
		{
			cout<<"Seleccione el producto (codigo): ";
			cin>>opt2;
			cout<<"\nNombre del producto: "<<productoController->get(opt2-1).getNom()<<endl;
			cout<<"Precio p/u del producto: "<<productoController->get(opt2-1).getPrecio()<<endl;
			cout<<"Stock del producto: "<<productoController->get(opt2-1).getCan()<<endl;
			cout<<"Ingrese la cantidad que desea comprar: ";
			cin>>can;
			cout<<endl;
		}
		else{
			cout<<"Producto no encontrador \n";
			cout<<"¿Desea buscar nuevamente? \n";
			cin>>flagProN;
			if(flagProN=="S"||flagProN=="s")
			{
				system("cls");
				agregarVenta();
			}
			else{
				system("cls");
				agregarVenta();
			}
		}
		
		importe=productoController->get(opt2-1).getPrecio()*can;
		if(contador<=10)
		{
			for(int i = 0;i<contador;i++)
			{
				cout<<"Codigo\tNombre\tPrecio\tCantidad\tImporte\n"
					<<productoController->get(opt2-1).getCodigo()<<"\t"
					<<productoController->get(opt2-1).getNom()<<"\t"
					<<productoController->get(opt2-1).getPrecio()<<"\t"
					<<can<<"\t\t"
					<<importe<<endl;
				totalVenta=totalVenta+(productoController->get(opt2-1).getPrecio()*can);
			}
		}
		
		cout<<"Total de venta: "<<totalVenta<<endl;
		cin.ignore();
		cout<<"Estado de venta: "<<estadoVenta<<endl;
		
		cout<<"Desea realizar otra venta (S/s):";
		cin>>flag;
		if (flag=="S"|| flag=="s")
		{
			system("cls");
			agregarVenta();
			/*Crear el objeto de tipo venta*/
			Venta objVenta(codVenta,numVenta,opt,fechaVenta,estadoVenta,totalVenta);
			/*Agregar el objeto alarreglo*/
			ventaController->add(objVenta);
			//grabar en archivo
			ventaController->grabarEnArchivo(objVenta);
			
			
			/*Crear el objeto de tipo detalleventa*/
			DetalleVenta objDVenta(codVenta,opt2,productoController->get(opt2-1).getPrecio(),can,importe);
			/*Agregar el objeto alarreglo*/
			detalleVController->add(objDVenta);
			//grabar en archivo
			detalleVController->grabarEnArchivo(objDVenta);
			
		}
		else
		{
			system("cls");
			/*Crear el objeto de tipo venta*/
			Venta objVenta(codVenta,numVenta,opt,fechaVenta,estadoVenta,totalVenta);
			/*Agregar el objeto alarreglo*/
			ventaController->add(objVenta);
			//grabar en archivo
			ventaController->grabarEnArchivo(objVenta);
			
			
			/*Crear el objeto de tipo detalleventa*/
			DetalleVenta objDVenta(codVenta,opt2,productoController->get(opt2-1).getPrecio(),can,importe);
			/*Agregar el objeto alarreglo*/
			detalleVController->add(objDVenta);
			//grabar en archivo
			detalleVController->grabarEnArchivo(objDVenta);
			registroVenta();
		}
	
	} 
	while(flag == "S" || flag == "s" || flagProN !="S"||flagProN !="s");
	system("pause");
	system("cls");
}
void buscarVenta()
{
	int codVenta;
	cout<<"Ingrese codigo a buscar: ";
	cin>>codVenta;
	Venta objEncontrado = ventaController->buscar(codVenta);
	if(objEncontrado.getFechaVenta() != "Error")
	{
		cout<<"Venta encontrada:\n";
		cout<<"Codigo: "<<objEncontrado.getCodVenta()<<endl;
		cout<<"Fecha de venta: "<<objEncontrado.getFechaVenta()<<endl;
		cout<<"Numero de venta: "<<objEncontrado.getNumVenta()<<endl;
		cout<<"Total de venta: "<<objEncontrado.getTotVenta()<<endl;
		cout<<"Estado de venta: "<<objEncontrado.getEstVenta()<<endl;
		cout<<"Codigo de cliente: "<<objEncontrado.getCodCliente()<<endl;
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");
}
void modificarVenta()
{
	int codVenta;
	cout<<"Ingrese codigo a buscar: ";
	cin>>codVenta;
	Venta objEncontrado = ventaController->buscar(codVenta);
	if(objEncontrado.getFechaVenta() != "Error")
	{
		cout<<"Objeto encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodVenta()<<endl;
		cout<<"Fecha de venta: "<<objEncontrado.getFechaVenta()<<endl;
		cout<<"Numero de venta: "<<objEncontrado.getNumVenta()<<endl;
		cout<<"Total de venta: "<<objEncontrado.getTotVenta()<<endl;
		cout<<"Estado de venta: "<<objEncontrado.getEstVenta()<<endl;
		cout<<"Codigo de cliente: "<<objEncontrado.getCodCliente()<<endl;		
		/*Modificación*/
		string	fechaVenta;
		int		numVenta;
		float 	totalVenta;
		string 	estadoVenta;
		int 	codCli;
		cout<<"Modificar fecha de venta: ";
		getline(cin,fechaVenta);
		cout<<"Modificar numero de venta: ";
		cin>>numVenta;
		cout<<"Modificar total de venta: ";
		cin>>totalVenta;
		cout<<"Modificar estado de venta: ";
		getline(cin,estadoVenta);
		cout<<"Modificar codigo de cliente: ";
		cin>>codCli;
		
		Venta objNew(objEncontrado.getCodVenta(),numVenta,codCli,fechaVenta,estadoVenta,totalVenta);
		
		bool estado = ventaController->modificar(objEncontrado,objNew);
		if(estado == true)
		{	
			cout<<"Registro modificado satisfactoriamente\n";	
			/*grabar en archivo*/
			ventaController->grabarModificarEliminar();
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
	system("cls");
}
void eliminarVenta()
{
	int codVenta;
	cout<<"Ingrese codigo a eliminar: ";
	cin>>codVenta;
	Venta objEliminar = ventaController->buscar(codVenta);
	if(objEliminar.getFechaVenta() != "Error")
	{
		ventaController->eliminar(objEliminar);	
		cout<<"Registro Eliminado Satisfactoriamente!\n";
		/*Grabar en archivo*/
		ventaController->grabarModificarEliminar();
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");
}
void listarVenta()
{
	cout<<"\t Codigo de venta   Numero de venta    Nombre de cliente        Fecha   Estado de venta  Total de Venta\n";
	cout<<"\t----------------------------------------------------------------------------------------------------------\n";
	for(int i = 0;i<ventaController->size();i++)
	{
		cout<<"\t\t"<<ventaController->get(i).getCodVenta()<<"\t"
			"\t"<<ventaController->get(i).getNumVenta()<<"\t"
			"\t"<<clienteController->getClien(ventaController->get(i).getCodCliente())<<"\t"
			"\t"<<ventaController->get(i).getFechaVenta()<<"\t"
			<<ventaController->get(i).getEstVenta()<<"\t"
			<<ventaController->get(i).getTotVenta()<<endl;
	}
	system("pause");
	system("cls");	
}
