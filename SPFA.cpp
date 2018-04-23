#include<stdio.h>
#include<vector>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;
struct EDGE{ //有向边u->v 长度为w
  int u,v,w;
  EDGE(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
};
/*
  用法：(1) clearMap()
        (2) addEdge() 有向边
        (3) solve(start) 计算以start为起点的最短路
*/
class SPFA{
  #define SPFAINF 0x7fffffff
  #define SPFAN   101000
private:
  int n;                    //n在加边是自动加入，表示节点下标区间为[0,n]
  vector<int>  g[SPFAN];
  bool         inq[SPFAN];
  int          cnt[SPFAN];  //进队数量
public:
  vector<EDGE> e;
  int  path[SPFAN]; //记录最短路路径。path[i]表示连接到i的最短路边下标
  int  dist[SPFAN]; //最短路
  int  clearMap();
  int  addEdge(int u,int v,int w); //添加一条有向边
  int  solve(int start);           //从start出发，计算最短路。成功返回0，出现负环返回-1
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
  //添加起点
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
