#include "pch.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

//Estructura del Arbol
struct AVLNodo {

	int dato;
	AVLNodo *izq;
	AVLNodo *der;
	AVLNodo *raiz;
	int altura;
	int posicion;

};

//Estructura del Archivo
struct AVLNodeFile {

	int Hizq;
	int Hder;
	int valor;

};

AVLNodo *raiz = NULL;

//Prototipos
AVLNodo *CrearNodo(int);
void insertar(AVLNodo *&, int);
int altura(AVLNodo *);
void actualizarAltura(AVLNodo *&);
void balancear(AVLNodo *&);
void rotar_s(AVLNodo *&, bool);			//Movimiento Rotacion Simple 
void rotar_d(AVLNodo *&, bool);			//Movimiento Rotacion Doble
bool busqueda(AVLNodo *&, int);

void guardarArbol(AVLNodo *&);
int pos(AVLNodo *);
void actualizarIndice(AVLNodo *&);

AVLNodo *izquierdo(AVLNodo *);			//Devuelve el subarbol izquierdo
AVLNodo *derecho(AVLNodo *);			//Devuelve el subarbol derecho

//Eliminacion
int EncontrarMayor(AVLNodo *&);
int EncontrarMenor(AVLNodo *&);
void Eliminar(AVLNodo *&, int);

//Imprimir Arbol
void preOrden(AVLNodo *&);
void inOrden(AVLNodo *&);
void postOrden(AVLNodo *&);
//Imprime todo el arbol
void mostrarArbol(AVLNodo *&, int);
void mostrarArchivo();

int main(){

	int opcion = 0;
	int valor = 0, valor2 = 0, datoB = 0, contador = 0, valorX = 0;
	int a = 0, x = 0;	//Variables de datos a eliminar

	do {

		cout << "Menu Inicial" << endl;
		cout << "1. Insertar Nodo" << endl;
		cout << "2. Eliminar Nodo" << endl;		//metodo sucesor, predecesor
		cout << "3. Buscar Nodo" << endl;
		cout << "4. Imprimir Arbol" << endl;
		cout << "5. Mostar Archivo" << endl;
		cout << "6. Salir" << endl;
		cin >> opcion;

		
		switch (opcion) {
		case 1:
			cout << "Ingresa el nodo a ingresar: ";
			cin >> valor;
			insertar(raiz, valor);
			actualizarIndice(raiz);
			cout << "Valor ingresado exitosamente!" << endl << endl;
			break;
		case 2:
			
			cout << "Ingresa el nodo que quieres eliminar: ";
			cin >> x;

			Eliminar(raiz, x);
			actualizarIndice(raiz);

			break;
		case 3:
			cout << "Ingresa el numero que estas buscando: ";
			cin >> datoB;

			if (busqueda(raiz, datoB) == true) {
				cout << "\nElemento " << datoB << " a sido encontrado con exito!" << endl;
			}
			else {
				cout << "Elemento no encontrado!" << endl;
			}

			break;
		case 4:

			cout << "Que metodo quieres usar?" << endl;
			cout << "1. PreOrden" << endl;
			cout << "2. InOrden" << endl;
			cout << "3. PostOrden" << endl;
			cin >> valor2;

			//Menu de Recorrido de Arbol
			switch (valor2) {
			case 1:
				cout << "Imprimiendo Arbol -PreOrden-" << endl;
				preOrden(raiz);
				cout << "\n\n";
				break;
			case 2:
				cout << "Imprimiendo Arbol -InOrden-" << endl;
				inOrden(raiz);
				cout << "\n\n" << endl;
				break;
			case 3:
				cout << "Imprimiendo Arbol -PostOrden-" << endl;
				postOrden(raiz);
				cout << "\n\n";
				break;
			}
			break;

		case 5:
			cout << endl;
			mostrarArchivo();
			cout << endl;
			break;
		case 10:
			cout << "Imprimiendo Arbol Completo" << endl;
			mostrarArbol(raiz, contador);
			cout << "\n\n" << endl; 
			break;
		}


	} while (opcion != 6);

	system("pause > null");
	cout << "Hasta Pronto!" << endl;

}

