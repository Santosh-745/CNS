#include <stdio.h>
#include <math.h>
char plain[30] = "123456ABCD132536";
char key[16] = "AABB09182736CCDD";
char keys[16][16];
//char plain[30] = "ABCD";
int bin[100];
char dec[30];
int temp[64];
int ip[64] = {58, 50, 42, 34, 26, 18, 10, 2,
			  60, 52, 44, 36, 28, 20, 12, 4,
			  62, 54, 46, 38, 30, 22, 14, 6, 64, 56,
			  48, 40, 32, 24, 16, 8, 57, 49,
			  41, 33, 25, 17, 9, 1, 59, 51,
			  43, 35, 27, 19, 11, 3, 61, 53,
			  45, 37, 29, 21, 13, 5, 63, 55,
			  47, 39, 31, 23, 15, 7};
int kp1[64] = {57, 49, 41, 33, 25,
			   17, 9, 1, 58, 50, 42, 34, 26,
			   18, 10, 2, 59, 51, 43, 35, 27,
			   19, 11, 3, 60, 52, 44, 36, 63,
			   55, 47, 39, 31, 23, 15, 7, 62,
			   54, 46, 38, 30, 22, 14, 6, 61,
			   53, 45, 37, 29, 21, 13, 5, 28,
			   20, 12, 4};
int kp2[64] = {14, 17, 11, 24, 1, 5, 3,
			   28, 15, 6, 21, 10, 23, 19, 12,
			   4, 26, 8, 16, 7, 27, 20, 13, 2,
			   41, 52, 31, 37, 47, 55, 30, 40,
			   51, 45, 33, 48, 44, 49, 39, 56,
			   34, 53, 46, 42, 50, 36, 29, 32};
void perm(int pt[64])
{
	int i, j;
	for (i = 0; i < 64; i++)
	{
		temp[i] = bin[pt[i] - 1];
	}
	for (i = 0; i < 64; i++)
	{
		bin[i] = temp[i];
	}
}
void bin2hex(char a[])
{
	int i, n, j;
	int temp;
	double k;
	for (i = 0; i < 16; i++)
	{
		temp = 0;
		k = 3;
		for (j = i * 4; j <= (i * 4) + 3; j++)
		{
			if (bin[j] == 1)
				temp = temp + pow(2.0, k);
			k--;
		}
		//printf("temp %d ",temp);
		if (temp < 10)
			a[i] = temp + 48;
		else
			a[i] = temp + 55;
		//printf("%c",a[i]);
	}
}
void hex2bin(char a[])
{
	int i, n, j;
	for (i = 0; i < 16; i++)
	{
		if (a[i] < 65)
			n = a[i] - 48;
		else if (a[i] >= 65)
			n = a[i] - 55;
		//printf("%d ",n);
		for (j = (i * 4) + 3; j >= i * 4; j--)
		{
			bin[j] = n % 2;
			//printf("%d ",bin[j]);
			n = n / 2;
		}
		//printf("\n");
	}
	// for(i = 0;i < 64;i++)
	// {
	// 	if(i%4 == 0)
	// 	    printf("\n");
	// 	printf("%d ",bin[i]);
	// }
}
void left_cir_shift(int x)
{
	int t1, t2, i;
	if (x == 0 || x == 1 || x == 8 || x == 15)
	{
		t1 = bin[0];
		for (i = 1; i < 27; i++)
		{
			bin[i - 1] = bin[i];
		}
		bin[27] = t1;
		t1 = bin[28];
		for (i = 29; i < 55; i++)
		{
			bin[i - 1] = bin[i];
		}
		bin[55] = t1;
	}
	else
	{
		t1 = bin[0];
		t2 = bin[1];
		for (i = 2; i < 27; i++)
		{
			bin[i - 2] = bin[i];
		}
		bin[26] = t1;
		bin[27] = t2;
		t1 = bin[28];
		t2 = bin[29];
		for (i = 30; i < 55; i++)
		{
			bin[i - 2] = bin[i];
		}
		bin[54] = t1;
		bin[55] = t2;
	}
}
void key_generation()
{
	int i, j, n;
	hex2bin(key);
	// for(i = 0;i < 64;i++)
	// {
	// 	if(i%4 == 0)
	// 	    printf("\n");
	// 	printf(" %d=%d ",i+1,bin[i]);
	// }
	perm(kp1);
	bin2hex(key);
	// printf("\n");
	// for(i=0;i<16;i++)
	//     printf("%c",key[i]);
	for (i = 0; i < 16; i++)
	{
		hex2bin(key);
		left_cir_shift(i);
		bin2hex(key);
		perm(kp2);
		bin2hex(keys[i]);
	}
	printf("\n");
	for(i=0;i<16;i++)
	{
		for(j=0;j<16;j++)
		{
			printf("%c",keys[i][j]);
		}
		printf("\n");
	}
}
void initial_permutation()
{
	int i, n, j;
	hex2bin(plain);
	printf("\n");
	// for(i=0;i<16;i++)
	// 	printf("%c",plain[i]);
	/*for(i=0;i<64;i++)
	{
		if(i%4 == 0)
			printf("\n");
		printf(" %d=%d ",i+1,bin[i]);
	}*/
	perm(ip);
	// for(i=0;i<64;i++)
	// {
	// 	if(i%4 == 0)
	// 		printf("\n");
	// 	printf(" %d=%d ",i+1,bin[i]);
	// }
	bin2hex(plain);
	// printf("\n After Intial Permutation ");
	// for(j=0;j<16;j++)
	// 	printf("%c",plain[j]);
}
void encrypt()
{
	key_generation();
	//printf("%d",plain[0]);
	initial_permutation();
}
int main()
{
	encrypt();
}
