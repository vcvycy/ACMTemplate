#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
int main(){
    int t;
    scanf("%d", &t);
    while (t--){
        int n, k;
        scanf("%d%d", &n, &k);
        int ans =0 ;
        if (k > n){
            ans = k-n;
            n = k;
        }else{
            ans = 0;
        }
        if ((k+n)&1) ans++;
        printf("%d\n",ans);
    }
    return 0;
}