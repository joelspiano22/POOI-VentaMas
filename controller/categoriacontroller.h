#pragma once
#include <iostream>
#include <vector>
#include"../model/categoria.h"
#include<fstream>
using namespace std;

void registroCategoria();
void agregarCategoria();
void buscarCategoria();
void modificarCategoria();
void eliminarCategoria();
void listarCategoria();

//CATEGORIA CONTROLLER
class CategoriaController
{
private:
	vector<Categoria> vectorCategoria;
public:
	CategoriaController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arreglo
	void add(Categoria obj)
	{
		vectorCategoria.push_back(obj); //El punto es para a los metodos o propiedades de un objeto 
	}
	
	Categoria get(int pos)
	{
		return vectorCategoria[pos];
	}
	
	int size()
	{
		return vectorCategoria.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorCategoria[size() - 1].getCodCat() + 1;
		}
	}
	
	Categoria buscar(int dato,int inf,int sup)
	{
		int center;
		Categoria objError;
		objError.setNomCat("Error");
		if(inf>sup)
		{
			return objError;
		}
		else
		{
			center=(inf+sup)/2;
			if(vectorCategoria[center].getCodCat()==dato)
			{
				return vectorCategoria[center];
			}
			else if(vectorCategoria[center].getCodCat()<dato)
			{
				return buscar(dato,center+1,sup);
			}
			else
			{
				return buscar(dato,inf,center-1);
			}
		}
	}
	
	
	bool modificar(Categoria ObjOld,Categoria ObjNew)
	{
		for(int i=0;i<vectorCategoria.size();i++)
		{
			if(ObjOld.getCodCat() == vectorCategoria[i].getCodCat())
			{
				vectorCategoria[i].setNomCat(ObjNew.getNomCat());
				return true;
			}
		}
		return false;
	}
	int getPostArray(Categoria obj)
	{
		for(int i = 0;i<vectorCategoria.size();i++)
		{
			if(obj.getCodCat() == vectorCategoria[i].getCodCat())			
			{
				return i;
			}
		}
		return -1;
	}
	void eliminar(Categoria objEncontrado)
	{
		vectorCategoria.erase(vectorCategoria.begin() + getPostArray(objEncontrado));
	}
	
	string getCate(int opt){
		for(int i=0;i<size();i++){
			if(opt == vectorCategoria[i].getCodCat())
			{
				return vectorCategoria[i].getNomCat();
			}
		}
		return "Error";
	}
		
		void grabarEnArchivo(Categoria obj)
		{
			try
			{
				fstream archivoCategoria;
				archivoCategoria.open("archivocategoria.csv",ios::app);
				if(archivoCategoria.is_open())
				{
					archivoCategoria<<obj.getCodCat()<<";"<<obj.getNomCat()<<";"<<endl;
					archivoCategoria.close();					
				}
			}
			catch(exception e)
			{
				cout<<"Ocurrio un error al grabar el archivo01";
			}
		}
		void grabarModificarEliminar()
		{
			try
			{
				fstream archivoCategoria;
				archivoCategoria.open("archivocategoria.csv",ios::out);
				if(archivoCategoria.is_open())
				{
					for(Categoria x:vectorCategoria) //la x es como si fuera el arrae(siendo una colección)
					{	
						archivoCategoria<<x.getCodCat()<<";"<<x.getNomCat()<<";"<<endl;
					}
					archivoCategoria.close();					
				}
			}
			catch(exception e)
			{
				cout<<"Ocurrio un error al grabar el archivo02";
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
				fstream	archivoCategoria;
				archivoCategoria.open("archivocategoria.csv",ios::in);
				if(archivoCategoria.is_open())
				{
					while(!archivoCategoria.eof() && getline(archivoCategoria,linea))
					{
						i = 0;
						while((posi = linea.find(";")) != string::npos)
						{
							temporal[i] = linea.substr(0,posi);
							linea.erase(0,posi+1);
							++i;
						}
						Categoria objCategoria(stoi(temporal[0]),temporal[1]);
						
						add(objCategoria);
					}
				}
			}
			catch(exception e)
			{
				cout<<"Ocurrio un error al grabar el archivo03";
			}
		}
};

