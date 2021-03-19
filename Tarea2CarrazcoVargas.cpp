//Nicolas Carrazco & Victor Vargas
//El siguiente codigo genera un array de 100000 elementos distintos y realiza
//dos recorridos para calcular la potencia de cada elemento; uno con un solo hilo
//y otro con cuatro hilos.

#include <pthread.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <stdio.h>

using namespace std;
using namespace std::chrono;

void solo_hilo() { //hace un recorrido de 0 a 100000 elevando al cuadrado cada elemento
	vector<int> potencia;
	int exponente = 2;
	int op;
	for (int i = 0; i < 100000; i++)
	{
		op = pow(i, exponente);
		potencia.push_back(op);
	}
}
void* hilo1(void*) { //hace un recorrido de 0 a 25000 elevando al cuadrado cada elemento
	vector<int> potencia1;
	int exponente1 = 2;
	int op1;
	for (int i = 0; i <= 25000; i++)
	{
		op1 = pow(i, exponente1);
		potencia1.push_back(op1);
	}
	return NULL;
}
void* hilo2(void*) { //hace un recorrido de 25001 a 50000 elevando al cuadrado cada elemento
	vector<int> potencia2;
	int exponente2 = 2;
	int op2;
	for (int i = 25001; i <= 50000; i++)
	{
		op2 = pow(i, exponente2);
		potencia2.push_back(op2);
	}
	return NULL;
}
void* hilo3(void*) { //hace un recorrido de 50001 a 75000 elevando al cuadrado cada elemento
	vector<int> potencia3;
	int exponente3 = 2;
	int op3;
	for (int i = 50001; i <= 75000; i++)
	{
		op3 = pow(i, exponente3);
		potencia3.push_back(op3);
	}
	return NULL;
}
void* hilo4(void*) { //hace un recorrido de 75001 a 100000 elevando al cuadrado cada elemento
	vector<int> potencia4;
	int exponente4 = 2;
	int op4;
	for (int i = 75001; i < 100000; i++)
	{
		op4 = pow(i, exponente4);
		potencia4.push_back(op4);
	}
	return NULL;
}


void multi_hilo() { //va a generar 4 hilos que recorran las funciones hilo1,2,3 y 4 simultaneamente
	pthread_t thread1, thread2, thread3, thread4; //variables de tipo pthread_t que almacenan el identificador de cada hilo
	pthread_create(&thread1, NULL, hilo1, NULL); //da el llamada a ejecutar la funcion hilo1
	pthread_create(&thread2, NULL, hilo2, NULL); //da el llamada a ejecutar la funcion hilo2
	pthread_create(&thread3, NULL, hilo3, NULL); //da el llamada a ejecutar la funcion hilo3
	pthread_create(&thread4, NULL, hilo4, NULL); //da el llamada a ejecutar la funcion hilo4
	pthread_join(thread1, NULL); //avanza a la siguiente linea de codigo hasta que el hilo que ejecuta la funcion hilo1() finalice
	pthread_join(thread2, NULL); //avanza a la siguiente linea de codigo hasta que el hilo que ejecuta la funcion hilo2() finalice
	pthread_join(thread3, NULL); //avanza a la siguiente linea de codigo hasta que el hilo que ejecuta la funcion hilo3() finalice
	pthread_join(thread4, NULL); //avanza a la siguiente linea de codigo hasta que el hilo que ejecuta la funcion hilo4() finalice
}

int main()
{
	auto start = high_resolution_clock::now();
	solo_hilo();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "EL tiempo transcurrido para el recorrido con un hilo fue de: " << duration.count() << " microsegundos." << endl;

	auto start2 = high_resolution_clock::now();
	multi_hilo();
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	cout << "EL tiempo transcurrido para el recorrido con cuatro hilos fue de: " << duration2.count() << " microsegundos." << endl;
	return 0;
}