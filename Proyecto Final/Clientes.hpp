#pragma once
#include <string>
using namespace std;
class Clientes
{
public:
	int getDni();
	void setDni(int dni);

	string getNombre();
	void setNombre(string nombre);

	string getApellido();
	void setApellido(string apellido);

	double getSaldo();
	void setSaldo(double saldo);

	string getUsuario();
	void setUsuario(string usuario);

	string getContrasena();
	void setContrasena(string contrasena);

private:
	int _dni;
	string _nombre;
	string _apellido;
	double _saldo;
	string _usuario;
	string _contrasena;
};