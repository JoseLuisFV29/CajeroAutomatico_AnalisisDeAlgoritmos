#pragma once
#include <string>
using namespace std;
class Operaciones
{
public:
	string getUsuario();
	void setUsuario(string usuario);

	string getAccion();
	void setAccion(string accion);

	int getMonto();
	void setMonto(int monto);

	string getFecha();
	void setFecha(string fecha);

	string getHora();
	void setHora(string hora);



private:
	string _Usuario;
	string _Accion;
	int _Monto;
	string _Fecha;
	string _Hora;

};