//Definiciones
AVLNodo * CrearNodo(int x) {
	
	AVLNodo *nuevo = new AVLNodo();
	nuevo->dato = x;
	nuevo->der = NULL;
	nuevo->izq = NULL;
	nuevo->altura = 0;
	
	guardarArbol(nuevo);
	return nuevo;
}
void insertar(AVLNodo *&t, int x) {

	if (t == NULL) {	//Si el arbol esta vacio

		AVLNodo *nuevo = CrearNodo(x);
		t = nuevo;
		actualizarAltura(t);
		guardarArbol(t);
		
	}
	else {				//Si el arbol tiene un nodo o mas

		int valorRaiz = t->dato;

		if (x < valorRaiz) {	//Si el elemento es menor a la raiz, lo insertamos a la izquierda
			insertar(t->izq, x);
		}
		else {					//Si el elemento es mayor a la raiz, lo insertamos a la derecha
			insertar(t->der, x);
		}

		actualizarAltura(t);
		balancear(t);
		
	}

}
int altura(AVLNodo *t) {

	if (t == NULL) {
		return -1;
	}
	else {
		return t->altura;
	}

}				//Devuelve la altura del nodo en el arbol
void actualizarAltura(AVLNodo *&t) {

	if (!t == NULL) {
		t->altura = max(altura((t)->izq), altura((t)->der)) + 1;
	}

}		//Actualiza la altura de un nodo cualquiera del arbol
bool busqueda(AVLNodo *&t, int x) {

	if (t == NULL) {
		return false;
	}
	else if (t->dato == x) {
		return true;
	}
	else if (x < t->dato) {
		return busqueda(t->izq,x);
	}
	else {
		return busqueda(t->der,x);
	}

}
void balancear(AVLNodo *&t) {

	if (!t == NULL) {
		
		int alturaN = altura(izquierdo(t)) - altura(derecho(t));
		
		if (alturaN == 2) {		//Desequilibrio a la izquierda

			if (altura((t)->izq->izq) >= altura((t)->izq->der)) {
				rotar_s(t, true);
			}
			else {
				rotar_d(t, true);
			}

		}
		else if (alturaN == -2) {

			if (altura((t)->der->der) >= altura((t)->der->izq)) {
				rotar_s(t, false);
			}

			else {
				rotar_d(t, false);
			}

		}
	}
}
AVLNodo *izquierdo(AVLNodo *t) {

	if (t == NULL) {
		return nullptr;
	}
	else {

		return t->izq;

	}

}
AVLNodo *derecho(AVLNodo *t) {


	if (t == NULL) {

		return nullptr;
	
	}
	else {

		return t->der;

	}

}

//Movimientos de Rotacion
void rotar_s(AVLNodo *&t, bool izq) {

	AVLNodo *t1;

	if (izq) {						//Rotacion Izquierda

		t1 = izquierdo(t);
		(t)->izq = derecho(t1);
		t1->der = t;
	}
	else {							//Rotacion Derecha
		t1 = derecho(t);
		(t)->der = izquierdo(t1);
		t1->izq = t;
	}

	//Actualizmos las alturas de ambos nodos nuevos
	actualizarAltura(t);
	actualizarAltura(t1);

	//Asignamos la nueva raiz
	t = t1;

}
void rotar_d(AVLNodo *&t, bool izq) {

	if (izq) {		//Movimiento a la izquierda

		rotar_s((t)->izq, false);
		rotar_s(t, true);

	}
	else {			//Movimiento a la derecha

		rotar_s((t)->der, true);	//Era true
		rotar_s(t, false);			//Era false

	}

}

//Recorridos del Arbol
void preOrden(AVLNodo *&t) {

	if (t == NULL) {
		return;
	}
	else {
		cout << t->dato << " - ";
		preOrden(t->izq);
		preOrden(t->der);
	}

}
void inOrden(AVLNodo *&t) {

	if (t == NULL) {
		return;
	}
	else {

		inOrden(t->izq);
		cout << t->dato << " - ";
		inOrden(t->der);

	}

}
void postOrden(AVLNodo *&t) {

	if (t == NULL) {
		return;
	}
	else {

		postOrden(t->izq);
		postOrden(t->der);
		cout << t->dato << " - ";

	}

}
void mostrarArbol(AVLNodo *&t, int contador) {

	balancear(t);
	actualizarAltura(t);

	if (t == NULL) {
		return;
	}
	else {
		mostrarArbol(t->der, contador + 1);
		for (int a = 0; a < contador; a++) {
			cout <<"   ";
		}

		cout <<t->dato<< endl;
		mostrarArbol(t->izq, contador + 1);

	}

}

//Definicion de Eliminacion
int EncontrarMayor(AVLNodo *&t) {

	int x;
	if (t->der == NULL) {
		x = t->dato;
		t = t->izq;
		return x;
	}
	else {
		x = EncontrarMayor(t->der);
		return x;
	}

}
int EncontrarMenor(AVLNodo *&t) {

	int x;
	if (t->izq == NULL) {
		x = t->dato;
		t = t->der;
		return x;
	}
	else {
		x = EncontrarMenor(t->izq);
		return x;
	}

}
void Eliminar(AVLNodo *&t, int x) {

	AVLNodo * aux;

	if (t == NULL) {
		cout << "elemento no encontrado" << endl;
	}
	else if (x < t->dato) {
		Eliminar(t->izq, x);
	}
	else if (x > t->dato) {
		Eliminar(t->der, x);
	}
	else if ((t->izq == NULL) && (t->der == NULL)) {
		aux = t;
		free(aux);
		t = NULL;
		cout << "Elemento borrado con exito\n";
	}
	else if (t->izq == NULL)
	{
		aux = t;
		free(aux);
		t = t->der;
		cout << "Elemento borrado con exito\n" << endl;
	}
	else if (t->der == NULL)
	{
		aux = t;
		t = t->izq;
		free(aux);
		cout << "Elemento borrado con exito\n" << endl;
	}
	else {

		int a = 0;
		bool activo = true;

		do {
			cout << "Con que metodo desea eliminar este nodo:\n1.Sucesor\n2.Predecesor\n ";
			cin >> a;
			switch (a)
			{
			case 1:
				//se elimina con sucesor 
				t->dato = EncontrarMenor(t->der);
				activo = false;
				break;
			case 2:
				//se e;imina con predecesor
				t->dato = EncontrarMayor(t->izq);
				activo = false;
				break;
			default:
				cout << "\nInserto una opcion invalida\n";
				activo = true;
				break;
			}
		} while (activo);

	}
}

