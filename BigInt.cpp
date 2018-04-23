#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
class BigInt{ //�޷��������߾���
#define MAXDIGIT  10000  //���Ϊ10^MAXDIGIT
#define BIGINTMOD 10000  //ѹ4λ
private:
public:
  int n;                //a��nλ��Ч
  int a[MAXDIGIT/4+10]; //ѹ4λ���±��1��ʼ���Ҹ�λ��һ��Ϊ0��
  //��ʼ��
  BigInt();             //Ĭ������Ϊ0
  BigInt(long long x);  //����Ϊx
  BigInt(char *s);      //�����ַ���
  ~BigInt(){}
  //��ʼ��
  int  set(long long x);
  int  set(char* s);
  //��ʾ
  int  Display();       //���,û�л���
  int  trim();          //ȥ��ǰ׺0

  BigInt& operator =(BigInt& bnum);
  //(1)��Ŀ�ӷ�
  int     operator +=(BigInt& bnum);
  int     operator +=(int bnum);
  //(2)����
  int     operator /=(int bnum);  //����ֵΪmod bnum��ֵ��
};
//����������
//  (3)�˷�
int    operator *= (BigInt& anum,BigInt& bnum);
BigInt&operator *  (BigInt& anum,BigInt &bnum);
//  (4)ȡģ
int    operator %  (BigInt& anum,int bnum);
//  (5)˫Ŀ�ӷ�
BigInt&operator +  (BigInt& anum,BigInt& bnum);  //�м����ʹ�þ�̬����
//  (6)�Ƚ�
bool   operator <  (BigInt& anum,BigInt& bnum);
bool   operator >  (BigInt& anum,BigInt& bnum);
bool   operator == (BigInt& anum,BigInt& bnum);

//implementation
BigInt::BigInt(){
  set(0ll);
}
BigInt::BigInt(long long x){
  set(x);
}
BigInt::BigInt(char *s){
  set(s);
}
int BigInt::set(long long x){
  n=0;
  do{
      a[++n]=x%BIGINTMOD;
      x/=BIGINTMOD;
  }while(x);
  return 0;
}
int BigInt::set(char* s){
  n=0;
  int len=strlen(s)-1;
  while (len>=0){
     int digits=len+1>4?4:len+1; //���ѡ��4λ
     int num=0;
     for (int i=len-digits+1;i<=len;i++)
       num=num*10+s[i]-'0';
     a[++n]=num;
     len-=digits;
  }
  trim(); //ǰ׺0ɾȥ
  return 0;
}
int BigInt::Display(){
  printf("%d",a[n]);
  for (int i=n-1;i>=1;i--) printf("%04d",a[i]);
  return 0;
}
int BigInt::trim(){
  while (n>1 && a[n]==0){
    n--;
  }
  return 0;
}

BigInt& BigInt::operator =(BigInt& bnum){
  n=bnum.n;
  for (int i=1;i<=n;i++)a[i]=bnum.a[i];
  return bnum;
}
int  BigInt::operator +=(BigInt& bnum){
  n=max(n,bnum.n);
  int x=0;
  for (int i=1;i<=n;i++){
    a[i]=a[i]+bnum.a[i]+x;
    x=a[i]/BIGINTMOD;
    a[i]%=BIGINTMOD;
  }
  a[++n]=x;
  trim();
  return 0;
}
int  BigInt::operator +=(int bnum){
  a[1]+=bnum;
  int idx=1;
  while (a[idx]>=BIGINTMOD){
    a[idx+1]+=a[idx]/BIGINTMOD;
    a[idx]%=BIGINTMOD;
    idx++;
  }
  n=max(n,idx);
  return 0;
}
int operator *=(BigInt& cnum,BigInt& bnum){          //cnum*=bnum
  static BigInt anum;
  anum=cnum;
  //cnum=anum*bnum
  for (int i=anum.n+1;i<=bnum.n;i++) anum.a[i]=0;
  for (int i=bnum.n+1;i<=anum.n;i++) bnum.a[i]=0;
  cnum.n=anum.n+bnum.n;
  for (int i=1;i<=cnum.n;i++) cnum.a[i]=0;
  //
  for (int i=1;i<=anum.n;i++){
    int x=0;
    for (int j=1;j<=bnum.n;j++){
        cnum.a[i+j-1]+=anum.a[i]*bnum.a[j]+x;
        x=cnum.a[i+j-1]/BIGINTMOD;
        cnum.a[i+j-1]%=BIGINTMOD;
    }
    cnum.a[i+bnum.n]+=x;
  }
  cnum.trim();
  return 0;
}
BigInt& operator *(BigInt& anum,BigInt& bnum){  //cnum=anum*bnum
  static BigInt cnum;
  cnum=anum;
  cnum*=bnum;
  return cnum;
}
//����������
int    operator %  (BigInt& anum,int bnum){  //a%b
  int x=0;
  for (int i=anum.n;i>=1;i--){
    x=(x*BIGINTMOD+anum.a[i])%bnum;
  }
  return x;
}
int    BigInt::operator /=(int bnum){
  int x=0;
  for (int i=n;i>=1;i--){
    int tmp=x*BIGINTMOD+a[i];
    a[i]=tmp/bnum;
    x=tmp%bnum;
  }
  trim();
  return x;
}

BigInt &operator + (BigInt& anum,BigInt& bnum){
  static BigInt cnum;                                 //��̬��������
  cnum.n=max(anum.n,bnum.n);
  for (int i=anum.n+1;i<=cnum.n;i++)anum.a[i]=0;
  for (int i=bnum.n+1;i<=cnum.n;i++)bnum.a[i]=0;
  int x=0;
  for (int i=1;i<=cnum.n;i++){
    cnum.a[i]=anum.a[i]+bnum.a[i]+x;
    x=cnum.a[i]/BIGINTMOD;
    cnum.a[i]%=BIGINTMOD;
  }
  cnum.a[++cnum.n]=x;
  cnum.trim();
  return cnum;
}
bool operator < (BigInt& anum,BigInt& bnum){  //ʵ��<
  anum.trim();
  bnum.trim();
  if (anum.n > bnum.n) return false;
  if (anum.n < bnum.n) return true;
  for (int i=anum.n;i>=1;i--){
    if (anum.a[i] > bnum.a[i]) return false;
    if (anum.a[i] < bnum.a[i]) return true;
  }
  return false;
}
bool operator > (BigInt& anum,BigInt& bnum){ // anum>bnum  �ȼ��� bnum<anum
  return bnum<anum;
}
bool operator ==(BigInt& anum,BigInt& bnum){ // anum==bnum �ȼ��� anum<>bnum
  return (!(anum<bnum) && !(anum>bnum));
}
int main(){
  BigInt a("12345");
  int m=(a/=123456);
  printf("%d %d\n",m,12345%12345);
  a.Display();
  return 0;
}
