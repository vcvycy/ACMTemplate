#include<string.h>
#include<stdlib.h>
#include<stdio.h>
/*
  KMP算法：
  (1) init(s)  ：s会被复制一份
  (2) match(t) ：找到s中的匹配点，找不到返回-1
*/
class KMP{
#define N 101000
private:
  int nxt[N];
  int len;
  char s[N];
public:
  void  init(char* t){
    strcpy(s+1,t);
    len=strlen(s+1);
    memset(nxt,0,sizeof(nxt));
    //get nxt
    int j=0;
    for (int i=2;i<=len;i++){
      while (j&&s[j+1]!=s[i]) j=nxt[j];
      if (s[j+1]==s[i]) j++;
      nxt[i]=j;
    }
  }
  int match(char* t){
    t-=1;
    int j=0;
    int t_len=strlen(t+1);
    for (int i=1;i<=len;i++){
        while(j && s[i]!=t[j+1]) j=nxt[j];
        if (s[i]==t[j+1]) j++;
        if (j==t_len) {
          return i;
        }
    }
    return -1;
  }
}kmp;
char s[]="abaaba";
char t[]="aaa";
int main(){
  kmp.init(s);
  int m=kmp.match(t);
  printf("%d\n",m);
  return 0;
}
