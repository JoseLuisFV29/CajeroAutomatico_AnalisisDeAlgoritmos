#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <list>
#include <vector>
#include <iomanip>
#include <dos.h>
#include <random>
#include "Clientes.hpp"
#include "Dispensadores.hpp"
#include "Operaciones.hpp"
#include <ctime>
#include <sstream>


using namespace std;

const string ARCHIVO_CLIENTES = "Clientes.txt";
const string ARCHIVO_TEMPORAL_CLIENTES = "TempC.txt";
const string ARCHIVO_DISPENSADORES = "Dispensadores.txt";
const string ARCHIVO_TEMPORAL_DISPENSASDORES = "TempD.txt";
const string ARCHIVO_OPERACIONES = "Operaciones.txt";
const string ARCHIVO_TEMPORAL_OPERACIONES = "TempOperaciones.txt";

vector<Clientes> clientes;
vector<Operaciones> vec_operaciones;
vector<Dispensadores> dispensadores;
vector <double> PrecioServicios;
Clientes logeado;
//PROTOTIPOS METODOS

char opcmenuAdministrador();
char opcmenuCliente();
char opcmenuGestClie();
char opcmenuGestDisp();

//METODOS CLIENTES
void modificarArchivo();
void agregarCliente();
void ordenarBurbuja();
void listarCliente();
void guardarenArchivo(Clientes c, string txt);
void cargardesdeArchivo();
void guardarenlista(Clientes C);
void eliminarCliente();
void modificarCliente();
int getidxCliente(int tempCli);
void buscarCliente();

//METODOS OPERACIONES
void operacionDepositar(Clientes C);
void operacionRetirar(Clientes C);
void operacionTransferencia(Clientes C);
void operacionPagarServicio(Clientes C);
void generarCobroServicios();
void guardarenArchivoOperaciones(Operaciones operacion_, string txt);
void cargardesdeArchivoOperaciones();
void operacionConsultarSaldo(Clientes C);
void listarOperaciones();
string getHoraOperacion();
string getFechaOperacion();
int verificarDispensador(Dispensadores D, int saldoOperacion);
void desconponerBilletes(int saldoOperacion, Clientes C,int operacion);

//METODOS DISPENSADORES
void guardarenArchivoD(Dispensadores d, string txt);
void cargardesdeArchivoD();
void guardarenlistaD(Dispensadores D);
void agregarDispensador();
void ordenarBurbujaDispensadores();
void listarDispensadores();
void modificarArchivoD();
void modificarDispensador();
int getidxDispensador(int tempDispen);
void buscarDispensador();
//METODOS LOGIN
int login();
int getUsuarioxCliente(string tempCliUsuario);
int getContrasenaxCliente(string tempCliContrasena);
int menuPrincipalAdmin();
int menuPrincipalClientes();

int main()
{
	cargardesdeArchivo();
	cargardesdeArchivoD();
	cargardesdeArchivoOperaciones();
	login();

}
int login() {

	system("cls");
	string leerUsuario, leerContrasena;
	int nivelUsuario;
	int intentos = 0;
	do {
		cin.ignore();
		system("cls");
		cout << "Ingrese su Usuario: ";
		cin >> leerUsuario;

		cin.ignore();
		cout << "Ingrese su Contrasena: ";
		cin >> leerContrasena;

		int idxUsuario = getUsuarioxCliente(leerUsuario);
		int idxContrasena = getContrasenaxCliente(leerContrasena);

		/*
		RANGO USUARIOS:
		ADMINISTRADOR = 1
		USUARIO CLIENTE = 2
		*/
		if (leerUsuario == "UserAdmin" && leerContrasena == "123Admin")
		{
			nivelUsuario = 1;
		}
		else if (idxUsuario != -1 && idxContrasena != -1) {
			Clientes encontrado = clientes.at(idxUsuario);
			nivelUsuario = 2;
			logeado = encontrado;
			generarCobroServicios();
		}
		else {
			nivelUsuario = 0;
		}

		switch (nivelUsuario)
		{
		case 1:
			cout << "BIENVENIDO ADMINISTRADOR!\n";
			system("pause");
			system("cls");
			menuPrincipalAdmin();
			break;
		case 2:
			cout << "BIENVENIDO USUARIO: " << logeado.getNombre() << " " << logeado.getApellido() << endl;

			system("pause");
			system("cls");
			menuPrincipalClientes();
			break;

		default:
			intentos++;
			if (intentos < 5)
			{
				cout << "ERROR!!! Contraseña incorrecta. Intente nuevamente...\n" << '\n';
				system("pause");

			}
			break;
		}

		if (intentos == 5)
		{
			cout << "ERROR!!! Muchos intentos fallidos...\n";
			system("pause");
			return 0;
		}
	} while (nivelUsuario == 0);
	return 1;
}
int getUsuarioxCliente(string tempCliUsuario) {
	int idxUsuario = -1;
	for (Clientes x : clientes)
	{
		idxUsuario++;
		if (x.getUsuario() == tempCliUsuario) {
			return idxUsuario;
		}
	}
	return -1;
}
int getContrasenaxCliente(string tempCliContrasena) {
	int idxContrasena = -1;
	for (Clientes x : clientes)
	{
		idxContrasena++;
		if (x.getContrasena() == tempCliContrasena) {
			return idxContrasena;
		}
	}
	return -1;
}

