#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
int T;
int main(){
    scanf("%d", &T);
    while (T--){
        int n, k;
        scanf("%d%d", &n ,&k);
        int min_divisor = n ;
        for (int i=2;i * i<= n;i++){
            if (n % i==0){
                min_divisor = i;
                break;
            }
        }
        if (min_divisor == 2){
            printf("%d\n", n + 2*k);
        }else{
            printf("%d\n", n+ min_divisor + 2*k-2);
        }
    }
    return 0;
}