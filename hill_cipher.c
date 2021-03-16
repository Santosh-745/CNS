// Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

int dtn(int *a)
{
    int d = 0;
    int x[3] = {1,0,0};
    int y[3] = {2,2,1};
    int i;
    for(i=0;i<3;i++){
        
        printf("\n %d %d %d",*(a + i), *(a+ 3*1 + x[i]) * *(a+ 3*2 + y[i]),*(a+ 3*1 + y[i]) * *(a+ 3*2 + x[i]));
        if(i == 1)
            d = d - 
                    (*(a + i) * 
                    (
                     *(a+ 3*1 + x[i]) * *(a+ 3*2 + y[i]) - 
                     *(a+ 3*1 + y[i]) * *(a+ 3*2 + x[i])
                    )
                    );
        else
            d = d + 
                    (*(a + i) * 
                    (
                     *(a+ 3*1 + x[i]) * *(a+ 3*2 + y[i]) - 
                     *(a+ 3*1 + y[i]) * *(a+ 3*2 + x[i])
                    )
                    );
        printf("\n values %d",d);
    }
    return d;
    
}

int extuq(int a,int b){
int q,a1,a2,a3,b1,b2,b3,t1,t2,t3;
a1 = 1;
a2 = 0;
a3 = a;
b1 = 0;
b2 = 1;
b3 = b;
while(1){
if(b3 == 0){
return 0;
break;
}
if(b3 == 1){
while(b2 < 0)
b2 = b2 + a;
return b2;
break;
}
q = a3/b3;
t1 = a1 - b1*q;
t2 = a2 - b2*q;
t3 = a3 - b3*q;
a1 = b1;
a2 = b2;
a3 = b3;
b2 = t1; 
b2 = t2; 
b3 = t3;
} }

int main() {
    int p,i,j,l,d,dtn_inv;
    char key[] = "gybnqkurp";
    int k_int[3][3];
    char plain[50];
    printf("\n==>  Enter the Plain text ==> ");
    scanf("%s",&plain);
    l = strlen(plain);
    int p_int[3];
    char cip[l] ;
    int c_int[3];
    do{
        printf("\n==>  Enter Key text ==> ");
        scanf("%s",&key);
        // printf("%s",key);
        for(i=0;i<3;i++){
            printf("\n");
            for(j=0;j<3;j++){
                k_int[i][j] = key[i*3 + j] - 'a';
                // printf(" %d ",k_int[i][j]);
            }
        }
        d = dnt(&k_int[0][0]);
        dtn_inv = extuq(26,d);
        printf("\n==> Determinant  %d Determinant inverse  %d",d,dtn_inv);
    }while(d == 0 || (d != 1 && dtn_inv == 0));
    //  || (d != 1 && dtn_inv == 0)
    // printf("\n test %d %d",d,dtn_inv);
    // Encryption
    
    // printf("\n test lenth %d",l);
    for(p = 0; p < l; p+=3){
        for(i = 0; i < 3; i++){
            c_int[i] = 0;
            // printf("\n");
            for(j = 0; j < 3; j++){
                p_int[j] = (plain[p+j] - 'a');
                // printf("\t test p_int %d",p_int[j]);
                c_int[i] = c_int[i] + (k_int[i][j] * p_int[j]) ;
            }
            c_int[i] = c_int[i] % 26; 
            cip[p+i] = c_int[i] + 'a' ; 
        }
    }
    printf("\n==>  CIPHER TEXT ==>  ");
    for(i = 0; i < l; i++)
        printf("%c",cip[i]);  
    
    // Decryption
    int dk_int[3][3];
    int de_int[3];
    char de[l];
    int temp;
    int adj[3][3];
    adj[0][0] = k_int[1][1]*k_int[2][2] - k_int[1][2]*k_int[2][1];
    adj[0][1] = k_int[2][1]*k_int[0][2] - k_int[0][1]*k_int[2][2];
    adj[0][2] = k_int[0][1]*k_int[1][2] - k_int[0][2]*k_int[1][1];
    adj[1][0] = k_int[1][2]*k_int[2][0] - k_int[2][2]*k_int[1][0];
    adj[1][1] = k_int[2][2]*k_int[0][0] - k_int[0][2]*k_int[2][0];
    adj[1][2] = k_int[0][2]*k_int[1][0] - k_int[1][2]*k_int[0][0];
    adj[2][0] = k_int[1][0]*k_int[2][1] - k_int[2][0]*k_int[1][1];
    adj[2][1] = k_int[2][0]*k_int[0][1] - k_int[2][1]*k_int[0][0];
    adj[2][2] = k_int[0][0]*k_int[1][1] - k_int[1][0]*k_int[0][1];
    for(i=0;i<3;i++){
        // printf("\n  test adj");
        // printf("\n");
        for(j=0;j<3;j++){
            if(adj[i][j] < 0){
                // printf(" %d ",adj[i][j]);
                temp = ((-1)*adj[i][j] ) / 26;
                temp++;
                // printf("\n test %d %d %d",temp,temp-1,adj[i][j]);
                adj[i][j] = (temp * 26) + adj[i][j]; 
            }
            dk_int[i][j] = (dtn_inv * adj[i][j]) % 26;
            // printf(" %d ",dk_int[i][j]);
        }
    }
    // printf("\n");
    // for(i = 0; i < l; i++)
    //     printf("%c",cip[i]); 
    for(p = 0; p < l; p+=3){
        for(i = 0; i < 3; i++){
            de_int[i] = 0;
            // printf("\n");
            for(j = 0; j < 3; j++){
                // printf("\t test p j %d %d",p,j);
                // printf("\t test cip %c",cip[p+j]);
                c_int[j] = (cip[p+j] - 'a');
                // printf("\t test c_int %d",c_int[j]);
                de_int[i] = de_int[i] + (dk_int[i][j] * c_int[j]) ;
            }
            de_int[i] = de_int[i] % 26; 
            de[p+i] = de_int[i] + 'a' ; 
        }
    }
    printf("\n==>  DECRYPTED TEXT  ==>  ");
    for(i = 0; i < l; i++)
        printf("%c",de[i]);
}
