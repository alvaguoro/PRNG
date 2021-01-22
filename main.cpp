#include <iostream>
#include <bitset>
#include <time.h>

unsigned int s0; unsigned int s1; unsigned  int s2; unsigned int s3; unsigned int s4; unsigned int s5; unsigned int s6; unsigned int s7;
unsigned int s8; unsigned int s9; unsigned int s10; unsigned int s11; unsigned int s12; unsigned int s13; unsigned int s14; unsigned int s15; unsigned int s16;

unsigned  int x0; unsigned int x1; unsigned int x2; unsigned int x3;

unsigned int r1; unsigned int r2;

 int f1; int f2;

 int d; int d1; int d2; int z;


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

void init() 
{
	s0 = 0xf8b92f67; s1 = 0x6e3a53b5; s2 = 0x48ad2eed; s3 = 0x956f5e42; s4 = 0xf9e9b01a; s5 = 0x962d97c0; s6 = 0x724cff09; s7 = 0x932f2f93;
	s8 = 0xb8147c3e; s9 = 0x0ada63aa; s10 = 0xc847a5e8; s11 = 0x3cbd4881; s12 = 0xf8d16c50; s13 = 0xda3dc12c;s14 = 0x1d3994e1;s15 = 0xfbb5db2a;

	r1 = 0x1340c615;
	r2 = 0xb4252095;

	FuncionF(-0.2306260232230942, 0.42841027518257125);
}

void BR()
{
	unsigned int auxx1, auxx2;
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
	if (modo)
	{
		s16 = ((s15 & 0x2000) | (s13 & 0x80000) | (s10 & 0x20000) | (s6 & 0x100000) | (s0 & 0x101)) | d >> 1;
		if (!s16)
			s16 = 0x7FFFFFFF;
	}
	else 
	{
		s16 = (s15 & 0x2000) | (s13 & 0x80000) | (s10 & 0x20000) | (s6 & 0x100000) | (s0 & 0x101);
		if (!s16)
			s16 = 0x7FFFFFFF;
	}

	s0 = s1; s1 = s2; s2 = s3; s3 = s4; s4 = s5; s5 = s6; s6 = s7;s7 = s8;
	s8 = s9;s9 = s10;s10 = s11;s11 = s12;s12 = s13;s13 = s14;s14 = s15;s15 = s16;
}

int main(int argc, char* argv[])
{
	init();
	for (int i = 0; i < 32; i++) {
		BR();
		LFSR(1);
		FuncionF(0, 0);
	}
		
	for (int i = 0; i < 10000; i++) {
		BR();
		LFSR(1);
		FuncionF(0, 0);
		if(i > 99)
			std::cout << std::bitset< 32 >(z) << ' ' << '\n';
	}
}