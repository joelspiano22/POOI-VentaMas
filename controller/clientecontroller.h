#pragma once
#include <iostream>
#include <vector>
#include"../model/cliente.h"
#include"../controller/categoriacontroller.h"
#include<fstream>
using namespace std;

//Funciones de registro cliente
void registroCliente();
void agregarCliente();
void buscarCliente();
void modificarCliente();
void eliminarCliente();
void listarCliente();

//CLIENTE CONTROLLER
class ClienteController
{
private:
	vector<Cliente> vectorCliente;/*Crear el arreglo de objetos*/	
public:
	ClienteController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arreglo
	void add(Cliente obj)
	{
		vectorCliente.push_back(obj);
	}
	
	Cliente get(int pos)
	{
		return vectorCliente[pos];
	}
	
	int size()
	{
		return vectorCliente.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorCliente[size() - 1].getCodCli() + 1;
		}
	}
	
	Cliente buscar(int dato,int inf, int sup)
	{
		int center;
		Cliente objError;
		objError.setNomApeCli("Error");
		if(inf>sup)
		{
			return objError;
		}
		else
		{
			center=(inf+sup)/2;
			if(vectorCliente[center].getCodCli()==dato)
			{
				return vectorCliente[center];
			}
			else if(vectorCliente[center].getCodCli()<dato)
			{
				return buscar(dato,center+1,sup);
			}
			else
			{
				return buscar(dato,inf,center-1);
			}
		}
	}
	
	bool modificar(Cliente ObjOld,Cliente ObjNew)
	{
		for(int i=0;i<vectorCliente.size();i++)
		{
			if(ObjOld.getCodCli() == vectorCliente[i].getCodCli())
			{
				vectorCliente[i].setNomApeCli(ObjNew.getNomApeCli());
				vectorCliente[i].setDirCli(ObjNew.getDirCli());
				vectorCliente[i].setRucCli(ObjNew.getRucCli());
				return true;
			}
		}
		return false;
	}
	int getPostArray(Cliente obj)
	{
		for(int i = 0;i<vectorCliente.size();i++)
		{
			if(obj.getCodCli() == vectorCliente[i].getCodCli())			
			{
				return i;
			}
		}
		return -1;
	}
	bool buscarNombreCli(string nombre)
	{ 
		bool busca = false;
		int cont = 0;  
		for(Cliente x:vectorCliente)
		{
			size_t found = (x.getNomApeCli()).find(nombre);
			if (found != string::npos)
			{  if(cont<1)
			{
				cout<<"\n";
				cout<<"\t     CODIGO           NOMBRE             DIRECCION     \t|      RUC      \n\n"; 
				cont++;
			}
			cout<<"\t\t"<<x.getCodCli()<<"\t\t"<<x.getNomApeCli()<<"\t\t"<<x.getDirCli()<<"\t\t"<<x.getRucCli()<<endl;
			busca = true;
			}
		}
		if(busca == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void eliminar(Cliente objEncontrado)
	{
		vectorCliente.erase(vectorCliente.begin() + getPostArray(objEncontrado));
	}
	string getClien(int opt)
	{
		for(int i=0;i<size();i++)
		{
			if(opt == vectorCliente[i].getCodCli())
			{
				return vectorCliente[i].getNomApeCli();
			}
		}
		return "Error";
	}
	void grabarEnArchivo(Cliente obj)
	{
		try
		{
			fstream archivoCliente;
			archivoCliente.open("clientes.csv",ios::app);
			if(archivoCliente.is_open())
			{
				archivoCliente<<obj.getCodCli()<<";"<<obj.getNomApeCli()<<";"<<obj.getDirCli()<<";"<<obj.getRucCli()<<";"<<endl;
				archivoCliente.close();					
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
			fstream archivoCliente;
			archivoCliente.open("clientes.csv",ios::out);
			if(archivoCliente.is_open())
			{
				for(Cliente x:vectorCliente)
				{	
					archivoCliente<<x.getCodCli()<<";"<<x.getNomApeCli()<<";"<<x.getDirCli()<<";"<<x.getRucCli()<<";"<<endl;
				}
				archivoCliente.close();					
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
			string 	temporal[4];
			fstream	archivoCliente;
			archivoCliente.open("clientes.csv",ios::in);
			if(archivoCliente.is_open())
			{
				while(!archivoCliente.eof() && getline(archivoCliente,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Cliente objCliente(stoi(temporal[0]),temporal[1],temporal[2],temporal[3]);
					
					add(objCliente);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};

ClienteController*   clienteController   = new ClienteController();

//MENU REGISTRO DE CLIENTE
void registroCliente()
{
	int opt;
	do
	{
		cout<<"\t\t*************OPCIONES DE CLIENTE*************\n";
		cout<<"\t\t*********************************************\n";
		cout<<"\t\t 1. Agregar Cliente   | 4. Eliminar Cliente  \n";
		cout<<"\t\t 2. Buscar Cliente    | 5. Listar Cliente    \n";
		cout<<"\t\t 3. Modificar Cliente | 6. Regresar al menu  \n";
		cout<<"\t\tIngrese una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agregarCliente();break;
		case 2:system("cls");buscarCliente();break;
		case 3:system("cls");modificarCliente();break;
		case 4:system("cls");eliminarCliente();break;
		case 5:system("cls");listarCliente();break;
		case 6:cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-6]\t!!\n";cout<<endl;
		}
	} while(opt!=6);
	system("cls");
}
void agregarCliente()
{
	string  flag;
	int 	codCli;
	string 	nomApeCli;
	string	dirCli;
	string	rucCli;
	do
	{
		codCli = clienteController->getCorrelativo();
		cout<<"<<<<<<<<<< CODIGO DEL CLIENTE ("<<codCli<<") >>>>>>>>>>\n";
		cout<<"--------------------------------------------\n\n";
		cin.ignore();
		cout<<"Nombres y Apellidos: ";
		getline(cin,nomApeCli);
		cout<<"Direccion: ";
		getline(cin,dirCli);
		cout<<"RUC: ";
		getline(cin,rucCli);
		cout<<"Continuar(S/s):";
		cin>>flag;
		/*Crear el objeto de tipo alumno*/
		Cliente objCliente(codCli,nomApeCli,dirCli,rucCli);
		/*Agregar el objeto alarreglo*/
		clienteController->add(objCliente);
		//grabar en archivo
		clienteController->grabarEnArchivo(objCliente);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}

void buscarCliente()
{
	int codCli;
	int inferior=0;
	int superior=clienteController->size()-1;
	cout<<"Ingrese codigo a buscar: ";
	cin>>codCli;
	Cliente objEncontrado = clienteController->buscar(codCli,inferior,superior);
	if(objEncontrado.getNomApeCli() != "Error")
	{
		cout<<"Cliente encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodCli()<<endl;
		cout<<"Nombres y Apellidos: "<<objEncontrado.getNomApeCli()<<endl;
		cout<<"Direccion: "<<objEncontrado.getDirCli()<<endl;
		cout<<"RUC: "<<objEncontrado.getRucCli()<<endl;
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");
}
void modificarCliente()
{
	int codCli;
	int inferior=0;
	int superior=clienteController->size()-1;
	cout<<"Ingrese codigo a buscar: ";
	cin>>codCli;
	Cliente objEncontrado = clienteController->buscar(codCli,inferior,superior);
	if(objEncontrado.getNomApeCli() != "Error")
	{
		cout<<"Objeto encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodCli()<<endl;
		cout<<"Nombres y Apellidos: "<<objEncontrado.getNomApeCli()<<endl;
		cout<<"Direccion: "<<objEncontrado.getDirCli()<<endl;		
		cin.ignore();
		cout<<"RUC: "<<objEncontrado.getRucCli()<<endl;	
		/*Modificación*/
		string 	nomApeCli;
		string 	dirCli;
		string  rucCli;
		cout<<"Modificar Nombres y Apellidos: ";
		getline(cin,nomApeCli);
		cout<<"Modificar Direccion: ";
		getline(cin,dirCli);
		cout<<"Modificar RUC: ";
		getline(cin,rucCli);
		
		Cliente objNew(objEncontrado.getCodCli(),nomApeCli,dirCli,rucCli);
		
		bool estado = clienteController->modificar(objEncontrado,objNew);
		if(estado == true)
		{
			cout<<"Registro modificado satisfactoriamente\n";	
			/*grabar en archivo*/
			clienteController->grabarModificarEliminar();
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
void eliminarCliente()
{
	int codCli;
	int inferior=0;
	int superior=clienteController->size()-1;
	cout<<"Ingrese codigo a eliminar: ";
	cin>>codCli;
	Cliente objEliminar = clienteController->buscar(codCli,inferior,superior);
	if(objEliminar.getNomApeCli() != "Error")
	{
		clienteController->eliminar(objEliminar);	
		cout<<"Registro Eliminado Satisfactoriamente!\n";
		/*Grabar en archivo*/
		clienteController->grabarModificarEliminar();
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");		
}
void listarCliente()
{
	cout<<"Codigo de cliente    Nombre de cliente      Direccion        RUC\n";
	for(int i = 0;i<clienteController->size();i++)
	{
		cout<<"\t"<<clienteController->get(i).getCodCli()<<"\t"
			"\t"<<clienteController->get(i).getNomApeCli()<<"\t"
			<<clienteController->get(i).getDirCli()<<"\t"
			<<clienteController->get(i).getRucCli()<<endl;
	}
	system("pause");
	system("cls");	
}
