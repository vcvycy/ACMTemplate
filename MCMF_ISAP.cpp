#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<iostream>
using namespace std;
struct EDGE{
  int from,to,flow,cap,cost;
  EDGE(int u=0,int v=0,int cp=0,int cst=0){from=u;to=v;flow=0;cap=cp;cost=cst;}
};
/*
  用法:(1) clearMap
       (2) addEdge    节点个数由addEdge自动计算
       (3) solve(s,t,&flow,&cost) 计算s->t的最小费用最大流,费用保存在cost中，流保留在flow中
*/
class MCMF{                                  //对费用流进行类似ISAP的优化
  #define MCMFINF 0x7fff0000
  #define MCMFN   1010
private:
  int  s,t;
  int  n;                                    //n在添加边时自动维护，节点下标范围[0..n]
  int  p[MCMFN];
  int  d[MCMFN];
  bool inq[MCMFN];
  vector<EDGE> e;
  vector<int>  g[MCMFN];
  bool spfa(int &flow,int &cost);            //是否能找到一条增广路
  int  augument(int &flow,int& cost);        //对p中的路径进行增广，流量和费用加在flow和cost中
public:
  int  clearMap();
  int  addEdge(int u,int v,int cap,int cost);  //添加一条单向边
  int  solve(int s,int t,int& flow,int&cost);  //求解s->t的费用流
};
int MCMF::clearMap(){
  n=0;
  e.clear();
  for (int i=0;i<MCMFN;i++)g[i].clear();
  return 0;
}
int MCMF::addEdge(int u,int v,int cap,int cost){
  n=max(n,u);
  n=max(n,v);
  e.push_back(EDGE(u,v,cap,cost));
  e.push_back(EDGE(v,u,0,-cost));
  g[u].push_back(e.size()-2);
  g[v].push_back(e.size()-1);
  return 0;
}
int MCMF::augument(int& flow,int& cost){
  int x=t;
  int mi_flow=MCMFINF;    //增广路可以通过的流量
  int cost2  =0;          //单位流量的cost
  while (x!=s){
    EDGE ed=e[p[x]];
    mi_flow=min(mi_flow,ed.cap-ed.flow);
    cost2 +=ed.cost;
    x=ed.from;
  }
  //边的流量增加
  x=t;
  while(x!=s){
    e[p[x]].flow+=mi_flow;
    e[p[x]^1].flow-=mi_flow;
    x=e[p[x]].from;
  }
  //
  flow+=mi_flow;
  cost+=cost2*mi_flow;
  return 0;
}
bool MCMF::spfa(int& flow,int& cost){
  for (int i=0;i<=n;i++)d[i]=MCMFINF;
  memset(inq,0,sizeof(inq));
  d[s]=0;
  inq[s]=true;
  //spfa
  queue<int> Q;
  Q.push(s);
  while (!Q.empty()){
     int u=Q.front();Q.pop();
     inq[u]=false;
     for (int i=0;i<g[u].size();i++){
       EDGE ed=e[g[u][i]];
       if (ed.cap>ed.flow && d[ed.to]>d[u]+ed.cost){
         d[ed.to]=d[u]+ed.cost;
         p[ed.to]=g[u][i];
         if (!inq[ed.to]){
           inq[ed.to]=true;
           Q.push(ed.to);
         }
       }
     }
  }
  if (d[t]>=MCMFINF) return false;
  augument(flow,cost);
  return true;
}
int MCMF::solve(int s,int t,int &flow,int& cost){
  flow=cost=0;
  this->s=s;
  this->t=t;
  while (spfa(flow,cost));
  return 0;
}
MCMF mcmf;
int main(){//poj2135
  int n,m;
  scanf("%d%d",&n,&m);
  mcmf.clearMap();
  for (int i=1;i<=m;i++){
    int u,v,w;
    scanf("%d %d %d",&u,&v,&w);
    //mcmf.addEdge(u,v,1,w);
    //mcmf.addEdge(v,u,1,w);
    int x=n+2+m*2-1;
    int y=n+2+m*2;
    mcmf.addEdge(u,x,1,0);
    mcmf.addEdge(v,x,1,0);
    mcmf.addEdge(x,y,1,w);
    mcmf.addEdge(y,v,1,0);
    mcmf.addEdge(y,u,1,0);
  }
  mcmf.addEdge(n+1,1,2,0);
  mcmf.addEdge(n,n+2,2,0);
  int flow,cost;
  mcmf.solve(n+1,n+2,flow,cost);
  printf("%d %d\n",flow,cost);
  return 0;
}
