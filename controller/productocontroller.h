#pragma once
#include<iostream>
#include<vector>
#include"../model/producto.h"
#include"../controller/categoriacontroller.h"
#include<fstream>

using namespace std;

void registroProducto();
void agregarProducto();
void buscarProducto();
void modificarProducto();
void eliminarProducto();
void listarProducto();

//PRODUCTO CONTROLLER
class ProductoController
{
private:
	vector<Producto> vectorProducto;
public:
	ProductoController()
	{
		cargarDatosDelArchivoAlVector();
	}
	//Agregar objetos al arreglo
	void add(Producto obj)
	{
		vectorProducto.push_back(obj);
	}
	
	Producto get(int pos)
	{
		return vectorProducto[pos];
	}
	
	int size()
	{
		return vectorProducto.size();
	}
	
	int getCorrelativo()
	{
		if(size() == 0)
		{
			return 1;
		}
		else
		{
			return 	vectorProducto[size() - 1].getCodigo() + 1;
		}
	}
	string getNomPro(int opt)
	{
		for(int i=0;i<size();i++)
		{
			if(opt == vectorProducto[i].getCodigo())
			{
				return vectorProducto[i].getNom();
			}
		}
		return "Error";
	}
	int getProduc(int opt)
	{
		for(int i=0;i<size();i++)
		{
			if(opt == vectorProducto[i].getCodigo())
			{
				return vectorProducto[i].getPrecio();
			}
		}
		return -1;
	}
	bool buscarNombrePro(string nombre)
	{ 
		bool busca = false;
		int cont = 0;  
		for(Producto x:vectorProducto)
		{
			size_t found = (x.getNom()).find(nombre);
			if (found != string::npos)
			{  if(cont<1)
			{
				cout<<"\n";
				cout<<"\t     CODIGO           STOCK          PRECIO    \t     NOMBRE    \n\n"; 
				cont++;
			}
			cout<<"\t\t"<<x.getCodigo()<<"\t\t"<<x.getCan()<<"\t\t"<<x.getPrecio()<<"\t\t"<<x.getNom()<<endl;
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
	Producto buscar(int dato)
	{
		Producto objError;
		objError.setNom("Error");
		for(Producto x:vectorProducto)
		{
			if(dato == x.getCodigo())
			{
				return x;	
			}			
		}
		return objError;
	}
	
	bool modificar(Producto ObjOld,Producto ObjNew)
	{
		for(int i=0;i<vectorProducto.size();i++)
		{
			if(ObjOld.getCodigo() == vectorProducto[i].getCodigo())
			{
				vectorProducto[i].setNom(ObjNew.getNom());
				vectorProducto[i].setPrecio(ObjNew.getPrecio());
				vectorProducto[i].setCan(ObjNew.getCan());
				vectorProducto[i].setCodCat(ObjNew.getCodiCat());
				return true;
			}
		}
		return false;
	}
	int getPostArray(Producto obj)
	{
		for(int i = 0;i<vectorProducto.size();i++)
		{
			if(obj.getCodigo() == vectorProducto[i].getCodigo())			
			{
				return i;
			}
		}
		return -1;
	}
	void eliminar(Producto objEncontrado)
	{
		vectorProducto.erase(vectorProducto.begin() + getPostArray(objEncontrado));
	}
	void grabarEnArchivo(Producto obj)
	{
		try
		{
			fstream archivoProducto;
			archivoProducto.open("archivoproducto.csv",ios::app);
			if(archivoProducto.is_open())
			{
				archivoProducto<<obj.getCodigo()<<";"<<obj.getNom()<<";"<<obj.getPrecio()<<";"<<obj.getCan()<<";"<<obj.getCodiCat()<<";"<<endl;
				archivoProducto.close();					
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
			fstream archivoProducto;
			archivoProducto.open("archivoproducto.csv",ios::out);
			if(archivoProducto.is_open())
			{
				for(Producto x:vectorProducto)
				{	
					archivoProducto<<x.getCodigo()<<";"<<x.getNom()<<";"<<x.getPrecio()<<";"<<x.getCan()<<";"<<x.getCodiCat()<<";"<<endl;
				}
				archivoProducto.close();					
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
			fstream	archivoProducto;
			archivoProducto.open("archivoproducto.csv",ios::in);
			if(archivoProducto.is_open())
			{
				while(!archivoProducto.eof() && getline(archivoProducto,linea))
				{
					i = 0;
					while((posi = linea.find(";")) != string::npos)
					{
						temporal[i] = linea.substr(0,posi);
						linea.erase(0,posi+1);
						++i;
					}
					//stoi: string a int
					//stof: string a float
					Producto objProducto(stoi(temporal[0]),temporal[1],stof(temporal[2]),stoi(temporal[3]),stoi(temporal[4]));
					
					add(objProducto);
				}
			}
		}
		catch(exception e)
		{
			cout<<"Ocurrio un error al grabar el archivo3";
		}
	}
	
};


ProductoController* productoController = new ProductoController();
//REGISTRO PRODUCTOS
void registroProducto()
{
	int opt;
	do
	{
		cout<<"\t\t*************OPCIONES DE PRODUCTO*************\n";
		cout<<"\t\t**********************************************\n";
		cout<<"\t\t 1. Agregar Producto   | 4. Eliminar Producto \n";
		cout<<"\t\t 2. Buscar Producto    | 5. Listar Producto   \n";
		cout<<"\t\t 3. Modificar Producto | 6. Regresar al menu  \n";
		cout<<"\t\tIngrese una opción: ";
		cin>>opt;
		switch(opt)
		{
		case 1:system("cls");agregarProducto();break;
		case 2:system("cls");buscarProducto();break;
		case 3:system("cls");modificarProducto();break;
		case 4:system("cls");eliminarProducto();break;
		case 5:system("cls");listarProducto();break;
		case 6:cout<<"Gracias por usar nuestro programa\n";
		system("cls");break;
		default:system("cls");cout<<"¡¡\tIngresa una opción correcta[1-6]\t!!\n";cout<<endl;
		}
	} while(opt!=6);
	system("cls");
}

void agregarProducto()
{
	string  flag;
	int 	cod;
	string 	nom;
	int		can;
	float 	precio;
	int		opt;
	do
	{
		cod = productoController->getCorrelativo();
		cout<<"<<<<<<<<<< CODIGO DEL PRODUCTO ("<<cod<<") >>>>>>>>>>\n";
		cout<<"---------------------------------------------\n\n";
		cin.ignore();
		cout<<"Nombre del Producto: ";
		getline(cin,nom);
		cout<<"Precio por unidad: ";
		cin>>precio;
		cout<<"Stock del Producto: ";
		cin>>can;
		
		for (int i=0;i<categoriaController->size();i++)
		{
			cout<<categoriaController->get(i).getCodCat()<<"\t";
			cout<<categoriaController->get(i).getNomCat()<<endl;
		}
		cout<<"Ingrese una opcion: ";
		cin>>opt;
		
		cout<<"Continuar(S/s):";
		cin>>flag;
		//Crear el objeto de tipo alumno
		Producto objProducto(cod,nom,precio,can,opt);
		//Agregar el objeto alarreglo
		productoController->add(objProducto);
		//grabar en archivo
		productoController->grabarEnArchivo(objProducto);
		system("cls");
	} 
	while(flag == "S" || flag == "s");
}

void buscarProducto()
{
	int cod;
	cout<<"Ingrese codigo a buscar:";
	cin>>cod;
	Producto objEncontrado = productoController->buscar(cod);
	if(objEncontrado.getNom() != "Error")
	{
		cout<<"Objeto encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodigo()<<endl;
		cout<<"Nombre del Producto: "<<objEncontrado.getNom()<<endl;
		cout<<"Precio: "<<objEncontrado.getPrecio()<<endl;
		cout<<"Cantidad: "<<objEncontrado.getCan()<<endl;
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");
}

void modificarProducto()
{
	int cod;
	cout<<"Ingrese codigo a buscar:";
	cin>>cod;
	Producto objEncontrado = productoController->buscar(cod);
	if(objEncontrado.getNom() != "Error")
	{
		cout<<"Objeto encontrado:\n";
		cout<<"Codigo: "<<objEncontrado.getCodigo()<<endl;
		cout<<"Nombre del Producto: "<<objEncontrado.getNom()<<endl;
		cout<<"Precio: "<<objEncontrado.getPrecio()<<endl;
		cout<<"Cantidad: "<<objEncontrado.getCan()<<endl;
		//Modificacion
		string 	nom;
		float 	can;
		float	precio;
		cin.ignore();
		cout<<"Modificar Nombre del Producto:";
		getline(cin,nom);
		cout<<"Modificar Precio:";
		cin>>precio;
		cout<<"Modificar Cantidad:";
		cin>>can;
		cout<<"Modificar codigo: ";
		cin>>cod;
		
		Producto objNew(objEncontrado.getCodigo(),nom,precio,can,cod);
		
		bool estado = productoController->modificar(objEncontrado,objNew);
		if(estado == true)								
		{
			cout<<"Registro modificado satisfactoriamente\n";	
			/*grabar en archivo*/
			productoController->grabarModificarEliminar();
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
void eliminarProducto()
{
	int cod;
	cout<<"Ingrese codigo a eliminar:";
	cin>>cod;
	Producto objEliminar = productoController->buscar(cod);
	if(objEliminar.getNom() != "Error")
	{
		productoController->eliminar(objEliminar);	
		cout<<"Registro Eliminado Satisfactoriamente!\n";
		/*Grabar en archivo*/
		productoController->grabarModificarEliminar();
	}
	else
	{
		cout<<"No se encontro el codigo ingresado\n";	
	}
	system("pause");
	system("cls");		
}
void listarProducto()
{
	cout<<"Codigo      Nombre de producto        Precio     Cantidad          Categoria\n";
	cout<<"------------------------------------------------------------------------------\n";
	for(int i = 0;i<productoController->size();i++)
	{
		cout<<productoController->get(i).getCodigo()<<"\t"
			"\t"<<productoController->get(i).getNom()<<"\t"
			"\t"<<productoController->get(i).getPrecio()<<"\t"
			<<productoController->get(i).getCan()<<"\t"
			"\t"<<categoriaController->getCate(productoController->get(i).getCodiCat())<<endl;
	}		
	system("pause");
	system("cls");	
}
