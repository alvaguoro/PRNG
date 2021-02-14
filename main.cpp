#include <iostream>
#include <bitset>
#include <ctime>
#include <string>  
#include <sstream>
#include <fstream>

unsigned long s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16;

unsigned long x0, x1, x2, x3;

unsigned long r1, r2;

unsigned long f1, f2;

long d, d1, d2, z;


double x_aux = 0.0;
double y_aux = 0.0;
double aux1;
double aux2;

void FuncionF(double x, double y)
{
	d = (x0 ^ r1) | r2;
	d1 = r1 | x1;
	d2 = r2 ^ x2;

	if (!x && !y) {
		x_aux = 2.0 * x_aux * x_aux - 1.0;
		y_aux = 4.0 * y_aux * y_aux * y_aux - 3.0 * y_aux;
		aux1 = x_aux * 100000000.0;
		aux2 = y_aux * 100000000.0;
		f1 = abs(aux1);
		f2 = abs(aux2);
	}
	else 
	{
		x_aux = 2 * x * x - 1;
		y_aux = 4 * y * y * y - 3 * y;
		aux1 = x_aux * 100000000.0;
		aux2 = y_aux * 100000000.0;
		f1 = abs(aux1);
		f2 = abs(aux2);
	}

	r1 = d1 ^ f1;
	r2 = d2 ^ f2;

	z = d ^ x3;
}

void init() //Inicializamos todos los registros iniciales
{
	srand(time(NULL));
	s0 = rand(); s1 = rand(); s2 = rand(); s3 = rand(); s4 = rand(); s5 = rand(); s6 = rand(); s7 = rand();
	s8 = rand(); s9 = rand(); s10 = rand(); s11 = rand(); s12 = rand(); s13 = rand();s14 = rand();s15 = rand();

	r1 = rand();
	r2 = rand();

	double faux1 = rand()/pow(2, 32);
	double faux2 = rand()/pow(2, 32);

	FuncionF(faux1 > 0.5 ? faux1: -faux1, faux2 < 0.5 ? faux2 : -faux2);
}

void BR() //Reorganizacion de bits
{
	unsigned long auxx1, auxx2;
	auxx1 = s15 & 0xffff0000; auxx2 = s14 & 0x0000ffff;
	x0 = auxx1 | auxx2;
	auxx1 = s9 & 0xffff0000; auxx2 = s11 & 0x0000ffff;
	x1 = auxx1 | auxx2;
	auxx1 = s7 & 0xffff0000; auxx2 = s5 & 0x0000ffff;
	x2 = auxx1 | auxx2;
	auxx1 = s0 & 0xffff0000; auxx2 = s2 & 0x0000ffff;
	x3 = auxx1 | auxx2;
}

void LFSR(int modo)
{
	if (modo) //Modo inicializacion
	{
		s16 = ((s15 * 8192) + (s13 * 524288) + (s10 * 131072) + (s6 * 1048576) + (s0 * 257)) + d >> 1;
		if (!s16)
			s16 = 0xffffffff;
	}
	else //Modo trabajo
	{
		s16 = (s15 * 8192) + (s13 * 524288) + (s10 * 131072) + (s6 * 1048576) + (s0 * 257);
		if (!s16)
			s16 = 0xffffffff;
	}

	s0 = s1; s1 = s2; s2 = s3; s3 = s4; s4 = s5; s5 = s6; s6 = s7;s7 = s8;
	s8 = s9;s9 = s10;s10 = s11;s11 = s12;s12 = s13;s13 = s14;s14 = s15;s15 = s16;
}

size_t popcount(size_t n) {
	std::bitset<sizeof(size_t)* CHAR_BIT> b(n);
	return b.count();
}

int main(int argc, char* argv[])
{
	int avg_0 = 0;
	int avg_1 = 0;
	int auxAvg = 0;
	int numIter;

	printf("Introduce la cantidad de numeros que quieras generar:\n");
	scanf_s("%d", &numIter);

	std::ofstream archivo("prng.txt");

	init();
	for (int i = 0; i < 32; i++) {
		BR();
		LFSR(1);
		FuncionF(0, 0);
	}
		
	for (int i = 0; i < numIter + 100; i++) {
		BR();
		LFSR(0);
		FuncionF(0, 0);
		if (i > 99) {
			archivo << std::bitset< 32 >(z) << ' ' << '\n';
			auxAvg = popcount(z);
			avg_1 = avg_1 + auxAvg;
			avg_0 = avg_0 + 32 - auxAvg;
		}	
	}

	archivo << "Total 0s: " << avg_0 << " Total 1s: " << avg_1 << '\n';

	archivo.close();

	printf("\nPulse una tecla para finalizar");
	getchar();
}