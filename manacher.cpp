#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
using namespace std;
/*
  manacher algrithm
  (1)������ԭ������ͻ���ַ���ʹ�´������ڳ���Ϊż���Ļ��Ĵ�
  (2)һ����xΪ���ģ��뾶Ϊ10�Ļ��Ĵ�������벿��ĳ���е�(��x-5)���Ұ��ĳ���е�(��x+5)�Ļ��Ĵ����������ԡ�
*/
struct MANACHER{
#define STRSIZE 1010000
  char str[STRSIZE*2+5];
  int  radius[STRSIZE*2+5];
  int  str_len;
  MANACHER(){}
  MANACHER(char *tar){solver(tar);}
  int solver(char *tar);                //ִ��MANACHER�㷨
  int getMaxPalSize();                  //����Ĵ�����
  long long getPalNum();                //��ͬ���Ĵ�����
};
int MANACHER::solver(char *tar){
    //(1)construct new string
    int tar_len=strlen(tar);
    str_len=tar_len*2+2;
    str[0]='~';
    str[1]='!';
    for (int i=0;i<tar_len;i++){
      str[i*2+2]=tar[i];
      str[i*2+3]='!';
    }
    str[str_len]=0;
    //(2)calculate radius
    int max_idx=-1;
    int center=-1;
    for (int i=0;i<str_len;i++){
      radius[i]=1;
      if (max_idx>i)
        radius[i]=min(max_idx-i+1,radius[center*2-i]);
      while(str[i+radius[i]]==str[i-radius[i]]) radius[i]++;
      //update max_idx
      if (max_idx<i+radius[i]-1){
        max_idx=i+radius[i]-1;
        center=i;
      }
    }
    return 0;
}
int MANACHER::getMaxPalSize(){
    int ans=0;
    for (int i=1;i<str_len;i++)
       ans=max(ans,radius[i]-1);
    return ans;
}
long long MANACHER::getPalNum(){
    long long ans=0;
    for (int i=1;i<str_len;i++){
      ans+=radius[i]/2;
    }
    return ans;
}
MANACHER x;
char s[STRSIZE];
int main(){
  while (scanf("%s",s)!=EOF){
    x.solver(s);
    //printf("%lld\n",x.getPalNum()); //8
    printf("%d\n",x.getMaxPalSize());
  }
  return 0;
}