//MENUS
int menuPrincipalAdmin()
{
	char opcion, opc, opcGest;
	do
	{

		opc = opcmenuAdministrador();
		system("cls");
		switch (opc) {
		case '1': {
			do
			{
				opcGest = opcmenuGestClie();
				system("cls");
				switch (opcGest) {
				case '1': {
					cout << "OPC1 - AGREGAR CLIENTE" << endl;
					agregarCliente();
					break;
				}
				case '2': {
					cout << "OPC2 - MODIFICAR CLIENTE" << endl;
					modificarCliente();
					break;
				}
				case '3': {
					cout << "OPC3 - BAJA DE CLIENTE" << endl;
					eliminarCliente();
					break;
				}
				case '4': {
					cout << "OPC4 - BUSCAR CLIENTE" << endl;
					buscarCliente();
					break;
				}
				case '5': {
					cargardesdeArchivo();
					ordenarBurbuja();
					system("cls");
					cout << "OPC5 - LISTAR CLIENTES" << endl;

					listarCliente();
					break;
				}
				case '6': {
					menuPrincipalAdmin();
					return 0;
					break;
				}
				}
			} while (opcGest != 6);
			break;
		}
		case '2': {
			do
			{
				cout << "OPC2" << endl;
				opcGest = opcmenuGestDisp();
				system("cls");
				switch (opcGest) {
				case '1': {
					cout << "OPC1 - AGREGAR DISPENSADOR" << endl;
					agregarDispensador();
					break;
				}
				case '2': {
					cout << "OPC2 - MODIFICAR DISPENSADOR" << endl;
					modificarDispensador();
					break;
				}
				case '3': {
					cout << "OPC3 - BUSCAR DISPENSADOR" << endl;
					buscarDispensador();
					break;
				}
				case '4': {
					cout << "OPC4 - LISTAR DISPENSADORES" << endl;
					listarDispensadores();
					break;
				}
				case '5': {
					menuPrincipalAdmin();
					break;
				}
				}
			} while (opcGest != 5);
			break;
		}
		case '3': {
			login();
			return 0;
			break;
		}
		}
		break;
	} while (opcion != '3');
	return 0;
}
int menuPrincipalClientes() {
	char opc;

	do
	{
		cargardesdeArchivo();//Cargado Lista Clientes
		system("cls");
		opc = opcmenuCliente();//Muestra el Menu Clientes
		system("cls");
		switch (opc) { //Seleccionar Opcion
		case '1': {
			cout << "OPC1 - DEPOSITAR" << endl;
			operacionDepositar(logeado);
			break;
		}
		case '2': {
			cout << "OPC2 - RETIRAR" << endl;
			operacionRetirar(logeado);
			break;
		}
		case '3': {
			cout << "OPC3 - TRANSFERIR" << endl;
			operacionTransferencia(logeado);
			break;
		}
		case '4': {
			cout << "OPC4 - PAGO SERVICIO" << endl;
			operacionPagarServicio(logeado);
			break;
		}
		case '5': {
			cout << "OPC5 - CONSULTAR SALDO" << endl;
			operacionConsultarSaldo(logeado);
			break;
		}
		case '6': {
			cargardesdeArchivoOperaciones();
			system("cls");
			cout << "OPC6 - CONSULTAR MOVIMIENTOS" << endl;
			listarOperaciones();
			break;
		}
		case '7': {
			login();//Volver al Login
			break;
		}
		}
		system("pause");
	} while (opc != '7');//ACABA CUANDO UNA OPCION SALGA 7
	return 0;

}
char opcmenuAdministrador() {
	char opc;
	cout << "============================" << endl;
	cout << "     MENU ADMINISTRADOR      " << endl;
	cout << "============================" << endl;
	cout << "[1] GESTIONAR CLIENTES" << endl;
	cout << "[2] GESTIONAR DISPENSADORES" << endl;
	cout << "[3] REGRESAR AL INICIO" << endl;
	cout << "Seleccione una opcion: ";
	opc = _getche();
	return opc;
}
//SUBMENUS DEL ADMINISTRADOR
char opcmenuGestClie() {
	char opc;
	cout << "==========================" << endl;
	cout << "     GESTION CLIENTES     " << endl;
	cout << "==========================" << endl;
	cout << "[1] AGREGAR CLIENTES" << endl;
	cout << "[2] MODIFICAR CLIENTES" << endl;
	cout << "[3] BAJA DE CLIENTE" << endl;
	cout << "[4] BUSCAR " << endl;
	cout << "[5] LISTAR CLIENTES" << endl;
	cout << "[6] REGRESAR AL MENU ADMIN" << endl;
	cout << "Seleccione una opcion: ";
	opc = _getche();
	return opc;
}
char opcmenuGestDisp() {
	char opc;
	cout << "===============================" << endl;
	cout << "     GESTION DISPENSADORES     " << endl;
	cout << "===============================" << endl;
	cout << "[1] AGREGAR DISPENSADOR" << endl;
	cout << "[2] MODIFICAR DISPENSADOR" << endl;
	cout << "[3] BUSCAR DISPENSADOR" << endl;
	cout << "[4] LISTAR DISPENSADORES" << endl;
	cout << "[5] REGRESAR AL MENU ADMIN" << endl;
	cout << "Seleccione una opcion: ";
	opc = _getche();
	return opc;
}
char opcmenuCliente() {
	char opc;
	cout << "==========================" << endl;
	cout << "       MENU CLIENTE      " << endl;
	cout << "==========================" << endl;
	cout << "[1] DEPOSITAR" << endl;
	cout << "[2] RETIRAR" << endl;
	cout << "[3] TRANSFERIR" << endl;
	cout << "[4] PAGAR SERVICIO" << endl;
	cout << "[5] CONSULTAR SALDO" << endl;
	cout << "[6] CONSULTAR MOVIMIENTOS" << endl;
	cout << "[7] REGRESAR AL INICIO" << endl;
	cout << "Seleccione una opcion: ";
	opc = _getche();
	return opc;
}

