#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define f first
#define s second
#define mp make_pair

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> uid(LLONG_MIN, LLONG_MAX);
 
struct node {
    ll val, priority, sz, sum;
    node *l = nullptr, *r = nullptr;
    bool rev = false;
 
    node(ll x) {
        val = x;
        priority = uid(rng);
        recalc();
    }
 
    void recalc() {
        sz = 1;
        sum = val;
        if (l != nullptr) {
            sum += l->sum;
            sz += l->sz;
        }
        if (r != nullptr) {
            sum += r->sum;
            sz += r->sz;
        }
    }
 
    void push() {
        if (rev) {
            rev = false;
            if (l != nullptr) {
                l->rev ^= 1;
                swap(l->l, l->r);
            }
            if (r != nullptr) {
                r->rev ^= 1;
                swap(r->l, r->r);
            }
        } 
    }
};
 
int sz(node* v) {
    return v == nullptr ? 0 : v->sz;
}
 
void heapify(node* v) {
    if (v == nullptr) return;
    node* big = v;
    if (v->l != nullptr && v->l->priority > big->priority) big = v->l;
    if (v->r != nullptr && v->r->priority > big->priority) big = v->r;
    if (big != v) {
        swap(v->priority, big->priority);
        heapify(big);
    }
}

node* build(vector<int>& v, int left, int right) {
    if (left > right) return nullptr;
    int mid = (left + right) / 2;
    node* res = new node(v[mid]);
    res->l = build(v, left, mid-1);
    res->r = build(v, mid+1, right);
    heapify(res);
    res->recalc();
    return res;
}

pair<node*, node*> split(node* v, int cur) {
    if (v == nullptr) return mp(nullptr, nullptr);
    v->push();
    if (sz(v->l) >= cur) {
        auto x = split(v->l, cur);
        v->l = x.s;
        v->recalc();
        return mp(x.f, v);
    }
    auto x = split(v->r, cur-sz(v->l)-1);
    v->r = x.f;
    v->recalc();
    return mp(v, x.s);
}
 
node* merge(node* l, node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    l->push();
    r->push();
    if (l->priority < r->priority) {
        l->r = merge(l->r, r);
        l->recalc();
        return l;
    }
    r->l = merge(l, r->l);
    r->recalc();
    return r;
}
 
void output(node* v) {
    if (v == nullptr) return;
    v->push();
    output(v->l);
    cout << v->val << "\n";
    output(v->r);
}
 
node* root;
 
void reverse(int x, int y) {
    auto cur = split(root, y);
    auto cur2 = split(cur.f, x-1);
    cur2.s->rev ^= 1;
    swap(cur2.s->l, cur2.s->r);
    root = merge(cur2.f, merge(cur2.s, cur.s));
}
 
ll query(int x, int y) {
    auto cur = split(root, y);
    auto cur2 = split(cur.f, x-1);
    ll res = cur2.s->sum;
    root = merge(cur2.f, merge(cur2.s, cur.s));
    return res;
}

void remove(node* cur) {
    if (cur == nullptr) return;
    remove(cur->l);
    remove(cur->r);
    delete cur;
}