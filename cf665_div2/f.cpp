#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
#define N ((1<<18)+1)
struct NODE {
    NODE* l;
    NODE* r;
    long long sum; // 和
    int need_reverse;
    int num;  // 有几个数值
    int depth;
    NODE() {
        l = r = nullptr;
        need_reverse = 0;
        sum =0;
    }
    void update(){ // 更新当前树上的值
        sum = l->sum + r->sum;
    }
    void build(int* a, int len, int d) {
        num = len;
        depth = d;
        if (num == 1) {
            sum = a[0];
            return ;
        }else {
            l = new NODE();
            r = new NODE();
            int half = len>>1;
            l->build(a, half, d-1);
            r->build(a + half, half, d-1);
            update();
        }
    }
    void pushdown() {
        // 将reverse 标记push down
        if (!need_reverse || num == 1) {
            return ;
        } else {
            if (need_reverse & (1<<depth)){
                swap(l, r);
                need_reverse ^= 1<<(depth - 1);
            }
            l->need_reverse ^= need_reverse;
            r->need_reverse ^= need_reverse;
            need_reverse = 0;
        }
    }
    void replace(int pos, int val) { // 位置pos(1..2^n)改成val
        pushdown();
        if (pos > num || pos <1) { // 不在当前子树上
            return;
        }
        if (num == 1){
            sum = val;
            return ;
        }
        l->replace(pos, val);
        r->replace(pos - (num >>1), val);
        update();
    }
    void reverse(int k) {  // depth
        need_reverse ^= (1<<k);
    }
    long long get_sum(int a, int b) {
        pushdown();
        if (b >= num) b = num;
        if (a <= 1) a = 1;
        if (a == 1 && b == num)  // 被包含
            return sum;
        long long sumlr = 0;
        // 左
        int half = num >>1;
        if (a <= half)
            sumlr += l->get_sum(a, b);
        if (b >half)
            sumlr += r->get_sum(a - half, b- half);
        return sumlr;
    }
    void print(){ // debug
        pushdown();
        if (num == 1){
            std::cout<< sum << " ";
        }else{
            l->print();
            r->print();
        }
    }
};
int a[N], q;
int n;
NODE *root = new NODE();
int main(){
    scanf("%d%d", &n, &q);
    for (int i=0;i < (1<<n); i++){
        scanf("%d", a+i);
    }
    root->build(a, 1 << n, n);
    // root->print();
    // std::cout<< "debug\n";
    while (q--){
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int pos, val;
            scanf("%d%d", &pos, &val);
            root->replace(pos, val);
        }else if (op == 2){
            int k;
            scanf("%d", &k);
            root->reverse(k);
        }else if (op == 3){
            int k;
            scanf("%d", &k);
            root->reverse(k+1);
            root->reverse(k);
        }else if (op ==4){
            int l, r;
            scanf("%d%d", &l, &r);
            std::cout<<root->get_sum(l, r) << std::endl;
        }
        // root->print();
        // std::cout<< "debug\n";
    }
    return 0;
}