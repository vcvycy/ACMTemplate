
#include<stdio.h>
#include<vector>
#include<queue>
#include<string.h>
using namespace std;
#define ACMXNODE 110   //AC�Զ����ڵ���(���Ϊ�����ַ����ַ�������)
int charIdx(char ch){ return ch-'a'; }
#define CHARSIZE 128   //��ͬ�ַ�����(128���Դ���󲿷�������ռ���ſ��Լ������ֵ,��Ҫ��֤charIdxÿ���ַ�����Ӧһ���±�)
class ACAUTO{
private:
  int sz;
  int ch[ACMXNODE][CHARSIZE];
  int val[ACMXNODE];       //�ڵ���ֵ��0��ʾ��Ҷ�ӽڵ㡣Ҷ�ӽڵ��¼һ���Զ���ֵ�����ǵڼ����ַ�����������ͬ�ַ����ụ�า�ǣ�
  int f[ACMXNODE];         //fail����
  int last[ACMXNODE];      ////last[u]����һ��u��β���ַ��������������ַ���(abcd,bc)���ڵ�u��ʾabc,��ڵ�last[u]ָ��bc��
  int print(int i,int j);
public:
  ACAUTO();
  //��ʼ��+��ͼ
  int clearMap();          //��ʼ��
  int ins(char *s,int v);  //����һ���ַ�����v�����ַ�����β�ڵ���ֵ��(0�����ַ�����β���������Զ���)
  int getFail();           //����ʧ��ָ�롣bfs����
  int kmpFind(char *T);    //�ҳ�trie��������ΪT�Ӵ����ַ���
};
ACAUTO::ACAUTO(){clearMap();}
int ACAUTO::clearMap(){
  sz=1;
  memset(ch[0],0,sizeof(ch[0]));
  memset(val,0,sizeof(val));
  return 0;
}
int ACAUTO::ins(char* s,int v=1){
  int u=0;
  int n=strlen(s);
  for (int i=0;i<n;i++){
    int c=charIdx(s[i]);
    if (!ch[u][c]){
      memset(ch[sz],0,sizeof(ch[sz]));
      val[sz]=0;
      ch[u][c]=sz++;
    }
    u=ch[u][c];
  }
  val[u]=v;
  return 0;
}
int ACAUTO::getFail(){
  queue<int> q;
  //�ȴ���ڵ�0��failֵ
  f[0]=0;
  for (int c=0;c<CHARSIZE;c++){
    int u=ch[0][c];
    if (u){
      f[u]=0;q.push(u);last[u]=0;
    }
  }
  //���������ڵ�
  while (!q.empty()){
    int r=q.front();q.pop();
    for (int c=0;c<CHARSIZE;c++){
       int u=ch[r][c];
       if (!u){ch[r][c]=ch[f[r]][c];continue;}
       q.push(u);
       f[u]=ch[f[r]][c];
       last[u]=val[f[u]]?f[u]:last[f[u]];
    }
  }
}

int ACAUTO::kmpFind(char *T){
  int n=strlen(T);
  int j=0;
  for (int i=0;i<n;i++){
    int c=charIdx(T[i]);
    j=ch[j][c];
    if (val[j])print(i,j);
      else
      if (last[j]) print(i,last[j]);
  }
}
int ACAUTO::print(int i,int j){
  if (j){
     printf("ģ�崮T��%d���ַ���β�Ӵ���AC�Զ������Ϊ%d��һ��,last[%d]=%d\n",i+1,val[j],j,last[j]);
     print(i,last[j]);
  }
  return 0;
}
ACAUTO ac;
int main(){
  int n;
  scanf("%d",&n);
  char s[100];
  ac.clearMap();
  for (int i=1;i<=n;i++){
    scanf("%s",s);
    ac.ins(s,i);
  }
  ac.getFail();
  while (1){
    scanf("%s",s);
    ac.kmpFind(s);
  }
  return 0;
}


