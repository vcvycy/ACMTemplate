#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

int main(){
    int n;
    scanf("%d", &n);
    while (n--){
        int k;
        scanf("%d", &k);
        vector<int> rst;
        int p = 1;
        while (k){
            int q = k%10;
            k/= 10;
            if (q > 0){
                rst.push_back(q*p);
            } 
            p *= 10;
        }
        printf("%d\n", rst.size());
        for (auto k : rst){
            printf("%d ", k);
        }
        putchar('\n');
    }
    return 0;
}