//METODOS CLIENTES
void cargardesdeArchivo() {
	clientes.clear();
	ifstream lectura;
	string codigo, nombre, apellido, saldo, usuario, contrasena, rango;
	Clientes c1;
	lectura.open(ARCHIVO_CLIENTES.c_str(), ios::in);

	if (lectura.fail())
	{
		cout << "No puedo abrir el archivo" << endl;
		return;
	}

	while (!lectura.eof())
	{
		getline(lectura, codigo, ';');
		getline(lectura, nombre, ';');
		getline(lectura, apellido, ';');
		getline(lectura, saldo, ';');
		getline(lectura, usuario, ';');
		getline(lectura, contrasena, '\n');

		if (codigo.length() > 0)
		{
			c1.setDni(atoi(codigo.c_str()));
			c1.setNombre(nombre);
			c1.setApellido(apellido);
			c1.setSaldo(atof(saldo.c_str()));
			c1.setUsuario(usuario);
			c1.setContrasena(contrasena);

			guardarenlista(c1);
		}
		cout << endl;
	}
	lectura.close();
}
void guardarenlista(Clientes C) {
	clientes.push_back(C);
}
void agregarCliente()
{
	int dni;
	string nombre, apellido, usuario, contrasena;
	double saldo;
	Clientes c;//INSTANCIAS EL OBJETO CLIENTE
	cout << endl;
	cout << "Registrar Cliente" << endl;
	cout << "DNI: ";
	cin >> dni;
	cin.ignore();
	cout << "Nombre: ";
	cin >> nombre;
	cin.ignore();
	cout << "Apellido: ";
	cin >> apellido;
	cin.ignore();
	cout << "Saldo: ";
	cin >> saldo;
	cin.ignore();
	cout << "Usuario: ";
	cin >> usuario;
	cin.ignore();
	cout << "Contrasena: ";
	cin >> contrasena;
	cout << endl;
	c.setDni(dni);
	c.setNombre(nombre);
	c.setApellido(apellido);
	c.setSaldo(saldo);
	c.setUsuario(usuario);
	c.setContrasena(contrasena);
	guardarenArchivo(c, ARCHIVO_CLIENTES.c_str());
	cout << "Se registro el cliente!!\n" << endl;
}
void guardarenArchivo(Clientes c, string txt) {
	ofstream outArchivo;
	outArchivo.open(txt, ios::out | ios::app);
	outArchivo << c.getDni() << ";";
	outArchivo << c.getNombre() << ";";
	outArchivo << c.getApellido() << ";";
	outArchivo << c.getSaldo() << ";";
	outArchivo << c.getUsuario() << ";";
	outArchivo << c.getContrasena() << "\n";
	outArchivo.close();
}
void ordenarBurbuja()
{
	int n = clientes.size();
	Clientes aux;

	for (int i = 0; i < n; i++) {

		for (int k = 0; k < n - 1; k++) {

			if (clientes.at(k).getNombre() > clientes.at(k + 1).getNombre())
			{
				aux = clientes[k];
				clientes[k] = clientes[k + 1];
				clientes[k + 1] = aux;
			}
		}
	}
}
void listarCliente()
{
	ordenarBurbuja();
	cout << endl << "=====================================   CLIENTES REGISTRADOS  =====================================" << endl;
	cout << endl << "|  DNI  |   |     NOMBRE     | |     APELLIDO     ||     SALDO     | |   USUARIO   | |   CONTRASENA" << endl;


	if (!clientes.empty()) {
		for (Clientes x : clientes)
		{
			cout.width(12); cout << left << x.getDni();
			cout.width(20); cout << left << x.getNombre();
			cout.width(20); cout << left << x.getApellido();

			cout << "S/";
			cout.width(12); cout << setprecision(2) << fixed << right << x.getSaldo();
			cout << "    ";

			cout.width(20); cout << left << x.getUsuario();
			cout.width(20); cout << left << x.getContrasena();
			cout << endl;
		}
	}
	else {
		cout << "LA LISTA ESTA VACIA!!" << endl;
	}
	cout << endl;
	cout << "Clientes: " << clientes.size() << endl;
	cout << endl;
}
void modificarArchivo() {
	for (Clientes x : clientes)
	{
		guardarenArchivo(x, ARCHIVO_TEMPORAL_CLIENTES.c_str());
	}
	remove(ARCHIVO_CLIENTES.c_str());
	rename(ARCHIVO_TEMPORAL_CLIENTES.c_str(), ARCHIVO_CLIENTES.c_str());
}
int getidxCliente(int tempCli) {
	int idx = -1;
	for (Clientes x : clientes)
	{
		idx++;
		if (x.getDni() == tempCli) {
			return idx;
		}
	}
	return -1;
}
void buscarCliente() {
	int cod;
	cout << "INGRESE DNI DEL CLIENTE: ";
	cin >> cod;
	int idx = getidxCliente(cod);
	if (idx != -1) {
		Clientes encontrado = clientes.at(idx);
		cout << "CLIENTE ENCONTRADO!!" << endl;
		cout << "*****************" << endl;
		cout << "DNI: " << encontrado.getDni()
			<< "\nNombre: " << encontrado.getNombre()
			<< "\nApellido: " << encontrado.getApellido()
			<< "\nSaldo: " << encontrado.getSaldo()
			<< "\nUsuario: " << encontrado.getUsuario()
			<< "\nContrasena: " << encontrado.getContrasena() << endl;

		cout << "*****************" << endl;
	}
	else {
		cout << "ERROR!!! Cliente no encontrado..." << endl;
	}
}
void modificarCliente()
{
	string newname, newapellido, newusuario, newcontrasena;
	double newsaldo;
	int tempCli;

	cout << "INGRESE DNI DEL CLIENTE A MODIFICAR: ";
	cin >> tempCli;

	int idx = getidxCliente(tempCli);

	if (idx != -1) {
		Clientes encontrado = clientes.at(idx);
		cout << "CLIENTE ENCONTRADO!!" << endl;
		cout << "DNI: " << encontrado.getDni()
			<< "\nNombre: " << encontrado.getNombre()
			<< "\nApellido: " << encontrado.getApellido()
			<< "\nSaldo: " << encontrado.getSaldo()
			<< "\nUsuario: " << encontrado.getUsuario()
			<< "\nContrasena: " << encontrado.getContrasena() << endl;
		cout << "\nINGRESE NUEVO NOMBRE DEL CLIENTE: ";
		cin >> newname;
		cout << "\nINGRESE NUEVO APELLIDO DEL CLIENTE: ";
		cin >> newapellido;
		cout << "\nINGRESE NUEVO SALDO DEL CLIENTE: ";
		cin >> newsaldo;
		cout << "\nINGRESE NUEVO USUARIO DEL CLIENTE: ";
		cin >> newusuario;
		cout << "\nINGRESE NUEVA CONTRASEÑA DEL CLIENTE: ";
		cin >> newcontrasena;

		clientes[idx].setNombre(newname);
		clientes[idx].setApellido(newapellido);
		clientes[idx].setSaldo(newsaldo);
		clientes[idx].setUsuario(newusuario);
		clientes[idx].setContrasena(newcontrasena);


		modificarArchivo();
		cout << "CLIENTE ACTUALIZADO!! " << endl;
	}
	else {
		cout << "ERROR!!! Cliente no encontrado..." << endl;
	}
}
void eliminarCliente()
{
		int tempCli;

	cout << "INGRESE DNI DEL CLIENTE A ELIMINAR: ";
	cin >> tempCli;

	int idx = getidxCliente(tempCli);

	if (idx != -1) {
		Clientes encontrado = clientes.at(idx);
		cout << "CLIENTE ENCONTRADO!!" << endl;
		cout << "DNI: " << encontrado.getDni()
			<< "\nNombre: " << encontrado.getNombre()
			<< "\nApellido: " << encontrado.getApellido()
			<< "\nSaldo: " << encontrado.getSaldo()
			<< "\nUsuario: " << encontrado.getUsuario()
			<< "\nContrasena: " << encontrado.getContrasena() << endl;
		clientes.erase(clientes.begin() + idx);
		modificarArchivo();
		cout << "CLIENTE ELIMINADO..." << endl;
	}
	else {
		cout << "ERROR!!! Cliente no encontrado..." << endl;
	}
}

