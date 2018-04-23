
    #include <cstdio>
    #include <cstring>
    #include<vector>
    #include <iostream>
    using namespace std;
    const int maxint=~0U>>1;

    /*
      用法:n节点个数。求解节点1到节点n的费用流
      (1)设置n
      (2)addEdge(from,to,cap,cost)
      (3)solve()
    */
    #define N 1000
    #define M 50000
    int n,m,pi1,cost=0;
    bool v[N];
    struct etype
    {
        int t,c,u;
        etype *next,*pair;
        etype(){}
        etype(int t_,int c_,int u_,etype* next_):
            t(t_),c(c_),u(u_),next(next_){}
        //void* operator new(unsigned,void* p){return p;}
    } *e[M];

    etype *Pe=new etype[M];

    int aug(int no,int m)
    {
        if(no==n)return cost+=pi1*m,m;
        v[no]=true;
        int l=m;
        for(etype *i=e[no];i;i=i->next)
            if(i->u && !i->c && !v[i->t])
            {
                int d=aug(i->t,l<i->u?l:i->u);
                i->u-=d,i->pair->u+=d,l-=d;
                if(!l)return m;
            }
        return m-l;
    }

    bool modlabel()
    {
        int d=maxint;
        for(int i=1;i<=n;++i)if(v[i])
            for(etype *j=e[i];j;j=j->next)
                if(j->u && !v[j->t] && j->c<d)d=j->c;
        if(d==maxint)return false;
        for(int i=1;i<=n;++i)if(v[i])
            for(etype *j=e[i];j;j=j->next)
                j->c-=d,j->pair->c+=d;
        pi1 += d;
        return true;
    }
    int solve(){
        cost=0;
        do do memset(v,0,sizeof(v));
        while(aug(1,maxint));
        while(modlabel());
        return cost;
    }
    void addEdge(int s,int t,int u,int c){
        e[s]=new(Pe++)etype(t, c,u,e[s]);
        e[t]=new(Pe++)etype(s,-c,0,e[t]);
        e[s]->pair=e[t];
        e[t]->pair=e[s];

    }
///////////////////////以上为zkw模板////////////////////////////
int main()
    {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=m;i++){
          int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
          addEdge(a,b,c,d);
        }
        printf("%d\n",solve());
        return 0;
    }

