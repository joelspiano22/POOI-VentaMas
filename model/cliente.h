#include <iostream>
#include<vector>
using namespace std;

//CLASE CLIENTE
class Cliente
{
private:
	int 	codCli;
	string 	nomApeCli;
	string 	dirCli;
	string 	rucCli;
public:
	Cliente()
	{
		
	}
	Cliente(int codCli,string nomApeCli,string dirCli,string rucCli)
	{
		this->codCli	 = codCli;
		this->nomApeCli  = nomApeCli;
		this->dirCli	 = dirCli;
		this->rucCli	 = rucCli;		
	}
	//Set
	void setCodCli(int codCli)
	{
		this->codCli = codCli;
	}
	void setNomApeCli(string nomApeCli)
	{
		this->nomApeCli = nomApeCli;
	}
	void setDirCli(string dirCli)
	{
		this->dirCli = dirCli;
	}
	void setRucCli(string rucCli)
	{
		this->rucCli =rucCli;
	}
	//get
	int getCodCli()
	{
		return this->codCli;
	}
	string getNomApeCli()
	{
		return this->nomApeCli;
	}
	string getDirCli()
	{
		return this->dirCli;
	}
	string getRucCli()
	{
		return this->rucCli;
	}	
};