//METODOS DISPENSADORES
void guardarenArchivoD(Dispensadores d, string txt) {
	ofstream outArchivo;
	outArchivo.open(txt, ios::out | ios::app);
	outArchivo << d.getCodigo() << ";";
	outArchivo << d.getLugar() << ";";
	outArchivo << d.getCant10() << ";";
	outArchivo << d.getCant20() << ";";
	outArchivo << d.getCant50() << ";";
	outArchivo << d.getCant100() << ";";
	outArchivo << d.getCant200() << ";";
	outArchivo << d.getTotal() << "\n";
	outArchivo.close();
}
void cargardesdeArchivoD() {
	dispensadores.clear();
	ifstream lectura;
	string codigo, lugar, cant10, cant20, cant50, cant100, cant200;
	Dispensadores d1;
	lectura.open(ARCHIVO_DISPENSADORES.c_str(), ios::in);

	if (lectura.fail()) //VALIDAR SI SE PUDO ABRIR EL ARCHIVO
	{
		cout << "No se pudo abrir el archivo" << endl;
		return;
	}

	while (!lectura.eof())
	{
		getline(lectura, codigo, ';');
		getline(lectura, lugar, ';');
		getline(lectura, cant10, ';');
		getline(lectura, cant20, ';');
		getline(lectura, cant50, ';');
		getline(lectura, cant100, ';');
		getline(lectura, cant200, '\n');

		if (codigo.length() > 0)//existen datos
		{
			d1.setCodigo(atoi(codigo.c_str()));
			d1.setLugar(lugar);
			d1.setCant10(atoi(cant10.c_str()));
			d1.setCant20(atoi(cant20.c_str()));
			d1.setCant50(atoi(cant50.c_str()));
			d1.setCant100(atoi(cant100.c_str()));
			d1.setCant200(atoi(cant200.c_str()));
			guardarenlistaD(d1);
		}
	}
	lectura.close();
}
void guardarenlistaD(Dispensadores D) {
	dispensadores.push_back(D);
}
void agregarDispensador()
{
	int codigo;
	string lugar;
	int cant10;
	int cant20;
	int cant50;
	int cant100;
	int cant200;

	Dispensadores d;
	cout << endl;
	cout << "Registrar Dispensador" << endl;
	cout << "Codigo: ";
	cin >> codigo;
	cin.ignore();
	cout << "Lugar: ";
	cin >> lugar;
	cin.ignore();
	cout << "Cant. Billetes 10: ";
	cin >> cant10;
	cin.ignore();
	cout << "Cant. Billetes 20: ";
	cin >> cant20;
	cin.ignore();
	cout << "Cant. Billetes 50: ";
	cin >> cant50;
	cin.ignore();
	cout << "Cant. Billetes 100: ";
	cin >> cant100;
	cin.ignore();
	cout << "Cant. Billetes 200: ";
	cin >> cant200;

	cout << endl;
	d.setCodigo(codigo);
	d.setLugar(lugar);
	d.setCant10(cant10);
	d.setCant20(cant20);
	d.setCant50(cant50);
	d.setCant100(cant100);
	d.setCant200(cant200);

	guardarenArchivoD(d, ARCHIVO_DISPENSADORES.c_str());
	cout << "Se registro el dispensador!!\n" << endl;
}
void ordenarBurbujaDispensadores()
{
	int n = dispensadores.size();
	Dispensadores aux;

	for (int i = 0; i < n; i++) {

		for (int k = 0; k < n - 1; k++) {

			if (dispensadores.at(k).getCodigo() > dispensadores.at(k + 1).getCodigo())
			{
				aux = dispensadores[k];
				dispensadores[k] = dispensadores[k + 1];
				dispensadores[k + 1] = aux;
			}
		}
	}
}
void listarDispensadores()
{
	cargardesdeArchivoD();
	ordenarBurbujaDispensadores();
	cout << endl << "===================DISPENSADORES REGISTRADOS==================" << endl << endl;
	if (!dispensadores.empty()) {
		for (Dispensadores x : dispensadores)
		{
			cout.width(8); cout << left << x.getCodigo();
			cout.width(15); cout << left << x.getLugar();
			cout.width(8); cout << left << x.getCant10();
			cout.width(8); cout << left << x.getCant20();
			cout.width(8); cout << left << x.getCant50();
			cout.width(8); cout << left << x.getCant100();
			cout.width(5); cout << left << x.getCant200();
			cout.width(5); cout << right << x.getTotal();
			cout << endl;
		}
	}
	else {
		cout << "LA LISTA ESTA VACIA!!" << endl;
	}
	cout << endl;
	cout << "Dispensadores: " << dispensadores.size() << endl;
}
void modificarArchivoD() {
	for (Dispensadores x : dispensadores)
	{
		guardarenArchivoD(x, ARCHIVO_TEMPORAL_DISPENSASDORES.c_str());
	}
	remove(ARCHIVO_DISPENSADORES.c_str());
	rename(ARCHIVO_TEMPORAL_DISPENSASDORES.c_str(), ARCHIVO_DISPENSADORES.c_str());
}
int getidxDispensador(int tempDispen) {
	int idx = -1;
	for (Dispensadores x : dispensadores)
	{
		idx++;
		if (x.getCodigo() == tempDispen) {
			return idx;
		}
	}
	return -1;
}
void modificarDispensador()
{
	int tempDispen;
	int newcant10;
	int newcant20;
	int newcant50;
	int newcant100;
	int newcant200;
	int total;

	cout << "INGRESE CODIGO DEL DISPENSADOR A MODIFICAR: ";
	cin >> tempDispen;

	int idx = getidxDispensador(tempDispen);

	if (idx != -1) {
		Dispensadores encontrado = dispensadores.at(idx);
		cout << "DISPENSADOR ENCONTRADO!!" << endl;
		cout << "Codigo: " << encontrado.getCodigo()
			<< "\nLugar: " << encontrado.getLugar()
			<< "\nBilletes s/ 10: " << encontrado.getCant10()
			<< "\nBilletes s/ 20: " << encontrado.getCant20()
			<< "\nBilletes s/ 50: " << encontrado.getCant50()
			<< "\nBilletes s/ 100: " << encontrado.getCant100()
			<< "\nBilletes s/ 200: " << encontrado.getCant200()
			<< "\nTotal Billetes: " << encontrado.getTotal() << endl;
		cout << "\nINGRESE NUEVA CANT. BILLETE 10: ";
		cin >> newcant10;
		cout << "\nINGRESE NUEVA CANT. BILLETE 20: ";
		cin >> newcant20;
		cout << "\nINGRESE NUEVA CANT. BILLETE 50: ";
		cin >> newcant50;
		cout << "\nINGRESE NUEVA CANT. BILLETE 100: ";
		cin >> newcant100;
		cout << "\nINGRESE NUEVA CANT. BILLETE 200: ";
		cin >> newcant200;

		dispensadores[idx].setCant10(newcant10);
		dispensadores[idx].setCant20(newcant20);
		dispensadores[idx].setCant50(newcant50);
		dispensadores[idx].setCant100(newcant100);
		dispensadores[idx].setCant200(newcant200);
		modificarArchivoD();
		cout << "\nDISPENSADOR ACTUALIZADO!! " << endl;
	}
	else {
		cout << "ERROR!!! Dispensador no encontrado..." << endl;
	}
}
void buscarDispensador() {
	int cod;
	cout << "INGRESE CODIGO DEL DISPENSADOR: ";
	cin >> cod;
	int idx = getidxDispensador(cod);
	if (idx != -1) {
		Dispensadores encontrado = dispensadores.at(idx);
		cout << "DISPENSADOR ENCONTRADO!!" << endl;
		cout << "***************************" << endl;
		cout << "Codigo: " << encontrado.getCodigo()
			<< "\nLugar: " << encontrado.getLugar()
			<< "\nBilletes s/ 10: " << encontrado.getCant10()
			<< "\nBilletes s/ 20: " << encontrado.getCant20()
			<< "\nBilletes s/ 50: " << encontrado.getCant50()
			<< "\nBilletes s/ 100: " << encontrado.getCant100()
			<< "\nBilletes s/ 200: " << encontrado.getCant200()
			<< "\nTotal Billetes: " << encontrado.getTotal() << endl;
		cout << "***************************" << endl;
	}
	else {
		cout << "ERROR!!! Dispensador no encontrado..." << endl;
	}
}

