#include<stdio.h>
#include<string.h>

//后缀自动机Suffix Automaton
/*
  注意:
  (1)CHARSZ是字符个数 idx()可以对字符进行编码
*/
#define CHARSZ 26
int idx(char c){return c-'a';}  //返回值在[0,CHARSZ)内。
struct State{
  State* par,*go[CHARSZ];
  int val,f;
  //method
  State(int _val){
    par=0;
    val=_val;
    memset(go,0,sizeof(go));
  }
  void clear_all(){
    for (int i=0;i<CHARSZ;i++)
        if(go[i]) go[i]->clear_all();
    delete this;
  }
}*root,*last;
class SAM{
  private:
    State* root;
    State* last;
    void extend(int w);
  public:
    SAM(){root=last=NULL;}
    void buildSAM(char* s);   //初始化SAM
    void clearSAM();          //释放SAM
    State* getRoot(){return root;}
};
void SAM::extend(int w){
  State* p=last;
  State* np=new State(p->val+1);
  while(p&&p->go[w]==0){
    p->go[w]=np;
    p=p->par;
  }
  if (p==0) np->par=root;
  else{
    State* q=p->go[w];
    if (p->val+1 == q->val) np->par=q;
    else{
        State* nq=new State(p->val+1);
        memcpy(nq->go,q->go,sizeof(q->go));
        nq->par=q->par;
        q->par=nq;
        np->par=nq;
        while (p&& p->go[w]==q){
            p->go[w]=nq;
            p=p->par;
        }
    }
  }
  last=np;
}
void SAM::buildSAM(char* s){
  root=last=new State(0);
  int slen=strlen(s);
  for (int i=0;i<slen;i++)
    extend(idx(s[i]));
}
void SAM::clearSAM(){if (root) root->clear_all(); root=NULL;}
//-----------------end---------------------
int main(){
  SAM sam;
  sam.buildSAM("hello,world");
  //以下代码判断是否是hello,world的子串。
  while (true){
    char s[100];
    scanf("%s",s);
    State* cur=sam.getRoot();
    for (int i=0;i<strlen(s);i++){
      cur=cur->go[idx(s[i])];
      if (!cur)break;
    }
    if (cur)printf("yes\n");else printf("no\n");
  }
  return 0;
}
