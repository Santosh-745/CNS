 //Online C compiler to run C program online
#include <stdio.h>
#include <string.h>

int main() {
    int l,k,d=4,ud,i,j,t;
    char a[30][30] = {0};
    char b[30][30] = {0};
    char plain[] = "thisisrailfence";
    char cip[50];
    char en[50];
    l = strlen(plain);
    // printf("%d",l );
    k = 0;
    ud = 0;
    i = 0;
    while(k<l){
        if(ud == 0){
            a[i][k] = plain[k]; 
            i++;
            k++;
            if(i==d){    
                ud = 1;
                i -= 2;
            }
        }
        else {
            a[i][k] = plain[k]; 
            i--;
            k++;
            if(i == -1){
                ud = 0;
                i+=2;
            }
        }
    }
    // for(i=0;i<5;i++)
    //     printf("%c %d",a[0][i],a[0][i]);
    k = 0;
    for(i=0;i<d;i++){
        printf("\n");
        for(j=0;j<l;j++){
            printf(" %c ",a[i][j]);
            if(a[i][j] != 0)
                cip[k++] = a[i][j];
        }
    }
    printf("\n");
    for(i=0;i<l;i++)
        printf(" %c ",cip[i]);
    printf("\n");
    int start,h,temp,temp1;
    start = 0;
    h = 1;
    k = 0;
    i = 0;
    j = 0;
    d = 4;
    t = d;
    // printf("%d %d",t,l);
    while(i < t && k < l)
    {
        // printf("\ntest i %d",i);
        b[i][start] = cip[k++];
        j = start;
        temp = 2 * (d - 1);
        temp1 = 2 * (h - 1);
        while((j + temp) < l && k < l)
        {
            if(i == 0 || i == t-1)
            {
                j = j + ( 2 * (t-1) );
                b[i][j] = cip[k++];
            }
            else 
            {   /*if(i > 0 && i < t-1)*/
                j = j + ( temp );
                b[i][j] = cip[k++];
                if((j + temp1) < l){
                    j = j + (temp1);
                    b[i][j] = cip[k++];
                }
            }
        }
        d--;
        h++;
        i++;
        start++;
    }
    for(i=0;i<t;i++){
        printf("\n");
        for(j=0;j<l;j++){
            printf(" %c ",b[i][j]);
        }
    }
    printf("\n");
    k = 0;
    ud = 0;
    i = 0;
    while(k<l)
    {
        printf("\ntest k %d",k);
        printf("  %c  ",b[i][k]);
        if(ud == 0){
            en[k] = b[i][k]; 
            i++;
            k++;
            if(i==t){    
                ud = 1;
                i -= 2;
            }
        }
        else {
            en[k] = b[i][k]; 
            i--;
            k++;
            if(i == -1){
                ud = 0;
                i+=2;
            }
        }
        // printf("  %c  ",en[k-1]);
    }
    // printf("\n test %d",l);
    for(i=0;i<l;i++)
        printf(" %c ",en[i]);
    printf("\n");
}