//METODOS OPERACIONES CLIENTE
void operacionDepositar(Clientes C)
{
	int idxD=-1, codDis, flag;
	int saldoViejo, saldoNuevo, saldoDepositar;
	Dispensadores encontradoDip;

	cout << "TU SALDO DISPONIBLE: " << C.getSaldo() << endl;
	cout << "INGRESE LA CANTIDAD A DEPOSITAR: ";
	cin >> saldoDepositar;
	desconponerBilletes(saldoDepositar, C, 1);
}
void operacionRetirar(Clientes C)
{
	int idx = getidxCliente(C.getDni());
	int saldoNuevo, saldoRetirar;
	if (idx != -1) {
		Clientes encontrado = clientes.at(idx);

		do {
			system("cls");
			cout << "SALDO DISPONIBLE: " << encontrado.getSaldo() << endl;
			cout << "INGRESE LA CANTIDAD A RETIRAR: ";
			cin >> saldoRetirar;
			
			desconponerBilletes(saldoRetirar, C, 2);
		} while (C.getSaldo() <= saldoRetirar);
	}
}
void operacionTransferencia(Clientes C)
{
	bool checkencontrado = false;
	double saldoViejoEmisor, saldoNuevoEmisor, saldoViejoReceptor, saldoNuevoReceptor, saldoDepositar;

	do {
		system("cls");
		int cod;
		cout << "INGRESE DNI DEL CLIENTE A TRASNFERIR: ";
		cin >> cod;
		int idxReceptor = getidxCliente(cod);
		int idxEmisor = getidxCliente(C.getDni());

		if (idxReceptor != -1) {
			checkencontrado = true;
			string receptorNombre, emisorNombre;
			Clientes encontrado = clientes.at(idxReceptor);
			cout << "CLIENTE ENCONTRADO!!" << endl;
			cout << "USUARIO: " << encontrado.getApellido() << " " << encontrado.getNombre() << "\n" << endl;
			receptorNombre = encontrado.getApellido() + " " + encontrado.getNombre();
			emisorNombre = C.getApellido() + " " + C.getNombre();

			system("pause");

			do {
				system("cls");
				cout << "SALDO DISPONIBLE: " << C.getSaldo() << endl;
				cout << "\nINGRESE LA CANTIDAD A TRANSFERIR: ";
				cin >> saldoDepositar;

				saldoViejoEmisor = C.getSaldo();
				if (saldoViejoEmisor >= saldoDepositar)
				{
					saldoViejoReceptor = encontrado.getSaldo();
					saldoNuevoEmisor = saldoViejoEmisor - saldoDepositar;
					saldoNuevoReceptor = saldoViejoReceptor + saldoDepositar;
					clientes[idxEmisor].setSaldo(saldoNuevoEmisor);
					clientes[idxReceptor].setSaldo(saldoNuevoReceptor);

					modificarArchivo();
					cout << "\nTRANSFERENCIA REALIZADA CON EXITO!!! " << endl;
					cout << "Nuevo saldo: " << saldoNuevoEmisor << endl;

					Operaciones nuevaOperacion;
					nuevaOperacion.setUsuario(C.getUsuario());
					nuevaOperacion.setAccion("TRANSFERENCIA A: "+ receptorNombre);
					nuevaOperacion.setMonto((saldoDepositar));
					nuevaOperacion.setFecha(getHoraOperacion());
					nuevaOperacion.setHora(getFechaOperacion());

					guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());

					Operaciones nuevaOperacion2;
					nuevaOperacion2.setUsuario(encontrado.getUsuario());
					nuevaOperacion2.setAccion("RECIBIO DE " + emisorNombre);
					nuevaOperacion2.setMonto((saldoDepositar));
					nuevaOperacion2.setFecha(getHoraOperacion());
					nuevaOperacion2.setHora(getFechaOperacion());

					guardarenArchivoOperaciones(nuevaOperacion2, ARCHIVO_OPERACIONES.c_str());

				}
				else
				{
					cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
					cout << "Intente de nuevo..." << endl;
					system("pause");
				}
			} while (saldoViejoEmisor <= saldoDepositar);
		}
		else {
			cout << "ERROR!!! Cliente no encontrado..." << endl;
			system("pause");
		}
	} while (checkencontrado == false);
}
void desconponerBilletes(int saldoOperacion, Clientes C, int operacion) {
	int saldoViejo, saldoNuevo;
	bool checkencontrado = false;
	int saldoViejoEmisor, saldoNuevoEmisor, saldoViejoReceptor, saldoNuevoReceptor, saldoTransferir;
	int idxD, codDis, new200, new100, new50, new20, new10;
	int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
	int billetes[] = { 200,100,50,20,10 };
	int tam = sizeof(billetes) / sizeof(*billetes);
	int idx = 0;
	int flag = 0;
	int saldoAux = 0;
	Dispensadores encontradoDip;
	Operaciones nuevaOperacion;
	int idxC = getidxCliente(C.getDni());
		cout << "\nINGRESE EL CODIGO DEL DISPENSADOR A USAR: ";
		cin >> codDis;
		idxD = getidxDispensador(codDis);
		if (idxD != -1) {
			encontradoDip = dispensadores.at(idxD);
			flag = verificarDispensador(encontradoDip, saldoOperacion);
			saldoAux = saldoOperacion;
			if (flag == 1) {
				saldoViejo = C.getSaldo();
				switch (operacion)
				{
				case 1:
					saldoNuevo = saldoViejo + saldoOperacion;
					while (saldoAux > 0)
					{
						while (idx < tam && saldoAux >= billetes[idx])
						{
							saldoAux -= billetes[idx];
							//saldoDepositar = saldoDepositar - billetes[idx];
							if (billetes[idx] == 200) {
								c1++;
							}
							else if (billetes[idx] == 100) {
								c2++;
							}
							else if (billetes[idx] == 50) {
								c3++;
							}
							else if (billetes[idx] == 20) {
								c4++;
							}
							else if (billetes[idx] == 10) {
								c5++;
							}
						}
						idx++;
					}

					new200 = encontradoDip.getCant200();
					new200 += c1;
					new100 = encontradoDip.getCant100();
					new100 += c2;
					new50 = encontradoDip.getCant50();
					new50 += c3;
					new20 = encontradoDip.getCant20();
					new20 += c4;
					new10 = encontradoDip.getCant10();
					new10 += c5;

					dispensadores[idxD].setCant200(new200);
					dispensadores[idxD].setCant100(new100);
					dispensadores[idxD].setCant50(new50);
					dispensadores[idxD].setCant20(new20);
					dispensadores[idxD].setCant10(new10);
					modificarArchivoD();

					clientes[idxC].setSaldo(saldoNuevo);
					modificarArchivo();

					cout << "\nDEPOSITO REALIZADO CON EXITO!!! " << endl;
					cout << "Nuevo saldo: " << saldoNuevo << endl;

					nuevaOperacion.setUsuario(C.getUsuario());
					nuevaOperacion.setAccion("DEPOSITO");
					nuevaOperacion.setMonto((saldoOperacion));
					nuevaOperacion.setFecha(getHoraOperacion());
					nuevaOperacion.setHora(getFechaOperacion());

					guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());
					break;
				case 2:
					if (saldoViejo >= saldoAux) {
						saldoNuevo = saldoViejo - saldoAux;
						while (saldoAux > 0)
						{
							while (idx < tam && saldoAux >= billetes[idx])
							{
								saldoAux -= billetes[idx];
								if (billetes[idx] == 200) {
									c1++;
								}
								else if (billetes[idx] == 100) {
									c2++;
								}
								else if (billetes[idx] == 50) {
									c3++;
								}
								else if (billetes[idx] == 20) {
									c4++;
								}
								else if (billetes[idx] == 10) {
									c5++;
								}
							}
							idx++;
						}

						new200 = encontradoDip.getCant200();
						new200 -= c1;
						new100 = encontradoDip.getCant100();
						new100 -= c2;
						new50 = encontradoDip.getCant50();
						new50 -= c3;
						new20 = encontradoDip.getCant20();
						new20 -= c4;
						new10 = encontradoDip.getCant10();
						new10 -= c5;

						dispensadores[idxD].setCant200(new200);
						dispensadores[idxD].setCant100(new100);
						dispensadores[idxD].setCant50(new50);
						dispensadores[idxD].setCant20(new20);
						dispensadores[idxD].setCant10(new10);
						modificarArchivoD();

						clientes[idxC].setSaldo(saldoNuevo);
						modificarArchivo();

						cout << "\RETIRO REALIZADO CON EXITO!!! " << endl;
						cout << "Nuevo saldo: " << saldoNuevo << endl;

						nuevaOperacion.setUsuario(C.getUsuario());
						nuevaOperacion.setAccion("RETIRO");
						nuevaOperacion.setMonto((saldoOperacion));
						nuevaOperacion.setFecha(getHoraOperacion());
						nuevaOperacion.setHora(getFechaOperacion());

						guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());
					}
					else {
						cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
						cout << "Intente de nuevo..." << endl;
						system("pause");
					}
					break;
				}
			}
			else {
				cout << "El dispensador no cuenta con saldo suficiente!!" << endl;
				cout << "INTENTE CON OTRO!!" << endl;
				desconponerBilletes(saldoOperacion, C, operacion);
			}
		}
		else {
			cout << "CODIGO INCORRECTO!!";
			cout << "Intentelo de nuevo...";
		}
	
}
void operacionConsultarSaldo(Clientes C)
{
	int idx = getidxCliente(C.getDni());
	Clientes encontrado = clientes.at(idx);
	cout << "SALDO DISPONIBLE: " << encontrado.getSaldo() << endl;
}
void generarCobroServicios()
{
	double serv_agua;
	double serv_luz;
	double serv_telefono;
	double serv_gas;
	double serv_internet;

	PrecioServicios.clear();
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<> distr1(20, 150);
	serv_agua = distr1(gen);

	uniform_int_distribution<> distr2(90, 200);
	serv_luz = distr2(gen);

	uniform_int_distribution<> distr3(25, 50);
	serv_telefono = distr3(gen);

	uniform_int_distribution<> distr4(15, 50);
	serv_gas = distr4(gen);

	uniform_int_distribution<> distr5(90, 200);
	serv_internet = distr5(gen);

	PrecioServicios.push_back(serv_agua);
	PrecioServicios.push_back(serv_luz);
	PrecioServicios.push_back(serv_telefono);
	PrecioServicios.push_back(serv_gas);
	PrecioServicios.push_back(serv_internet);
}
void operacionPagarServicio(Clientes C)
{
	int opcion;
	int idx = getidxCliente(C.getDni());
	Clientes encontrado = clientes.at(idx);
	cout << "==================================== PAGO DE SERVICIOS ====================================" << endl;
	cout << "[AGUA: S/"; cout << setprecision(2) << fixed << PrecioServicios.at(0) << "]  ";
	cout << "[LUZ: S/"; cout << setprecision(2) << fixed << PrecioServicios.at(1) << "]  ";
	cout << "[TELEFONO: S/"; cout << setprecision(2) << fixed << PrecioServicios.at(2) << "]  ";
	cout << "[GAS: S/"; cout << setprecision(2) << fixed << PrecioServicios.at(3) << "]  ";
	cout << "[INTERNET: S/"; cout << setprecision(2) << fixed << PrecioServicios.at(4) << "]\n" << endl;

	cout << "SALDO DISPONIBLE: " << encontrado.getSaldo() << endl;
	cout << "INGRESE EL SERVICIO A PAGAR: " << endl;
	cout << "[1] AGUA" << endl;
	cout << "[2] LUZ" << endl;
	cout << "[3] TELEFONO" << endl;
	cout << "[4] GAS " << endl;
	cout << "[5] INTERNET" << endl;
	cout << "[6] PAGAR TODOS" << endl;
	cin >> opcion;

	double saldoViejo = 0.0, saldoNuevo = 0.0, montoaPagar = 0.0;

	switch (opcion)
	{
	case 1:
		do {
			montoaPagar = PrecioServicios.at(0);
			saldoViejo = encontrado.getSaldo();
			if (saldoViejo >= montoaPagar)
			{
				saldoNuevo = saldoViejo - montoaPagar;

				clientes[idx].setSaldo(saldoNuevo);

				modificarArchivo();
				cout << "\nPAGO REALIZADO CON EXITO!!! " << endl;
				cout << "Nuevo saldo: " << saldoNuevo << endl;

				Operaciones nuevaOperacion;
				nuevaOperacion.setUsuario(C.getUsuario());
				nuevaOperacion.setAccion("PAGO DE AGUA");
				nuevaOperacion.setMonto((montoaPagar));
				nuevaOperacion.setFecha(getHoraOperacion());
				nuevaOperacion.setHora(getFechaOperacion());

				guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());
			}
			else
			{
				cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
				cout << "Intente de nuevo..." << endl;
				system("pause");
			}
		} while (saldoViejo <= montoaPagar);

		break;

	case 2:
		do {
			montoaPagar = PrecioServicios.at(1);
			saldoViejo = encontrado.getSaldo();
			if (saldoViejo >= montoaPagar)
			{
				saldoNuevo = saldoViejo - montoaPagar;

				clientes[idx].setSaldo(saldoNuevo);

				modificarArchivo();
				cout << "\nPAGO REALIZADO CON EXITO!!! " << endl;
				cout << "Nuevo saldo: " << saldoNuevo << endl;

				Operaciones nuevaOperacion;
				nuevaOperacion.setUsuario(C.getUsuario());
				nuevaOperacion.setAccion("PAGO DE LUZ");
				nuevaOperacion.setMonto((montoaPagar));
				nuevaOperacion.setFecha(getHoraOperacion());
				nuevaOperacion.setHora(getFechaOperacion());

				guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());  
			}
			else
			{
				cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
				cout << "Intente de nuevo..." << endl;
				system("pause");
			}
		} while (saldoViejo <= montoaPagar);


		break;

	case 3:
		do {
			montoaPagar = PrecioServicios.at(3);
			saldoViejo = encontrado.getSaldo();
			if (saldoViejo >= montoaPagar)
			{
				saldoNuevo = saldoViejo - montoaPagar;

				clientes[idx].setSaldo(saldoNuevo);

				modificarArchivo();
				cout << "\nPAGO REALIZADO CON EXITO!!! " << endl;
				cout << "Nuevo saldo: " << saldoNuevo << endl;

				Operaciones nuevaOperacion;
				nuevaOperacion.setUsuario(C.getUsuario());
				nuevaOperacion.setAccion("PAGO DE TELEFONO");
				nuevaOperacion.setMonto((montoaPagar));
				nuevaOperacion.setFecha(getHoraOperacion());
				nuevaOperacion.setHora(getFechaOperacion());

				guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());
			}
			else
			{
				cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
				cout << "Intente de nuevo..." << endl;
				system("pause");
			}
		} while (saldoViejo <= montoaPagar);


		break;

	case 4:

		do {
			montoaPagar = PrecioServicios.at(4);
			saldoViejo = encontrado.getSaldo();
			if (saldoViejo >= montoaPagar)
			{
				saldoNuevo = saldoViejo - montoaPagar;

				clientes[idx].setSaldo(saldoNuevo);

				modificarArchivo();
				cout << "\nPAGO REALIZADO CON EXITO!!! " << endl;
				cout << "Nuevo saldo: " << saldoNuevo << endl;

				Operaciones nuevaOperacion;
				nuevaOperacion.setUsuario(C.getUsuario());
				nuevaOperacion.setAccion("PAGO DE GAS");
				nuevaOperacion.setMonto((montoaPagar));
				nuevaOperacion.setFecha(getHoraOperacion());
				nuevaOperacion.setHora(getFechaOperacion());

				guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());
			}
			else
			{
				cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
				cout << "Intente de nuevo..." << endl;
				system("pause");
			}
		} while (saldoViejo <= montoaPagar);

		break;

	case 5:
		do {
			montoaPagar = PrecioServicios.at(5);
			saldoViejo = encontrado.getSaldo();
			if (saldoViejo >= montoaPagar)
			{
				saldoNuevo = saldoViejo - montoaPagar;

				clientes[idx].setSaldo(saldoNuevo);

				modificarArchivo();
				cout << "\nPAGO REALIZADO CON EXITO!!! " << endl;
				cout << "Nuevo saldo: " << saldoNuevo << endl;
				
				Operaciones nuevaOperacion;
				nuevaOperacion.setUsuario(C.getUsuario());
				nuevaOperacion.setAccion("PAGO DE INTERNET");
				nuevaOperacion.setMonto((montoaPagar));
				nuevaOperacion.setFecha(getHoraOperacion());
				nuevaOperacion.setHora(getFechaOperacion());

				guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());
			}
			else
			{
				cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
				cout << "Intente de nuevo..." << endl;
				system("pause");
			}
		} while (saldoViejo <= montoaPagar);


		break;

	case 6:
		double sumaMontos = 0.0;
		for (int i = 0; i < PrecioServicios.size(); i++)
		{
			montoaPagar = PrecioServicios.at(i);
			sumaMontos += montoaPagar;
		}
		do {
			saldoViejo = encontrado.getSaldo();
			if (saldoViejo >= sumaMontos)
			{
				saldoNuevo = saldoViejo - sumaMontos;

				clientes[idx].setSaldo(saldoNuevo);

				modificarArchivo();
				cout << "\nTotal: " << sumaMontos << endl;
				cout << "\nPAGO REALIZADO CON EXITO!!! " << endl;
				cout << "Nuevo saldo: " << saldoNuevo << endl;

				Operaciones nuevaOperacion;
				nuevaOperacion.setUsuario(C.getUsuario());
				nuevaOperacion.setAccion("PAGO DE TODOS");
				nuevaOperacion.setMonto((sumaMontos));
				nuevaOperacion.setFecha(getHoraOperacion());
				nuevaOperacion.setHora(getFechaOperacion());

				guardarenArchivoOperaciones(nuevaOperacion, ARCHIVO_OPERACIONES.c_str());
			}
			else
			{
				cout << "\nERORR!!! No dispone de saldo suficiente..." << endl;
				cout << "Intente de nuevo..." << endl;
				system("pause");
			}
		} while (saldoViejo <= sumaMontos);
		break;
	}
}
void guardarenlistaOperaciones(Operaciones operacion_) {
	vec_operaciones.push_back(operacion_);
}
void guardarenArchivoOperaciones(Operaciones operacion_, string txt) {
	ofstream outArchivo;
	outArchivo.open(txt, ios::out | ios::app);
	outArchivo << operacion_.getUsuario() << ";";
	outArchivo << operacion_.getAccion() << ";";
	outArchivo << operacion_.getMonto() << ";";
	outArchivo << operacion_.getFecha() << ";";
	outArchivo << operacion_.getHora() << "\n";
	outArchivo.close();
}
void listarOperaciones()
{
	cout << endl << "================================================   CLIENTES REGISTRADOS  ================================================";
	cout << endl << "|   USUARIO   | |                ACCION                ||      MONTO      |  |  HORA  | |  FECHA  |" <<endl;

	if (!clientes.empty()) {
		for (Operaciones x : vec_operaciones)
		{
			if (logeado.getUsuario() == x.getUsuario() )
			{
				cout.width(18); cout << left << x.getUsuario();
				
				cout.width(40); cout << left << x.getAccion();

				cout << "S/";
				cout.width(14); cout << setprecision(2) << fixed << right << x.getMonto();
				cout << "    ";

				cout.width(10); cout << left << x.getFecha();
				cout.width(15); cout << left << x.getHora();
				cout << endl;
			}

		}
	}
	else {
		cout << "LA LISTA ESTA VACIA!!" << endl;
	}
	cout << endl;
}
void cargardesdeArchivoOperaciones() {
	vec_operaciones.clear();
	ifstream lectura;
	string usuario,accion,monto,fecha,hora;
	Operaciones op1;
	lectura.open(ARCHIVO_OPERACIONES.c_str(), ios::in);

	if (lectura.fail())
	{
		cout << "No puedo abrir el archivo" << endl;
		return;
	}

	while (!lectura.eof())
	{
		getline(lectura, usuario, ';');
		getline(lectura, accion, ';');
		getline(lectura, monto, ';');
		getline(lectura, fecha, ';');
		getline(lectura, hora, '\n');

		if (usuario.length() > 0)
		{
			op1.setUsuario(usuario);
			op1.setAccion(accion);
			op1.setMonto(atoi(monto.c_str()));
			op1.setFecha(fecha);
			op1.setHora(hora);

			guardarenlistaOperaciones(op1);
		}
		cout << endl;
	}
	lectura.close();
}

string getHoraOperacion()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);
	ostringstream hora;
	hora << put_time(&tm, "%H:%M:%S");
	auto strHora = hora.str();
	string horaGenerada = strHora;
	return horaGenerada;
}
string getFechaOperacion()
{
	auto t = time(nullptr);
	auto tm = *localtime(&t);

	ostringstream fecha;
	fecha << put_time(&tm, "%d-%m-%Y");
	auto strFecha = fecha.str();
	
	string fechaGenerada = strFecha;
	return fechaGenerada;
}
int verificarDispensador(Dispensadores D, int saldoOperacion) {

	if (D.getTotal() >= saldoOperacion) {
		return 1;
	}
	else {
		return 0;
	}
}







