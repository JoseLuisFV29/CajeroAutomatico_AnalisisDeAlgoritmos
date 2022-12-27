#include "Operaciones.hpp"
#include <string>

string Operaciones::getUsuario() {
	return _Usuario;
}
void Operaciones::setUsuario(string usuario) {
	_Usuario = usuario;
}

string Operaciones::getAccion() {
	return _Accion;
}
void Operaciones::setAccion(string accion) {
	_Accion = accion;
}

int Operaciones::getMonto() {
	return _Monto;
}
void Operaciones::setMonto(int monto) {
	_Monto = monto;
}
string Operaciones::getFecha() {
	return _Fecha;
}
void Operaciones::setFecha(string fecha) {
	_Fecha = fecha;
}

string Operaciones::getHora() {
	return _Hora;
}
void Operaciones::setHora(string hora) {
	_Hora = hora;
}





