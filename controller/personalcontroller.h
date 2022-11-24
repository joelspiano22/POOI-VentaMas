#pragma once
#include <iostream>
#include <vector>
#include"../model/personal.h"
#include"../controller/tipopersonalcontroller.h"
#include<fstream>
using namespace std;
//Funciones de registro personal
void registroPersonal();
void agregarPersonal();
void buscarPersonal();
void modificarPersonal();
void eliminarPersonal();
void listarPersonal();
//PRODUCTO CONTROLLER
class PersonalController
{
private:
	vector<Personal> vectorPersonal;
public:
	PersonalController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arreglo
	void add(Personal obj)
	{
		vectorPersonal.push_back(obj);
	}
	
	Personal get(int pos)
	{
		return vectorPersonal[pos];
	}
	
	int size()
	{
		return vectorPersonal.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorPersonal[size() - 1].getCodPersonal() + 1;
		}
	}
	
	Personal buscar(int dato,int inf, int sup)
	{
		int center;
		Personal objError;
		objError.setNomApePer("Error");
		if(inf>sup)
		{
			return objError;
		}
		else
		{
			center=(inf+sup)/2;
			if(vectorPersonal[center].getCodPersonal()==dato)
			{
				return vectorPersonal[center];
			}
			else if(vectorPersonal[center].getCodPersonal()<dato)
			{
				return buscar(dato,center+1,sup);
			}
			else
			{
				return buscar(dato,inf,center-1);
			}
		}
	}
	
	bool modificar(Personal ObjOld,Personal ObjNew)
	{
		for(int i=0;i<vectorPersonal.size();i++)
		{
			if(ObjOld.getCodPersonal() == vectorPersonal[i].getCodPersonal())
			{
				vectorPersonal[i].setNomApePer(ObjNew.getNomApePer());
				vectorPersonal[i].setDniPer(ObjNew.getDniPer());
				vectorPersonal[i].setSuePer(ObjNew.getSuePer());
				vectorPersonal[i].setCodTipPer(ObjNew.getCodTipPer());
				return true;
			}
		}
		return false;
	}
	int getPostArray(Personal obj)
	{
		for(int i = 0;i<vectorPersonal.size();i++)
		{
			if(obj.getCodPersonal() == vectorPersonal[i].getCodPersonal())			
			{
				return i;
			}
		}
		return -1;
	}
	void eliminar(Personal objEncontrado)
	{
		vectorPersonal.erase(vectorPersonal.begin() + getPostArray(objEncontrado));
	}
	void grabarEnArchivo(Personal obj)
	{
		try
		{
			fstream archivoPersonal;
			archivoPersonal.open("archivopersonal.csv",ios::app);
			if(archivoPersonal.is_open())
			{
				archivoPersonal<<obj.getCodPersonal()<<";"<<obj.getNomApePer()<<";"<<obj.getDniPer()<<";"<<obj.getSuePer()<<";"<<obj.getCodTipPer()<<";"<<endl;
				archivoPersonal.close();					
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
			fstream archivoPersonal;
			archivoPersonal.open("archivopersonal.csv",ios::out);
			if(archivoPersonal.is_open())
			{
				for(Personal x:vectorPersonal)
				{	
					archivoPersonal<<x.getCodPersonal()<<";"<<x.getNomApePer()<<";"<<x.getDniPer()<<";"<<x.getSuePer()<<";"<<x.getCodTipPer()<<";"<<endl;
				}
				archivoPersonal.close();					
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
			string 	temporal[5];
			fstream	archivoPersonal;
			archivoPersonal.open("archivopersonal.csv",ios::in);
			if(archivoPersonal.is_open())
			{
				while(!archivoPersonal.eof() && getline(archivoPersonal,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					Personal objPersonal(stoi(temporal[0]),temporal[1],
										 stoi(temporal[2]),stoi(temporal[3]),stoi(temporal[4]));
					
					add(objPersonal);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};

PersonalController* personalController = new PersonalController();

//REGISTRO PERSONAL
void registroPersonal()
{
	int opt;
	do
	{
		cout<<"\t\t*************OPCIONES DE PERSONAL*************\n";
		cout<<"\t\t**********************************************\n";
		cout<<"\t\t 1. Agregar Personal   | 4. Eliminar Personal \n";
		cout<<"\t\t 2. Buscar Personal    | 5. Listar Personal   \n";
		cout<<"\t\t 3. Modificar Personal | 6. Regresar al menu  \n";
		cout<<"\t\tIngrese una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agregarPersonal();break;
		case 2:system("cls");buscarPersonal();break;
		case 3:system("cls");modificarPersonal();break;
		case 4:system("cls");eliminarPersonal();break;
		case 5:system("cls");listarPersonal();break;
		case 6:cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-6]\t!!\n";cout<<endl;
		}
	} while(opt!=6);
}
void agregarPersonal()
{
	string flag;
	int 	codPersonal;
	string 	nomApePer;
	int		dniPer;
	float 	suePer;
	float 	horas;
	float   precioxHora;
	int opt;
	do
	{
		codPersonal = personalController->getCorrelativo();
		cout<<"<<<<<<<<<< CODIGO DEL PERSONAL ("<<codPersonal<<") >>>>>>>>>>\n";
		cout<<"---------------------------------------------\n\n";
		cin.ignore();
		cout<<"Nombres y Apellidos: ";
		getline(cin,nomApePer);
		cout<<"DNI: ";
		cin>>dniPer;
		cout<<"Precio por Hora: ";
		cin>>precioxHora;
		cout<<"Horas Trabajadas: ";
		cin>>horas;
		suePer=precioxHora*horas;
		
		for (int i=0;i<tipoPersonalController->size();i++)
		{
			cout<<tipoPersonalController->get(i).getCodTipPer()<<"\t";
			cout<<tipoPersonalController->get(i).getNomTipPer()<<endl;
		}
		cout<<"Ingrese una opcion: ";
		cin>>opt;
		
		cout<<"Continuar(S/s):";
		cin>>flag;
		/*Crear el objeto de tipo alumno*/
		Personal objPersonal(codPersonal,nomApePer,dniPer,suePer,opt);
		/*Agregar el objeto alarreglo*/
		personalController->add(objPersonal);
		//grabar en archivo
		personalController->grabarEnArchivo(objPersonal);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}

void buscarPersonal()
{
	int codPersonal;
	int inferior=0;
	int superior=personalController->size()-1;
	cout<<"Ingrese codigo a buscar:";
	cin>>codPersonal;
	Personal objEncontrado = personalController->buscar(codPersonal,inferior,superior);
	if(objEncontrado.getNomApePer() != "Error")
	{
		cout<<"Personal encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodPersonal()<<endl;
		cout<<"Nombres y Apellidos: "<<objEncontrado.getNomApePer()<<endl;
		cout<<"DNI: "<<objEncontrado.getDniPer()<<endl;
		cout<<"Sueldo: "<<objEncontrado.getSuePer()<<endl;
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");
}
void modificarPersonal()
{
	int codPersonal;
	int inferior=0;
	int superior=personalController->size()-1;
	cout<<"Ingrese codigo a buscar:";
	cin>>codPersonal;
	Personal objEncontrado = personalController->buscar(codPersonal,inferior,superior);
	if(objEncontrado.getNomApePer() != "Error")
	{
		cout<<"Personal encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodPersonal()<<endl;
		cout<<"Nombres y Apellidos: "<<objEncontrado.getNomApePer()<<endl;
		cout<<"DNI: "<<objEncontrado.getDniPer()<<endl;
		cout<<"Sueldo: "<<objEncontrado.getSuePer()<<endl;
		/*Modificación*/
		string 	nomApePer;
		int 	dniPer;
		float	suePer;
		cin.ignore();
		cout<<"Modificar Nombres y Apellidos: ";
		getline(cin,nomApePer);
		cout<<"Modificar DNI: ";
		cin>>dniPer;
		cout<<"Modificar Sueldo: ";
		cin>>suePer;
		cout<<"Modificar Codigo: ";
		cin>>codPersonal;
		Personal objNew(objEncontrado.getCodPersonal(),nomApePer,dniPer,suePer,codPersonal);
		
		bool estado = personalController->modificar(objEncontrado,objNew);
		if(estado == true)								
		{
			cout<<"Registro modificado satisfactoriamente\n";	
			/*grabar en archivo*/
			personalController->grabarModificarEliminar();
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
void eliminarPersonal()
{
	int codPersonal;
	int inferior=0;
	int superior=personalController->size()-1;
	cout<<"Ingrese codigo a eliminar:";
	cin>>codPersonal;
	Personal objEliminar = personalController->buscar(codPersonal,inferior,superior);
	if(objEliminar.getNomApePer() != "Error")
	{
		personalController->eliminar(objEliminar);	
		cout<<"Registro Eliminado Satisfactoriamente!\n";
		/*Grabar en archivo*/
		personalController->grabarModificarEliminar();
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");		
}
void listarPersonal()
{
	cout<<"Codigo        Nombres y Apellidos        DNI        Sueldo      Tipo de Personal\n";
	cout<<"------------------------------------------------------------------------------------------\n";
	for(int i = 0;i<personalController->size();i++)
	{
		cout<<personalController->get(i).getCodPersonal()<<"\t\t"<<personalController->get(i).getNomApePer()<<"\t\t"
			<<personalController->get(i).getDniPer()<<"\t"
			<<personalController->get(i).getSuePer()<<"\t"
			<<tipoPersonalController->getTipo(personalController->get(i).getCodTipPer())<<endl;
	}
	system("pause");
	system("cls");	
}
