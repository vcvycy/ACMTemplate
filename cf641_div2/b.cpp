#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;
int T;
#define N 101000
std::vector<int> divisor[N];
int init(){
    for(int i=1;i<N ;i++){
        for (int j=i;j< N;j+=i){
            divisor[j].push_back(i);
            // if (j == 30) printf("%d\n", i);
        }
    }
    return 0;
}
int f[N];
int s[N];
void solve(){
    memset(f, 0, sizeof(f));
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n;i++) scanf("%d", s+i);
    f[1] = 1;
    int ans = 1;
    for (int i=2; i<=n;i++){
        f[i] = 1;
        for (auto j : divisor[i]){
            if (s[j] >= s[i]) continue;
            f[i] = std::max(f[i], f[j] + 1);
        }
        // printf("debug : %d %d\n", i, f[i]);
        ans = std::max(f[i], ans);
    }
    printf("%d\n", ans);
}
int main(){ 
    init();
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}