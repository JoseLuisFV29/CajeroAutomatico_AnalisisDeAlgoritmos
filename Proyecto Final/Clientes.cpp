#include "Clientes.hpp"
#include <string>

int Clientes::getDni() {
	return _dni;
}
void Clientes::setDni(int dni) {
	_dni = dni;
}

string Clientes::getNombre() {
	return _nombre;
}
void Clientes::setNombre(string nombre) {
	_nombre = nombre;
}

string Clientes::getApellido() {
	return _apellido;
}
void Clientes::setApellido(string apellido) {
	_apellido = apellido;
}

double Clientes::getSaldo() {
	return _saldo;
}
void Clientes::setSaldo(double saldo) {
	_saldo = saldo;
}

string Clientes::getUsuario() {
	return _usuario;
}
void Clientes::setUsuario(string usuario) {
	_usuario = usuario;
}

string Clientes::getContrasena() {
	return _contrasena;
}
void Clientes::setContrasena(string contrasena) {
	_contrasena = contrasena;
}




