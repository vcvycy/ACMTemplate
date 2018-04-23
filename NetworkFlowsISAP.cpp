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
  �÷�:(1) clearMap
       (2) addEdge    �ڵ������addEdge�Զ�����
       (3) solve(s,t)
*/
class ISAP{
  #define INF  0x7fff0000
  #define MXNODES 110
private:
  int s,t,n;                        //n��ʾ�ڵ��±�<=n�����n+1���ڵ�(�ڵ�0���ã������n���ڵ�)��n������ı��Զ����ɡ�
  vector<EDGE> e;
  vector<int>  g[MXNODES];
  queue<int>q;
  int num[MXNODES];
  int cur[MXNODES];
  int d[MXNODES];

  int p[MXNODES];                   //����·edge�±�
  int augment();                    //���һ������·�������¼·����p[u]��ʾ����һ��e[p[u]]�ı�����u��
  int bfs();                        //��ʼ��ÿ���㵽���ľ���(�߳���Ϊ1)
public:
  int clearMap();
  int addEdge(int u,int v,int cap); //���һ����u->v������Ϊcap����,initMap��ʾ�Ƿ����ͼ
  int solve(int s,int t);           //�����s->t�����
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
     while (d[s]<=n){                            //d[s]��ʾ��t->s���·�ĳ���
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
         if (--num[d[x]]==0)break;          //gap�Ż�
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
