#pragma once
#include <iostream>
#include <vector>
#include"../model/tipopersonal.h"
#include<fstream>
using namespace std;
//Funciones de Tipo_Personal
void registroTipoPersonal();
void agregarTipoPersonal();
void buscarTipoPersonal();
void modificarTipoPersonal();
void eliminarTipoPersonal();
void listarTipoPersonal();
//TIPO_PERSONAL CONTROLLER
class TipoPersonalController
{
private:
	vector<TipoPersonal> vectorTipoPersonal;
public:
	TipoPersonalController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arreglo
	void add(TipoPersonal obj)
	{
		vectorTipoPersonal.push_back(obj);
	}
	
	TipoPersonal get(int pos)
	{
		return vectorTipoPersonal[pos];
	}
	
	int size()
	{
		return vectorTipoPersonal.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorTipoPersonal[size() - 1].getCodTipPer() + 1;
		}
	}
	
	TipoPersonal buscar(int dato,int inf, int sup)
	{
		int center;
		TipoPersonal objError;
		objError.setNomTipPer("Error");
		if (inf > sup)
		{
			return objError;
		}
		else
		{
			center = (inf + sup) / 2;
			if (vectorTipoPersonal[center].getCodTipPer() == dato)
			{
				return vectorTipoPersonal[center];
			}
			else if (vectorTipoPersonal[center].getCodTipPer() < dato)
			{
				return buscar(dato, center +  1, sup);
			}
			else
			{
				return buscar(dato, inf, center - 1);
			}
		}
	}
	
	bool modificar(TipoPersonal ObjOld,TipoPersonal ObjNew)
	{
		for(int i=0;i<vectorTipoPersonal.size();i++)
		{
			if(ObjOld.getCodTipPer() == vectorTipoPersonal[i].getCodTipPer())
			{
				vectorTipoPersonal[i].setNomTipPer(ObjNew.getNomTipPer());
				return true;
			}
		}
		return false;
	}
	int getPostArray(TipoPersonal obj)
	{
		for(int i = 0;i<vectorTipoPersonal.size();i++)
		{
			if(obj.getCodTipPer() == vectorTipoPersonal[i].getCodTipPer())			
			{
				return i;
			}
		}
		return -1;
	}
	void eliminar(TipoPersonal objEncontrado)
	{
		vectorTipoPersonal.erase(vectorTipoPersonal.begin() + getPostArray(objEncontrado));
	}
	string getTipo(int opt){
		for(int i=0;i<size();i++){
			if(opt == vectorTipoPersonal[i].getCodTipPer())
			{
				return vectorTipoPersonal[i].getNomTipPer();
			}
		}
		return "Error";
	}
		void grabarEnArchivo(TipoPersonal obj)
		{
			try
			{
				fstream archivoTipoPersonal;
				archivoTipoPersonal.open("archivotipopersonal.csv",ios::app);
				if(archivoTipoPersonal.is_open())
				{
					archivoTipoPersonal<<obj.getCodTipPer()<<";"<<obj.getNomTipPer()<<";"";"<<endl;
					archivoTipoPersonal.close();					
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
				fstream archivoTipoPersonal;
				archivoTipoPersonal.open("archivotipopersonal.csv",ios::out);
				if(archivoTipoPersonal.is_open())
				{
					for(TipoPersonal x:vectorTipoPersonal)
					{	
						archivoTipoPersonal<<x.getCodTipPer()<<";"<<x.getNomTipPer()<<";"<<endl;
					}
					archivoTipoPersonal.close();					
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
				fstream	archivoTipoPersonal;
				archivoTipoPersonal.open("archivotipopersonal.csv",ios::in);
				if(archivoTipoPersonal.is_open())
				{
					while(!archivoTipoPersonal.eof() && getline(archivoTipoPersonal,linea))
					{
						i = 0;
						while((posi = linea.find(";")) != string::npos)
						{
							temporal[i] = linea.substr(0,posi);
							linea.erase(0,posi+1);
							++i;
						}
						TipoPersonal objTipoPersonal(stoi(temporal[0]),temporal[1]);
						
						add(objTipoPersonal);
					}
				}
			}
			catch(exception e)
			{
				cout<<"Ocurrio un error al grabar el archivo";
			}
		}
};

TipoPersonalController* tipoPersonalController = new TipoPersonalController();
//GENERAR TIPO_PERSONAL
void registroTipoPersonal()
{
	int opt;
	do
	{
		cout<<"\t\t*****************OPCIONES DE TIPO DE PERSONAL*****************\n";
		cout<<"\t\t**************************************************************\n";
		cout<<"\t\t 1. Agregar Tipo de Personal   | 4. Eliminar Tipo de Personal \n";
		cout<<"\t\t 2. Buscar Tipo de Personal    | 5. Listar Tipo de Personal   \n";
		cout<<"\t\t 3. Modificar Tipo de Personal | 6. Regresar al menu          \n";
		cout<<"\t\tIngrese una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agregarTipoPersonal();break;
		case 2:system("cls");buscarTipoPersonal();break;
		case 3:system("cls");modificarTipoPersonal();break;
		case 4:system("cls");eliminarTipoPersonal();break;
		case 5:system("cls");listarTipoPersonal();break;
		case 6:cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-6]\t!!\n";cout<<endl;
		}
	} while(opt!=6);
}
void agregarTipoPersonal()
{
	string flag;
	int 	codTipPer;
	string 	nomTipPer;
	do
	{
		codTipPer = tipoPersonalController->getCorrelativo();
		cout<<"<<<<<<<<<< CODIGO DEL TIPO DE PERSONAL ("<<codTipPer<<") >>>>>>>>>>\n";
		cout<<"-----------------------------------------------------\n\n";
		cin.ignore();
		cout<<"Nombre del Tipo de Personal: ";
		getline(cin,nomTipPer);
		cout<<"Continuar(S/s):";
		cin>>flag;
		/*Crear el objeto de tipo alumno*/
		TipoPersonal objTipoPersonal(codTipPer,nomTipPer);
		/*Agregar el objeto alarreglo*/
		tipoPersonalController->add(objTipoPersonal);
		//grabar en archivo
		tipoPersonalController->grabarEnArchivo(objTipoPersonal);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}

void buscarTipoPersonal()
{
	int codTipPer;
	int inferior=0;
	int superior=tipoPersonalController->size()-1;
	cout<<"Ingrese codigo a buscar:";
	cin>>codTipPer;
	TipoPersonal objTipoPersonal = tipoPersonalController->buscar(codTipPer,inferior,superior);
	if(objTipoPersonal.getNomTipPer() != "Error")
	{
		cout<<"Tipo de Personal encontrado:\n";
		cout<<"Codigo: "<<objTipoPersonal.getCodTipPer()<<endl;
		cout<<"Nombre del Tipo de Personal: "<<objTipoPersonal.getNomTipPer()<<endl;
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");
}
void modificarTipoPersonal()
{
	int codTipPer;
	int inferior=0;
	int superior=tipoPersonalController->size()-1;
	cout<<"Ingrese codigo a buscar:";
	cin>>codTipPer;
	TipoPersonal objEncontrado = tipoPersonalController->buscar(codTipPer,inferior,superior);
	if(objEncontrado.getNomTipPer() != "Error")
	{
		cout<<"Tipo de Personal encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodTipPer()<<endl;
		cout<<"Nombre del Tipo de Personal: "<<objEncontrado.getNomTipPer()<<endl;
		/*Modificación*/
		string 	nomTipPer;
		cin.ignore();
		cout<<"Modificar Nombre del Tipo de Personal:";
		getline(cin,nomTipPer);
		
		TipoPersonal objNew(objEncontrado.getCodTipPer(),nomTipPer);
		
		bool estado = tipoPersonalController->modificar(objEncontrado,objNew);
		if(estado == true)								
		{
			cout<<"Registro modificado satisfactoriamente\n";	
			/*grabar en archivo*/
			tipoPersonalController->grabarModificarEliminar();
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
void eliminarTipoPersonal()
{
	int codTipPer;
	int inferior=0;
	int superior=tipoPersonalController->size()-1;
	cout<<"Ingrese codigo a eliminar:";
	cin>>codTipPer;
	TipoPersonal objEliminar = tipoPersonalController->buscar(codTipPer,inferior,superior);
	if(objEliminar.getNomTipPer() != "Error")
	{
		tipoPersonalController->eliminar(objEliminar);	
		cout<<"Registro Eliminado Satisfactoriamente!\n";
		/*Grabar en archivo*/
		tipoPersonalController->grabarModificarEliminar();
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");		
}
void listarTipoPersonal()
{
	cout<<"Codigo       Tipo de Personal\n";
	cout<<"---------------------------------------------\n";
	for(int i = 0;i<tipoPersonalController->size();i++)
	{
		cout<<tipoPersonalController->get(i).getCodTipPer()<<"\t"<<tipoPersonalController->get(i).getNomTipPer()<<endl;
	}
	system("pause");
	system("cls");	
}
