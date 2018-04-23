#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
struct EDGE{ //�����u->v ����Ϊw
  int u,v,w;
  EDGE(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
};
/*
  �÷���(1) clearMap()
        (2) addEdge() �����
        (3) solve(start) ������startΪ�������·
*/
class SPFA{
  #define SPFAINF 0x7fffffff
  #define SPFAN   101000
private:
  int n;                    //n�ڼӱ����Զ����룬��ʾ�ڵ��±�����Ϊ[0,n]
  vector<int>  g[SPFAN];
  bool         inq[SPFAN];
  int          cnt[SPFAN];  //��������
public:
  vector<EDGE> e;
  int  path[SPFAN]; //��¼���··����path[i]��ʾ���ӵ�i�����·���±�
  int  dist[SPFAN]; //���·
  int  clearMap();
  int  addEdge(int u,int v,int w); //���һ�������
  int  solve(int start);           //��start�������������·���ɹ�����0�����ָ�������-1
};
int SPFA::clearMap(){
  n=0;
  e.clear();
  for (int i=0;i<SPFAN;i++)g[i].clear();
  return 0;
}
int SPFA::addEdge(int u,int v,int w){
  n=max(n,u);
  n=max(n,v);
  e.push_back(EDGE(u,v,w));
  g[u].push_back(e.size()-1);
  return 0;
}
int SPFA::solve(int start){
  memset(dist,127,sizeof(dist));
  memset(cnt,0,sizeof(cnt));
  memset(inq,false,sizeof(inq));
  memset(path,255,sizeof(path));
  queue<int> Q;
  //������
  dist[start]=0;
  cnt[start]=1;
  inq[start]=true;
  Q.push(start);
  while (!Q.empty()){
    int u=Q.front();
    Q.pop();
    inq[u]=false;
    for (int i=0;i<g[u].size();i++){
      EDGE ed=e[g[u][i]];
      if (dist[ed.v]>dist[u]+ed.w){
        dist[ed.v]=dist[u]+ed.w;
        path[ed.v]=g[u][i];
        if (!inq[ed.v]){
          Q.push(ed.v);
          inq[ed.v]=true;
          cnt[ed.v]++;
          if (cnt[ed.v]>n) return -1;
        }
      }
    }
  }
  return 0;
}
SPFA spfa;
int u[101000],v[101000],w[101000];
int d[101000];
int main(){
  spfa.clearMap();
  int n,m,x;
  scanf("%d%d%d",&n,&m,&x);
  for (int i=1;i<=m;i++){
    scanf("%d%d%d",&u[i],&v[i],&w[i]);
    spfa.addEdge(u[i],v[i],w[i]);
  }
  spfa.solve(x);
  int k=4;
  while (spfa.path[k]!=-1){
    k=spfa.e[spfa.path[k]].u;
    printf("%d->\n",k);
  }
  return 0;
}
