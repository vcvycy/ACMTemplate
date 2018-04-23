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
  int from,to,flow,cap;
  EDGE(int x=0,int y=0,int z=0){from=x;to=y;flow=0;cap=z;}
};
/*
  用法:(1) clearMap
       (2) addEdge    节点个数由addEdge自动计算
       (3) solve(s,t)
*/
class ISAP{
  #define INF  0x7fff0000
  #define MXNODES 110
private:
  int s,t,n;                        //n表示节点下标<=n，最多n+1个节点(节点0不用，则最多n个节点)。n由输入的边自动生成。
  vector<EDGE> e;
  vector<int>  g[MXNODES];
  queue<int>q;
  int num[MXNODES];
  int cur[MXNODES];
  int d[MXNODES];

  int p[MXNODES];                   //增光路edge下标
  int augment();                    //添加一条增光路，数组记录路径。p[u]表示存在一条e[p[u]]的边连向u。
  int bfs();                        //初始化每个点到汇点的距离(边长度为1)
public:
  int clearMap();
  int addEdge(int u,int v,int cap); //添加一条从u->v，容量为cap的流,initMap表示是否清空图
  int solve(int s,int t);           //计算从s->t最大流
};
int ISAP::clearMap(){
  this->n=0;
  e.clear();
  for (int i=0;i<MXNODES;i++)g[i].clear();
  memset(p,0,sizeof(p));
  return 0;
}
int ISAP::addEdge(int x,int y,int z){
  e.push_back(EDGE(x,y,z));
  e.push_back(EDGE(y,x,0));
  g[x].push_back(e.size()-2);
  g[y].push_back(e.size()-1);
  n=max(n,x);
  n=max(n,y);
  return 0;
}
int ISAP::augment(){
  int x=t,a=INF;
  while (x!=s){
    EDGE& ed=e[p[x]];
    a=min(a,ed.cap-ed.flow);
    x=ed.from;
  }
  x=t;
  while (x!=s){
    e[p[x]].flow+=a;
    e[p[x]^1].flow-=a;
    x=e[p[x]].from;
    }
    return a;
}
int ISAP::bfs(){
    memset(d,255,sizeof(d));
    q.push(t);
    d[t]=0;
    while (!q.empty()){
      int x=q.front();q.pop();
      for (int i=0;i<g[x].size();i++){
        EDGE& ed=e[g[x][i]];
        if (d[ed.to]==-1){
          d[ed.to]=d[x]+1;
          q.push(ed.to);
        }
      }
    }
    return 0;
}
int ISAP::solve(int s,int t){
     this->s=s;this->t=t;
     int flow=0;
     bfs();
     memset(num,0,sizeof(num));
     for (int i=s;i<=t;i++)if (d[i]>=0)num[d[i]]++;
     int x=s;
     memset(cur,0,sizeof(cur));
     while (d[s]<=n){                            //d[s]表示从t->s最短路的长度
       if (x==t){
         flow+=augment();
         x=s;
       }
       int ok=0;
       for (int i=cur[x];i<g[x].size();i++){
           EDGE& ed=e[g[x][i]];
           if (ed.cap>ed.flow&&d[x]==d[ed.to]+1){
             ok=1;
             p[ed.to]=g[x][i];
             cur[x]=i;
             x=ed.to;
             break;
           }
       }
       if (!ok){
         int m=MXNODES-1;
         for (int i=0;i<g[x].size();i++){
             EDGE& ed=e[g[x][i]];
             if (ed.cap>ed.flow) m=min(m,d[ed.to]);
           }
         if (--num[d[x]]==0)break;          //gap优化
         d[x]=m+1;
         if (d[x]<MXNODES) num[d[x]]++;
         cur[x]=0;
         if (x!=s)x=e[p[x]].from;
        }
     }
     return flow;
}
int main(){
ISAP sol;
sol.addEdge(1,2,3);
sol.clearMap();
vector<int>pig[1010];
int num[1010];
int i,j,k,m,n;
int x,y,z;
  cin>>m>>n;
  int s=n+1,t=n+2;
  for (i=1;i<=m;i++)cin>>num[i];
  for (i=1;i<=n;i++){
    cin>>j;
    while (j--)
    {
      cin>>k;
      pig[k].push_back(i);
    }
    cin>>k;
    sol.addEdge(i,t,k);
  }
  for (i=1;i<=m;i++)
    if (pig[i].size())
      sol.addEdge(s,pig[i][0],num[i]);
  for (i=1;i<=m;i++){
    for (j=1;j<pig[i].size();j++){
       int now=pig[i][j];
       int pre=pig[i][j-1];
       sol.addEdge(pre,now,INF);
    }
  }
  cout<<sol.solve(s,t)<<endl;
  return 0;
}
