#include <stdio.h>
#include <math.h>
#include <string.h>
char plain[30] = "0123456789ABCDEF";
char key[16] = "AABB09182736CCDD";
char keys[16][16]; // table for all 16 keys
//char plain[30] = "ABCD";
int bin[100]; 
int temp[64];

//Initial Permutaion
int ip[64] = {58, 50, 42, 34, 26, 18, 10, 2,
			  60, 52, 44, 36, 28, 20, 12, 4,
			  62, 54, 46, 38, 30, 22, 14, 6, 64, 56,
			  48, 40, 32, 24, 16, 8, 57, 49,
			  41, 33, 25, 17, 9, 1, 59, 51,
			  43, 35, 27, 19, 11, 3, 61, 53,
			  45, 37, 29, 21, 13, 5, 63, 55,
			  47, 39, 31, 23, 15, 7};

// Inverse Initial Permutation Table
int ip1[64] = {40, 8, 48, 16, 56, 24, 64,
			 32, 39, 7, 47, 15, 55,
			 23, 63, 31, 38, 6, 46,
			 14, 54, 22, 62, 30, 37,
			 5, 45, 13, 53, 21, 61,
			 29, 36, 4, 44, 12, 52,
			 20, 60, 28, 35, 3, 43,
			 11, 51, 19, 59, 27, 34,
			 2, 42, 10, 50, 18, 58,
			 26, 33, 1, 41, 9, 49,
			 17, 57, 25};

// 64 bit key to 56 bit key + permutation
int kp1[64] = {57, 49, 41, 33, 25,
			   17, 9, 1, 58, 50, 42, 34, 26,
			   18, 10, 2, 59, 51, 43, 35, 27,
			   19, 11, 3, 60, 52, 44, 36, 63,
			   55, 47, 39, 31, 23, 15, 7, 62,
			   54, 46, 38, 30, 22, 14, 6, 61,
			   53, 45, 37, 29, 21, 13, 5, 28,
			   20, 12, 4};

// 56 bit key to 48 bit key + permutation
int kp2[64] = {14, 17, 11, 24, 1, 5, 3,
			   28, 15, 6, 21, 10, 23, 19, 12,
			   4, 26, 8, 16, 7, 27, 20, 13, 2,
			   41, 52, 31, 37, 47, 55, 30, 40,
			   51, 45, 33, 48, 44, 49, 39, 56,
			   34, 53, 46, 42, 50, 36, 29, 32};
// Expansion D-box Table
int ep[48] = {32, 1, 2, 3, 4, 5, 4,
			  5, 6, 7, 8, 9, 8, 9, 10,
			  11, 12, 13, 12, 13, 14, 15,
			  16, 17, 16, 17, 18, 19, 20,
			  21, 20, 21, 22, 23, 24, 25,
			  24, 25, 26, 27, 28, 29, 28,
			  29, 30, 31, 32, 1};

// P - box Permutation
int p[32] = {16, 7, 20, 21, 29, 12, 28,
			 17, 1, 15, 23, 26, 5, 18,
			 31, 10, 2, 8, 24, 14, 32,
			 27, 3, 9, 19, 13, 30, 6,
			 22, 11, 4, 25};