CategoriaController* categoriaController = new CategoriaController(); //EL NEW ES PARA RESERVAR EN LA MEMORIA DINÁMICA, que sirve para reservar
//la cantidad de memoria exacta en el preciso instante en donde se necesite
//GENERAR CATEGORÍA
void registroCategoria()
{
	int opt;
	do
	{
		cout<<"\t\t**************OPCIONES DE CATEGORIA**************\n";
		cout<<"\t\t*************************************************\n";
		cout<<"\t\t 1. Agregar Categoria   | 4. Eliminar Categoria  \n";
		cout<<"\t\t 2. Buscar Categoria    | 5. Listar Categoria    \n";
		cout<<"\t\t 3. Modificar Categoria | 6. Regresar al menu    \n";
		cout<<"\t\tIngrese una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agregarCategoria();break;
		case 2:system("cls");buscarCategoria();break;
		case 3:system("cls");modificarCategoria();break;
		case 4:system("cls");eliminarCategoria();break;
		case 5:system("cls");listarCategoria();break;
		case 6:cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-6]\t!!\n";cout<<endl;
		}
	} while(opt!=6);
}
void agregarCategoria()
{
	string flag;
	int 	cod;
	string 	nom;
	do
	{
		cod = categoriaController->getCorrelativo();
		cout<<"<<<<<<<<<< CODIGO DE LA CATEGORIA ("<<cod<<") >>>>>>>>>>\n";
		cout<<"------------------------------------------------\n\n";
		cin.ignore();
		cout<<"Nombre de la Categoria: ";
		getline(cin,nom);
		cout<<"Continuar(S/s):";
		cin>>flag;
		/*Crear el objeto de tipo alumno*/
		Categoria objCategoria(cod,nom);
		/*Agregar el objeto alarreglo*/
		categoriaController->add(objCategoria);
		//grabar en archivo
		categoriaController->grabarEnArchivo(objCategoria);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}

void buscarCategoria()
{
	int cod;
	int inferior=0;
	int superior=categoriaController->size()-1;
	cout<<"Ingrese codigo a buscar: ";
	cin>>cod;
	Categoria objCategoria = categoriaController->buscar(cod,inferior,superior);
	if(objCategoria.getNomCat() != "Error")
	{
		cout<<"Objeto encontrado:\n";
		cout<<"Codigo: "<<objCategoria.getCodCat()<<endl;
		cout<<"Nombre de la Categoria: "<<objCategoria.getNomCat()<<endl;
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");
}
void modificarCategoria()
{
	int cod;
	int inferior=0;
	int superior=categoriaController->size()-1;
	cout<<"Ingrese codigo a buscar: ";
	cin>>cod;
	Categoria objEncontrado = categoriaController->buscar(cod,inferior,superior);
	if(objEncontrado.getNomCat() != "Error")
	{
		cout<<"Objeto encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodCat()<<endl;
		cout<<"Nombre del Producto: "<<objEncontrado.getNomCat()<<endl;
		/*Modificación*/
		string 	nom;
		cin.ignore();
		cout<<"Modificar Nombre del Producto:";
		getline(cin,nom);
		
		Categoria objNew(objEncontrado.getCodCat(),nom);
		
		bool estado = categoriaController->modificar(objEncontrado,objNew);
		if(estado == true)								
		{
			cout<<"Registro modificado satisfactoriamente\n";	
			/*grabar en archivo*/
			categoriaController->grabarModificarEliminar();
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
void eliminarCategoria()
{
	int cod;
	int inferior=0;
	int superior=categoriaController->size()-1;
	cout<<"Ingrese codigo a eliminar: ";
	cin>>cod;
	Categoria objEliminar = categoriaController->buscar(cod,inferior,superior);
	if(objEliminar.getNomCat() != "Error")
	{
		categoriaController->eliminar(objEliminar);	
		cout<<"Registro Eliminado Satisfactoriamente!\n";
		/*Grabar en archivo*/
		categoriaController->grabarModificarEliminar();
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");		
}
void listarCategoria()
{
	cout<<"Codigo de categoria    Nombre de categoria\n";
	cout<<"-----------------------------------------------\n";
	for(int i = 0;i<categoriaController->size();i++)
	{
		cout<<"\t"<<categoriaController->get(i).getCodCat()<<"\t"<<categoriaController->get(i).getNomCat()<<endl;
	}
	system("pause");
	system("cls");
}
