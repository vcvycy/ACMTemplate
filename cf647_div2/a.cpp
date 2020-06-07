#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;
int T;
int main(){
    scanf("%d", &T);
    while (T--){ 
        int64_t a, b;
        cin>>a>>b;
        if (a > b ) std::swap(a, b);
        int k = 0;
        while (a < b) {
            a <<=1;
            // cout<< "a="<<a<<endl;
            k++;
        }
        if (a!= b){
            printf("-1\n");
        }else{
            printf("%d\n", (k+2)/3);
        }
        // cout<<a<<endl;
    }
    return 0;
}