// S-box Table
int sbox[8][4][16] = {
	{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
	 {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
	 {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
	 {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
	{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	 {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	 {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
	{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
	 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
	 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
	 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
	{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
	 {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
	 {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
	 {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
	{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
	 {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
	 {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
	 {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
	{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
	 {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
	 {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
	 {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
	{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
	 {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
	 {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
	 {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
	{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
	 {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
	 {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
	 {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

// Common Function for permutation
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

// Function to convert bin to hex to get a values after permutation
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

// Function to convert hex to bin before any permutation
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

// left circular shift in key generation
void left_cir_shift(int x)
{
	int t1, t2, i;
	if (x == 0 || x == 1 || x == 8 || x == 15)
	{
		t1 = bin[0];
		for (i = 1; i < 28; i++)
		{
			bin[i - 1] = bin[i];
		}
		bin[27] = t1;
		t1 = bin[28];
		for (i = 29; i < 56; i++)
		{
			bin[i - 1] = bin[i];
		}
		bin[55] = t1;
	}
	else
	{
		t1 = bin[0];
		t2 = bin[1];
		for (i = 2; i < 28; i++)
		{
			bin[i - 2] = bin[i];
		}
		bin[26] = t1;
		bin[27] = t2;
		t1 = bin[28];
		t2 = bin[29];
		for (i = 30; i < 56; i++)
		{
			bin[i - 2] = bin[i];
		}
		bin[54] = t1;
		bin[55] = t2;
	}
}

// XOR function
void xor (char a[], int b[]) {
	// here the b[] is already in bin 
	int i;
	hex2bin(a);
	for (i = 0; i < 48; i++)
	{
		// printf("\ni=%d a=%d b=%d ",i,bin[i],b[i]);
		bin[i] = b[i] ^ bin[i];
		// printf(" ans=%d",bin[i]);
	}
}
void s_box()
{
	int i, j, n, r, c;
	char s_value[8];
	for (i = 0; i < 48; i += 6)
	{
		n = i / 6;  
		r = 2 * bin[i] + bin[i + 5];
		c = 8 * bin[i + 1] + 4 * bin[i + 2] + 2 * bin[i + 3] + bin[i + 4];
		if (sbox[n][r][c] > 9)
		{
			s_value[n] = (char)(sbox[n][r][c] + 55);
		}
		else
		{
			s_value[n] = (char)(sbox[n][r][c] + 48);
		}
		// printf("%c",s_value[n]);
	}
	hex2bin(s_value);
}

// function to process between rpart and key and swapping in every round 
void rd(int x, char k[])
{
	int i, j;
	char t;
	char left[8];
	char right[8];
	char t_right[8];
	int t_exp[48];
	int right_int[32];
	/*for(i = 0; i < 12;i++)
	{
		printf("%c",k[i]);
	}
	printf("\n");*/
	for (i = 0; i < 8; i++)
	{
		left[i] = plain[i];
		right[i] = plain[i + 8];
		t_right[i] = right[i];
	}
	/*for(i=0;i<8;i++)
	printf("%c",right[i]);*/
	hex2bin(t_right);
	perm(ep);
	for (i = 0; i < 48; i++)
	{
		t_exp[i] = bin[i];
	}
	xor(k, t_exp);
	s_box();
	/*for(i = 0;i < 32;i++)
	{
		if(i%4 == 0)
		    printf("\n");
		printf(" %d=%d ",i+1,bin[i]);
	}*/
	perm(p);
	/*for(i = 0;i < 32;i++)
	{
		if(i%4 == 0)
		    printf("\n");
		printf(" %d=%d ",i+1,bin[i]);
	}*/
	for (i = 0; i < 32; i++)
	{
		right_int[i] = bin[i];
	}
	xor(left, right_int);
	bin2hex(left);
	for (i = 0; i < 8; i++)
	{
		// printf("%c ",right[i]);
		plain[i] = right[i];
		plain[i + 8] = left[i];
	}
}

// Key Expansion 
void key_generation()
{
	int i, j, n;
	hex2bin(key);
	/*for(i = 0;i < 64;i++)
	{
		if(i%4 == 0)
		    printf("\n");
		printf(" %d=%d ",i+1,bin[i]);
	}*/
	perm(kp1);
	/*for(i = 0;i < 64;i++)
	{
		if(i%4 == 0)
		    printf("\n");
		printf(" %d=%d ",i+1,bin[i]);
	}*/
	bin2hex(key);
	// printf("\n");
	// for(i=0;i<14;i++)
	//     printf("%c",key[i]);
	for (i = 0; i < 16; i++)
	{
		hex2bin(key);
		left_cir_shift(i);
		bin2hex(key);
		perm(kp2);
		bin2hex(keys[i]);
		/*printf("\n");
		for (j = 0; j < 12; j++)
		{
			printf("%c", keys[i][j]);
		}*/
	}
}

// Function to performe initial permutation
void initial_permutation()
{
	int i, n, j;
	hex2bin(plain);
	printf("\n");
	/*for(i=0;i<64;i++)
	{
		if(i%4 == 0)
			printf("\n");
		printf(" %d=%d ",i+1,bin[i]);
	}*/
	perm(ip);
	bin2hex(plain);
	printf("\n After Intial Permutation ==> ");
	for (j = 0; j < 16; j++)
	{
		if (j == 8)
			printf("\t");
		printf(" %c", plain[j]);
	}
}

// Function for Encryption
void encrypt()
{
	int i, j, k, t;
	key_generation();
	//printf("%d",plain[0]);
	initial_permutation();
	for (i = 0; i < 16; i++)
	{
		rd(i, keys[i]);
		if (i == 15)
		{
			for (k = 0; k < 8; k++)
			{
				t = plain[k];
				plain[k] = plain[k + 8];
				plain[k + 8] = t;
			}
		}
		printf("\n After Round %d ==> ", i + 1);
		for (j = 0; j < 16; j++)
		{
			if (j == 8)
				printf("\t");
			printf(" %c", plain[j]);
		}
	}
	hex2bin(plain);
	perm(ip1);
	bin2hex(plain);
}

// Function for decryption
void decrypt()
{
	int i, j, k, t;
	initial_permutation();
	for (i = 15; i > -1; i--)
	{
		rd(15-i, keys[i]);
		if (i == 0)
		{
			// Last Round Swapper
			for (k = 0; k < 8; k++)
			{
				t = plain[k];
				plain[k] = plain[k + 8];
				plain[k + 8] = t;
			}
		}
		printf("\n After Round %d ==> ", 15 - i);
		for (j = 0; j < 16; j++)
		{
			if (j == 8)
				printf("\t");
			printf(" %c", plain[j]);
		}
	}
	hex2bin(plain);
	perm(ip1);
	bin2hex(plain);
}


int main()
{
	int i;
	printf("\n\n ==> Plain Text ==> ");
	for (i = 0; i < 16; i++)
	{
		printf(" %c", plain[i]);
	}
	encrypt();
	printf("\n\n ==> Cipher Text ==> ");
	for (i = 0; i < 16; i++)
	{
		printf(" %c", plain[i]);
	}
	decrypt();
	printf("\n\n ==> Decrypted Text ==> ");
	for (i = 0; i < 16; i++)
	{
		printf(" %c", plain[i]);
	}
	printf("\n\n");
}
