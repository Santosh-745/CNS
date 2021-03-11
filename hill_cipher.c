// Online C compiler to run C program online
#include <stdio.h>
#include<string.h>

int dnt(int *a)
{
    int d ;
    d = *(a + 3*0 + 0) * 
        ( (*(a + 3*1 + 1) * *(a + 3*2 + 2)) - (*(a + 3*1 + 2) * *(a + 3*2 + 1)) )-
        *(a + 3*0 + 1) * 
        ( (*(a + 3*1 + 0) * *(a + 3*2 + 2)) - (*(a + 3*1 + 2) * *(a + 3*2 + 0)) )+
        *(a + 3*0 + 2) * 
        ( (*(a + 3*1 + 0) * *(a + 3*2 + 1)) - (*(a + 3*2 + 0) * *(a + 3*1 + 1)) );
    // printf(" \n %d ", *(a + 3*2 + 2));
    return d;
}

int main() {
    int p,i,j,l;
    char key[9] = "gybnqkurp";
    int k_int[3][3];
    char plain[3] = "act";
    int p_int[3];
    char cip[3] ;
    int c_int[3];
    do{
        // printf("\n ==>  Enter Key text ==> ");
        // scanf("%s",&key);
        // printf("%s",key);
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                k_int[i][j] = key[i*3 + j] - 'a';
                // printf("\t%d",k_int[i][j]);
            }
        }
    }while(dnt(&k_int) == 0);
    // printf("%d",dnt(&k_int));
    l = strlen(plain);
    
    for(p = 0; p < l; p+=3){
        for(i = 0; i < 3; i++){
            c_int[i] = 0;
            // printf("\n");
            for(j = 0; j < 3; j++){
                p_int[j] = (plain[p+j] - 'a');
                // printf("\t test p_int %d",p_int[j]);
                c_int[i] = c_int[i] + (k_int[i][j] * p_int[j]) ;
            }    
        }
    }
    for(i = 0; i < 3; i++)
        printf("\t%d",c_int[i]);        
}
