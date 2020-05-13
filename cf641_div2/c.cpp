#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;
int T;
#define N 201000
std::vector<int> divisor[N];
bool is_prime[N];
int pnum = 0;
int prime[N];
int init(){
    for (int i=1; i< N;i++) is_prime[i] = true;
    for(int i=2;i<N ;i++){
        if (!is_prime[i])continue;
        prime[++pnum] = i;
        for (int j=i;j< N;j+=i){
            divisor[j].push_back(i);
            is_prime[j] = false;
            // if (j == 30) printf("%d\n", i);
        }
    }
    return 0;
}
int prime_cnt[N];
int prime_min[N];
int prime_min2[N];
void solve(){
    memset(prime_cnt, 0, sizeof(prime_cnt));
    memset(prime_min, 0, sizeof(prime_min));
    memset(prime_min2, 0, sizeof(prime_min2));
    int n;
    scanf("%d", &n);
    for (int i=1;i<=n;i++){
        int ai;
        scanf("%d", &ai);
        for (auto p : divisor[ai]){
            int num = 0;
            int tmp = ai;
            while (tmp % p ==0) {num ++; tmp/=p;}
            // printf("  %d^%d ", p, num);
            if (prime_cnt[p] == 0){
                prime_min[p] = num;
            }else 
            if (prime_cnt[p] == 1){
                prime_min2[p] = num;
            } else{
                if (num < prime_min2[p]) prime_min2[p] = num;
            }
            prime_cnt[p] ++;
            if (prime_cnt[p] >1 &&prime_min[p] > prime_min2[p]) std::swap(prime_min[p], prime_min2[p]);
        }
        // putchar('\n');
    }
    long long ans = 1;
    for (auto p : prime){
        if (n>=3 && prime_cnt[p] <= n-2){
            continue;
        }
        if (n==2 && prime_cnt[p] == 0) continue;
        // printf("prime : %d , num : %d %d", p, prime_min[p], prime_min2[p]);
        int num =prime_min2[p]; 
        if (n == 2 && prime_cnt[p] == 1) num = prime_min[p];
        if (n >= 3 && prime_cnt[p] == n-1) num = prime_min[p];
        while (num --)
            ans *= p;
    }
    std::cout<<ans<<std::endl;
    // printf("%d\n", ans);
}
int main(){
    init();
    solve();
    return 0;
}