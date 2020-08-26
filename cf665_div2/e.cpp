#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std; 
#define N 101000
#define E6 1000000
struct Line {
    int pos;
    int len;
    Line(int pos, int len):pos(pos), len(len){
    }
};
int n, m ;
vector<Line> lef,righ , bottom, top;
int cross_sum = 1; // 交点个数
void read() { 
    scanf("%d%d", &n, &m);
    for (int i =0;i<n;i++){
        int lx, rx, y;
        scanf("%d%d%d", &y, &lx, &rx);
        if (lx == 0) {
            lef.push_back(Line(y, rx));
        } else {
            righ.push_back(Line(y, E6 - lx));
        }
        if (lx == 0 && rx == E6) 
            cross_sum += 1;
    } 
    for (int i=0 ;i< m;i++){
        int x, y1, y2;
        scanf("%d%d%d", &x, &y1, &y2);
        if (y1 == 0){
            bottom.push_back(Line(x, y2));
        }else {
            top.push_back(Line(x, E6-y1));
        }
    }
    // printf("debug: 和边界交点: %d, l %zu r:%zu top :%zu, bot:%zu\n",cross_sum, lef.size(), righ.size(), top.size(), bottom.size());
}
struct NODE{ // 线段树
    NODE* l_node;
    NODE* r_node;
    int l, r;  // 长度在[l, r]区间内的数量
    int sum;
    NODE(int _l, int _r) {
        l = _l ;
        r = _r;
        sum =0; 
        l_node=r_node = nullptr;
    }
    void expand(){
        if (l_node || l == r) return ;
        int mid = (l+r)/2;
        l_node = new NODE(l, mid);
        r_node = new NODE(mid+1, r);
    }
    void update(){
        sum = l_node->sum + r_node->sum;
    }
    void inc(int pos){
        if (pos > r||pos <l) return ;
        if (l == r) {
            sum ++;
            return;
        }else {
            expand();
            l_node->inc(pos);
            r_node->inc(pos);
            update();
            // printf(" [inc] %d~%d %d\n", l, r, sum);
        }
    }
    int get_sum(int ll, int rr){
        if (ll > r || rr < l) return 0;  // 不在区间内
        if (sum == 0) return 0;         // 一个都没有
        if (l>=ll && r <= rr) {
            return sum;
        }
        return l_node->get_sum(ll, rr) + r_node->get_sum(ll, rr);
    }
};
void clear(NODE* node){
    if (node->l_node){
        clear(node->l_node);
        clear(node->r_node);
    }
    delete node;
}
bool sort_by_len(Line a, Line b) {
    return a.len <= b.len;
}
bool sort_by_pos(Line a, Line b) {
    return a.pos <= b.pos;
}
int solve(vector<Line>& lef, vector<Line>& bottom) {
    // 求交点数, 左侧节点为lef，底部节点为bottom
    /*
      思路：
      (1) 底部节点按长度排序 
      (2) 左侧节点按照坐标排序
      (3) 枚举底部节点，把左侧节点坐标逐渐加入线段树(左侧节点的长度)，然后求有多少节点长度
     */
    int num =0;
    std::sort(bottom.begin(), bottom.end(), sort_by_len);
    std::sort(lef.begin(), lef.end(), sort_by_pos);
    NODE *root = new NODE(0, E6);
    int lef_idx = 0;
    for (auto item : bottom) {
        // printf("x : %d len:%d\n", item.pos, item.len);
        while (lef_idx < lef.size() && lef[lef_idx].pos <= item.len){
            root->inc(lef[lef_idx].len);
            // printf("    add : %d len%d  总节点数:%d\n", lef[lef_idx].pos, lef[lef_idx].len, root->get_sum(0, E6));
            lef_idx ++;
        }
        int new_cross =  root->get_sum(item.pos, E6);
        // printf("    新增交叉:%d (%d->%d)\n ", new_cross, item.pos, E6);
        num+=new_cross ;
    }
    clear(root);
    return num;
}
int main(){ 
    read();
    // 底部和左侧
    cross_sum += solve(lef, bottom);
    // 底部和右侧
    vector<Line> bot;
    for (auto item : bottom) {
        bot.push_back(Line(E6 -item.pos, item.len));
    }
    cross_sum += solve(righ, bot);
    // 顶部和左侧
    vector<Line> tmp;
    for (auto item : lef) {
        tmp.push_back(Line(E6 - item.pos, item.len));
    }
    cross_sum += solve(tmp, top);
    // 顶部和右侧

    vector<Line> tmp2;
    tmp.clear();
    for (auto item : righ){
        tmp.push_back(Line(E6 - item.pos, item.len));
    }
    for (auto item : top){
        tmp2.push_back(Line(E6 - item.pos, item.len));
    }
    cross_sum += solve(tmp, tmp2);
    printf("%d\n", cross_sum);
    return 0;
}