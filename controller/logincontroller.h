#pragma once
#include<iostream>
#include<vector>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<cstring>
#include"../model/encryption.h"
#include"../model/login.h"
#include"clientecontroller.h"
#include"personalcontroller.h"
#include"tipopersonalcontroller.h"
#include"productocontroller.h"
#include"ventacontroller.h"
#include"../controller/detalleventacontroller.h"
using namespace std;

void menuDeAcceso();
void registrarPersonal();
void iniciarSesion();
void menuPrincipal();
string encriptar(string);
string desencriptar(string);

//LOGIN CONTROLLER
class LoginController
{
private:
	vector<Acceso> vectorAcceso; //Crear el arreglo de objetos
public:
	LoginController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar datos de tipo acceso
	void add(Acceso obj)
	{
		vectorAcceso.push_back(obj);
	}
	//Obtener datos de tipo acceso
	Acceso get(int pos)
	{
		return vectorAcceso[pos];
	}
	//Tamaño del arreglo
	int size()
	{
		return vectorAcceso.size();
	}
	//Grabar en archivo
	void grabarEnArchivo(Acceso acceso)
	{
		try
		{
			fstream archivoLogin;
			archivoLogin.open("login.csv", ios::app);
			if(archivoLogin.is_open())
			{
				archivoLogin<<acceso.getUsuario()<<";"
					<<acceso.getContrasena()<<";"<<endl;
				archivoLogin.close();
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
	
	//Leer el archivo
	void LeerEnArchivo(Acceso obj)
	{
		try
		{
			fstream archivoLogin;
			archivoLogin.open("login.csv",ios::in);
			if(archivoLogin.is_open())
			{
				archivoLogin<<obj.getUsuario() <<";"<<obj.getContrasena()<<";"<<endl;
				archivoLogin.close();
			}
		}
		catch (exception e)
		{
			cout<<"Error de lectura";
		}
	}
	//Cargar datos del archivo
	void cargarDatosDelArchivoAlVector()
	{
		try
		{
			int 	i;
			size_t 	posi;
			string 	linea;
			string 	temporal[2];
			fstream	archivoLogin;
			archivoLogin.open("login.csv",ios::in);
			if(archivoLogin.is_open())
			{
				while(!archivoLogin.eof() && getline(archivoLogin,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					
					Acceso objAcceso(temporal[0],temporal[1]);
					add(objAcceso);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo";
		}
	}
};

//Crear el objeto
LoginController* loginController = new LoginController();

//menus 
void menuDeAcceso()
{
	int opt;
	do
	{
		cout<<"\t\t|------------------------------------------------------------|\n";
		cout<<"\t\t|                       MENU DE ACCESO                       |\n";
		cout<<"\t\t|------------------------------------------------------------|\n\n";
		cout<<"\t\tREGISTRARSE**********************************************[1]\n\n";
		cout<<"\t\tINICIAR SESION*******************************************[2]\n\n";
		cout<<"\t\tSALIR****************************************************[3]\n\n";
		cout<<"\t\tIngresar una opción [1-3]: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");registrarPersonal();break;
		case 2:system("cls");iniciarSesion();break;
		case 3:system("cls");system("cls");break;
		default:system("cls");cout<<"Ingrese una opcion correcta[1-3]\n";
		}
	} while(opt != 3);
	system("cls");
	cout<<"\n\n";
	cout<<"\t\t**************************************************\n";
	cout<<"\t\t\tGRACIAS POR USAR NUESTRO PROGRAMA\n";
	cout<<"\t\t**************************************************\n";
}

void registrarPersonal()
{
	string user;
	string clave;
	string usu;
	string contra;
	string flag;
	int contador=0;
	cout<<"\n";
	do
	{
		cout<<"\t*******REGISTRAR PERSONAL********\n";
		
		cout<<"\tIngrese el usuario del sistema: ";
		cin>>user;
		cout<<"\tIngrese la clave del sistema: ";
		cin>>clave;
		if(user=="SISTEMAS" && clave == "USIL")
		{
			cout<<"\n\n";
			cout<<"****GENERE USUARIO Y CONTRASEÑA****\n";
			cout<<"\n\n";
			cout<<"Generar Usuario: ";
			cin>>usu;
			usu  =  encriptacion(usu);
			cout<<"Generar Contrasenia: ";
			cin>>contra;
			contra = encriptacion(contra);
			//crear objeto tipo acceso
			Acceso acceso(usu,contra);	
			//meter en un arreglo el objeto tipo alumno
			loginController->add(acceso);
			//grabar en un archibo csv la informacion
			loginController->grabarEnArchivo(acceso);
		}
		else
		{
			if(contador < 2)
			{
				cout<<"\t¿DESEA INTENTARLO NUEVAMENTE?(S/s): ";
				cin>>flag;
				system("cls");
			}
			else
			{
				cout<<"\tHa superado los 3 intentos, va a regresar al menu principal"<<endl;
				system("pause");
				system("cls");
			}
			if(flag== "S" || flag=="s")
			{
				contador++;
			}
			else
			{
				break;
				system("cls");
			}
		}
	} while(contador<=2&&flag=="s");
	
}

void iniciarSesion()
{
	string flag;
	bool   ingreso=false;
	int    contador=0;
	
	do
	{
		string usuarioDesencrip[100];
		string passDesencrip[100];
		string user;
		string contra;
		char caracter;
		for(int i = 0;i<loginController->size();i++)
		{
			usuarioDesencrip[i]   = loginController->get(i).getUsuario();
			passDesencrip[i] = loginController->get(i).getContrasena();
		}
		cout<<"\n";
		cout<<"\t*******ACCESO DE PERSONAL********\n";
		cout<<"\tIngrese usuario: ";
		cin>>user;
		cout<<"\tIngrese contrasena: ";
		//cin>>contra;
		caracter=getch();
		contra="";
		//caracteres ASCII
		//13=enter
		while(caracter!=13)
		{
			//8=retroceso
			if (caracter!=8)
			{
				contra.push_back(caracter);
				cout<<"*";
			} else{
				//lenght->numero de caracterees
				if(contra.length() > 0){
					//borrar asteriscos
					//imprimir caracter-espacio en blanco-imprimir caracter
					cout<<"\b \b";
					//borrar el ultimo caracter
					contra=contra.substr(0, contra.length() - 1);
				}
			}
			caracter=getch();
		}
		
		//desencriptar del archivo y comparar
		for(int i=0;i<loginController->size();i++)
		{
			if(user == desencriptacion(usuarioDesencrip[i]) && contra == desencriptacion(passDesencrip[i]))
			{
				ingreso = true;
				goto ingreso;
			}
		}
		if(ingreso!=true)
		{
			cout<<endl;
			cout<<"\tACCESO DENEGADO, vuelve a intentarlo \n\n";
			if(contador < 2)
			{
				cout<<"\t¿DESEA INTENTARLO NUEVAMENTE?(S/s): ";
				cin>>flag;
				system("cls");
			}
			else
			{
				cout<<"\tHa superado los 3 intentos, va a regresar al menu principal"<<endl;
				system("pause");
				system("cls");
			}
			if(flag== "S" || flag=="s")
			{
				contador++;
			}
			else
			{
				break;
				system("cls");
			}
		}
		
	} while(contador <= 2 && ingreso!=true);
	system("cls");
	
	ingreso:
		if(ingreso == true)
	{
		system("cls");
		cout<<"\t\t                   ¡ ACCESO PERMITIDO !                              "<<endl;
		
		menuPrincipal();
	}
		else
		{
			cout<<"GRACIAS POR USAR NUESTRO PROGRAMA :D "<<endl;
		}
		
		system("cls");
}

//MENU LUEGO DE INGRESAR EL USUARIO Y CONTRASEÑA CORRECTAMENTE
void menuPrincipal()
{
	int opt;
	do
	{
		cout<<"\t\t|-------------------------------------------------------------------|\n";
		cout<<"\t\t|           *****Bienvenido a la empresa ventaMas*****              |\n";
		cout<<"\t\t|----------------------------|--------------------------------------|\n";
		cout<<"\t\t|      *****SELECCIONE UNA DE LAS SIGUIENTES OPCIONES*****          |\n";
		cout<<"\t\t|----------------------------|--------------------------------------|\n";
		cout<<"\t\t| 1. Registro de clientes    | 5. Agregar el tipo del personal      |\n";
		cout<<"\t\t| 2. Registro de productos   | 6. Agregar la categoria del producto |\n";
		cout<<"\t\t| 3. Registro de venta       | 7. Registro de detalle de venta      |\n";
		cout<<"\t\t| 4. Registro del personal   | 8. Salir                             |\n";
		cout<<"\t\t|----------------------------|--------------------------------------|\n";
		cout<<"\t\t Ingrese una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");registroCliente();break;
		case 2:system("cls");registroProducto();break;
		case 3:system("cls");registroVenta();break;
		case 4:system("cls");registroPersonal();break;
		case 5:system("cls");registroTipoPersonal();break;
		case 6:system("cls");registroCategoria();break;
		case 7:system("cls");registroDetalleVenta();break;
		case 8:system("cls");cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-8]\t!!\n";cout<<endl;
		}
	}
	while(opt!=8);
}
