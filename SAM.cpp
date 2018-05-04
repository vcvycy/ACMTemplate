#include<stdio.h>
#include<string.h>

//��׺�Զ���Suffix Automaton
/*
  ע��:
  (1)CHARSZ���ַ����� idx()���Զ��ַ����б���
*/
#define CHARSZ 26
int idx(char c){return c-'a';}  //����ֵ��[0,CHARSZ)�ڡ�
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
    void buildSAM(char* s);   //��ʼ��SAM
    void clearSAM();          //�ͷ�SAM
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
  //���´����ж��Ƿ���hello,world���Ӵ���
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
