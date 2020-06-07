#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <iostream>
#include <set>
using namespace std;
int T;
int a[1100];
set<int> origin;
bool valid(int k){
    set<int> s2;
    // printf("\n ans =%d\n", k);
    for (auto x : origin){
        s2.insert(x^k);
        // printf("debug: %d\n", x^k);
    }
    //
    for (auto x : origin){
        if (s2.find(x) == s2.end()) return false;
        // retu
    }
    return true;
}
int main(){
    int n;
    scanf("%d", &T);
    while (T--){
        origin.clear();
        scanf("%d", &n);
        for (int i=1;i<=n;i++){
            scanf("%d", a+i);
            origin.insert(a[i]);
        }
        bool find = false;
        for (int ans =1 ;ans < (1<<10); ans++){
            if (valid(ans)){
               find = true;
               printf("%d\n", ans);
               break;
            }
        }  
        if (!find) printf("-1\n");
    }
    return 0;
}