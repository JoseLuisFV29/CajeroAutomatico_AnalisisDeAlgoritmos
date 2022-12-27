#pragma once
#include <string>

using namespace std;
class Dispensadores
{
public:
	int getCodigo();
	void setCodigo(int code);
	string getLugar();
	void setLugar(string nombre);
	int getCant10();
	void setCant10(int cant10);
	int getCant20();
	void setCant20(int cant20);
	int getCant50();
	void setCant50(int cant50);
	int getCant100();
	void setCant100(int cant100);
	int getCant200();
	void setCant200(int cant200);
	int getTotal();
private:
	int _code;
	string _lugar;
	int _cant10;
	int _cant20;
	int _cant50;
	int _cant100;
	int _cant200;
};