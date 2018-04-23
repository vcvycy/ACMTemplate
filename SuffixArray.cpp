#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
class SUFFIXARRAY {
#define SLEN 201000
  /*
    直接用函数.solve(char s[],int charSetSize=128)，s[]下标从0开始。
    charSetSize：表示0<=s[0]..s[n-1]<charSetSize。0为字符串结束符，尽量别用。这个开大开小基本不影响速度。
  */
  /*
    sa[],rank[],height[i]下标为1..n
    (1)sa[i]      : 排序后的后缀中，第i个在原串中的下标
    (2)rank[i]    : 原串第i个后缀，在排序后的后缀中下标,有sa[rank[i]]=i,rank[sa[i]]=i
    (3)height[i]  : 排序后的后缀中，第i个后缀和第i-1个后缀的LCP(最长公共前缀)。有height[i]=getlcp(sa[i-1],sa[i])
    (4)getlcp(i,j): 原串中，第i个后缀和第j个后缀的LCP。
  */
private:
  int s[SLEN];
  int t[SLEN], t2[SLEN], c[SLEN];
  int n;              // 字符个数，即strlen(s)
  static int lg[SLEN];//lg[i]=log2(i);下取整
  int f[SLEN][25];
  void clear();
    // m为最大字符值加1。调用之前需设置好s和n
  void build_sa(int m);
  void build_height();
  void initlcp();
public:
  SUFFIXARRAY();
  int sa[SLEN];
  int rank[SLEN];
  int height[SLEN];
  void solve(char *a,int charSetSize);
  int getlcp(int l,int r);//后缀 l,和后缀r的lcp
};
int SUFFIXARRAY::lg[SLEN];
SUFFIXARRAY::SUFFIXARRAY(){
    memset(lg,0,sizeof(lg));
    for (int i=2;i<=n;i<<=1)lg[i]=1;
    for (int i=1;i<=n;i++)lg[i]+=lg[i-1];
}
void SUFFIXARRAY::build_height() {
    int i, j, k = 0;
    for(i = 0; i < n; i++) rank[sa[i]] = i;
    for(i = 0; i < n; i++) {
      if(k) k--;
      int j = sa[rank[i]-1];
      while(s[i+k] == s[j+k]) k++;
      height[rank[i]] = k;
    }
  }
void SUFFIXARRAY::initlcp(){
    memset(f,0,sizeof(f));
    for (int i=1;i<=n;i++)f[i][0]=height[i];
    int m=lg[n];
    for (int j=1;j<=m;j++)
    for (int i=1;i<=n;i++){
    if  ((i-1+(1<<j))>n)break;
    f[i][j]=min(f[i][j-1],f[i+(1<<(j-1))][j-1]);
    }
  }
int SUFFIXARRAY::getlcp(int l,int r){//后缀 l,和后缀r的lcp
    if (l==r)return n-l+1;
    l=rank[l],r=rank[r];
    if (l>r)swap(l,r);l++;
    int tot=lg[r-l+1];
    return min(f[l][tot],f[r-(1<<(tot))+1][tot]);
  }
void SUFFIXARRAY::build_sa(int m){
    int i, *x = t, *y = t2;
    for(i = 0; i < m; i++) c[i] = 0;
    for(i = 0; i < n; i++) c[x[i] = s[i]]++;
    for(i = 1; i < m; i++) c[i] += c[i-1];
    for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1) {
      int p = 0;
      for(i = n-k; i < n; i++) y[p++] = i;
      for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
      for(i = 0; i < m; i++) c[i] = 0;
      for(i = 0; i < n; i++) c[x[y[i]]]++;
      for(i = 0; i < m; i++) c[i] += c[i-1];
      for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
      swap(x, y);
      p = 1; x[sa[0]] = 0;
      for(i = 1; i < n; i++)
        x[sa[i]] = y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1 : p++;
      if(p >= n) break;
      m = p;
    }
  }
void SUFFIXARRAY::clear() {
    n = 0;
    memset(sa, 0, sizeof(sa));
}
void SUFFIXARRAY::solve(char *a,int charSetSize=300){
    n=strlen(a)+1;
    for (int i=0;i<n;i++)s[i]=a[i];
    s[n]=0;
    build_sa(charSetSize+1);
    build_height();
    n--;
    for (int i=1;i<=n;i++)sa[i]++;
    for (int i=n;i>=1;i--)rank[i]=rank[i-1];
    initlcp();
  }
SUFFIXARRAY  sa;
char s[SLEN]="abcdefghij";
//s下标从0开始 ,rank[1]表示s[0]开始的后缀
int i,j,k,m,n;
int main(){
scanf("%s",s);
int m=strlen(s);
s[m]=27;
scanf("%s",s+m+1);

n=strlen(s);
sa.solve(s);
int ans=0;
for (i=2;i<=n;i++)
if ((sa.sa[i-1]<=m&&sa.sa[i]>m)||(sa.sa[i-1]>m&&sa.sa[i]<=m))
ans=max(sa.height[i],ans);
cout<<ans<<endl;
return 0;
}
