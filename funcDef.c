// #include<stdint.h>
int globalvar=0;
long calcSum(int32_t n){
    if (n <= 1) return 1;
    return n*calcSum(n-1);  
}

void nineMultiply(){
    for (int i=1;i<=9;i++){
        for (int j=1;j<=i;j++){
            printf("%d x %d = %-3d ", j,i,i*j);
        }
        printf("\n");
    }
}   

