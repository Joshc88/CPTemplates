#include <bits/stdc++.h>
using namespace std;

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()
 
T dot(pt v, pt w) {return (conj(v)*w).x;}
T cross(pt v, pt w) {return (conj(v)*w).y;}
T orient(pt a, pt b, pt c) {return cross(b-a,c-a);} // positive for left, negative for right, 0 for straight
 
bool half(pt p) {return p.y > 0 || (p.y == 0 && p.x < 0);}
// Warning: polarSort shouldn't contain origin
void polarSort(vector<pt> &v) {sort(v.begin(), v.end(), [](pt v, pt w) {return make_tuple(half(v), 0) < make_tuple(half(w), cross(v,w));});}
bool inDisk(pt a, pt b, pt p) {return dot(a-p, b-p) <= 0;}
bool onSegment(pt a, pt b, pt p) {return orient(a,b,p) == 0 && inDisk(a,b,p);}
 
bool intersect(pt a, pt b, pt c, pt d) {
    if (onSegment(a, b, c)) return true;
    if (onSegment(a, b, d)) return true;
    if (onSegment(c, d, a)) return true;
    if (onSegment(c, d, b)) return true;
    T oa = orient(c, d, a), ob = orient(c, d, b), oc = orient(a, b, c), od = orient(a, b, d);
    return ((oa > 0 && ob < 0) || (oa < 0 && ob > 0)) && ((oc > 0 && od < 0) || (oc < 0 && od > 0));
}

vector<pt> convexHull(vector<pt> &v) { // Returns in counterclockwise order
    int n = v.size();
    vector<int> lower, upper;
    sort(v.begin(), v.end(), [](pt a, pt b) {return make_pair(a.x, a.y) < make_pair(b.x, b.y);});
    for (int i=0; i<n; i++) {
        while (lower.size() > 1 && orient(v[lower[lower.size()-2]], v[lower.back()], v[i]) < 0) lower.pop_back();
        lower.push_back(i);
    }
    for (int i=n-1; i>=0; i--) {
        while (upper.size() > 1 && orient(v[upper[upper.size()-2]], v[upper.back()], v[i]) < 0) upper.pop_back();
        upper.push_back(i);
    }
    vector<pt> res;
    vector<bool> inlower(n);
    for (int i : lower) {
        inlower[i] = true;
        res.push_back(v[i]);
    }
    for (int i : upper) {
        if (!inlower[i]) res.push_back(v[i]);
    }
    return res;
}

int contains(vector<pt> &polygon, pt p) {
    // Return 0 if outside, 1 if inside, 2 if on boundary
    int n = polygon.size(), res = 0;
    for (int i=0; i<n; i++) {
        if (onSegment(polygon[i], polygon[(i+1)%n], p)) return 2;
        res ^= ((p.y>=polygon[(i+1)%n].y)-(p.y>=polygon[i].y)) * orient(p, polygon[i], polygon[(i+1)%n]) > 0;
    }
    return res;
}