//Guardar Arbol Archivo Binario
void guardarArbol(AVLNodo *&t) {

	ofstream archivo("ArchivoArbol_AVL.dat", ios::in | ios::app | ios::binary);

	if (!archivo) {
		cout << "Error en el archivo!" << endl;
		return;
	}

		AVLNodeFile nuevo;

		archivo.seekp(0, ios::end);

		nuevo.Hder = -1;
		nuevo.Hizq = -1;
		nuevo.valor = t->dato;
		t->posicion = pos(t);
		archivo.write(reinterpret_cast<const char *>(&nuevo), sizeof(AVLNodeFile));
		archivo.close();
	
}
int pos(AVLNodo *t) {

	int num = -1;
	AVLNodeFile nuevo;

	ifstream archivo("ArchivoArbol_AVL.dat", ios::in | ios::binary);

	if (!archivo) {
		cout << "Error en el archivo!" << endl;
		return -1;
	}

	do {

		archivo.read(reinterpret_cast<char *>(&nuevo), sizeof(AVLNodeFile));
		num++;

	} while (!archivo.eof());

	return num;

}
void mostrarArchivo() {

	AVLNodeFile leer;

	ifstream archivo("ArchivoArbol_AVL.dat", ios::in | ios::binary);
	
	if (!archivo) {
		cout << "Error en el archivo!" << endl;
	}

	do {

		archivo.read(reinterpret_cast<char *>(&leer), sizeof(AVLNodeFile));

		cout << "Valor: " << leer.valor << endl;
		cout << "Hijo Izquierdo: " << leer.Hizq << endl;
		cout << "Hijo Derecho: " << leer.Hder << endl << endl;

	} while (!archivo.eof());

}
void actualizarIndice(AVLNodo *& t) {

	if (t != NULL) {

		AVLNodeFile nuevo, guardar;

		fstream archivo("ArchivoArbol_AVL.dat", ios::in | ios::out | ios::app | ios::binary);

		if (!archivo) {
			cout << "Archivo Incorrecto!" << endl;
		}

		archivo.seekg(0);

		do {

			archivo.read(reinterpret_cast<char *>(&nuevo), sizeof(AVLNodeFile));
			if (nuevo.valor == t->dato) {

				if (t->der != NULL && t->izq != NULL) {
					guardar.Hder = t->der->posicion;
					guardar.Hizq = t->izq->posicion;
					guardar.valor = t->dato;
					archivo.seekp(t->posicion * sizeof(AVLNodeFile));
					archivo.write(reinterpret_cast<const char *>(&guardar), sizeof(AVLNodeFile));
					actualizarIndice(t->izq);
					actualizarIndice(t->der);
					archivo.close();
				}
				else if (t->der == NULL && t->izq != NULL) {
					guardar.Hder = -1;
					guardar.Hizq = t->izq->posicion;
					guardar.valor = t->dato;
					archivo.seekp(t->posicion * sizeof(AVLNodeFile));
					archivo.write(reinterpret_cast<const char *>(&guardar), sizeof(AVLNodeFile));
					actualizarIndice(t->izq);
					actualizarIndice(t->der);
					archivo.close();
				}
				else if (t->der != NULL && t->izq == NULL) {
					guardar.Hder = t->der->posicion;
					guardar.Hizq = -1;
					guardar.valor = t->dato;
					archivo.seekp(t->posicion * sizeof(AVLNodeFile));
					archivo.write(reinterpret_cast<const char *>(&guardar), sizeof(AVLNodeFile));
					actualizarIndice(t->izq);
					actualizarIndice(t->der);
					archivo.close();
				}
				else if (t->der == NULL && t->izq == NULL) {
					guardar.Hder = -1;
					guardar.Hizq = -1;
					guardar.valor = t->dato;
					archivo.seekp(t->posicion * sizeof(AVLNodeFile));
					archivo.write(reinterpret_cast<const char *>(&guardar), sizeof(AVLNodeFile));
					actualizarIndice(t->izq);
					actualizarIndice(t->der);
					archivo.close();
				}
			}
		} while (!archivo.eof());
	}
}
