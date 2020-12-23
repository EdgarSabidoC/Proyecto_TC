#include<stdio.h>

int decimalConvOctal(int num_decimal)
{
	int num_octal;
	int cont_valor;
	int resto;
	
	cont_valor = 1;
	
	while (num_decimal != 0)
	{
		resto = num_decimal % 8;
		num_octal += resto * cont_valor;
		cont_valor = cont_valor * 10;
		num_decimal /= 8;
	}
	
	printf("%d", num_octal);
	
	return num_octal;
}

int main()
{
	int n = 9;
	
	decimalConvOctal(n);
	
	return 0;
}
