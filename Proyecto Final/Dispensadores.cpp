#include "Dispensadores.hpp"
#include <string>

int Dispensadores::getCodigo() {
	return _code;
}
void Dispensadores::setCodigo(int code) {
	_code = code;
}

string Dispensadores::getLugar() {
	return _lugar;
}
void Dispensadores::setLugar(string lugar) {
	_lugar = lugar;
}

int Dispensadores::getCant10() {
	return _cant10;
}
void Dispensadores::setCant10(int cant10) {
	_cant10 = cant10;
}

int Dispensadores::getCant20() {
	return _cant20;
}
void Dispensadores::setCant20(int cant20) {
	_cant20 = cant20;
}

int Dispensadores::getCant50() {
	return _cant50;
}
void Dispensadores::setCant50(int cant50) {
	_cant50 = cant50;
}

int Dispensadores::getCant100() {
	return _cant100;
}
void Dispensadores::setCant100(int cant100) {
	_cant100 = cant100;
}

int Dispensadores::getCant200() {
	return _cant200;
}
void Dispensadores::setCant200(int cant200) {
	_cant200 = cant200;
}

int Dispensadores::getTotal() {
	return _cant10*10 + _cant20*20 + _cant50*50 + _cant100*100 + _cant200*200;
}