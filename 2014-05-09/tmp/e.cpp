#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int inf = static_cast<int>(1e9);

struct TPoint {
    int X;
    int Y;
    int Value;
    TPoint(int x = 0, int y = 0, int value = 0)
        : X(x)
        , Y(y)
        , Value(value)
    { }
    bool operator<(const TPoint& point) const {
        return X < point.X;
    }
};


struct TLowerElem;
typedef TLowerElem* PLowerElem;
struct TLowerElem {
    PLowerElem LeftSon;
    PLowerElem RightSon;
    int MinX;
    int MaxX;
    pair<int, TPoint*> Max;
    TLowerElem()
        : LeftSon(0)
        , RightSon(0)
        , MinX(0)
        , MaxX(0)
        , Max(make_pair<int, TPoint*>(-inf, 0))
    { }
};

PLowerElem MakeLowerTree(vector<TPoint>::iterator begin, vector<TPoint>::iterator end) {
    if (begin >= end)
        return 0;
    PLowerElem result = new TLowerElem;
    if (begin + 1 == end) {
        result->MinX = begin->X;
        result->MaxX = begin->X;
        result->Max = make_pair(begin->Value, &(*begin));
    } else {
        vector<TPoint>::iterator pivot = begin + (end - begin) / 2;
        result->LeftSon = MakeLowerTree(begin, pivot);
        result->MinX = result->LeftSon->MinX;
        result->RightSon = MakeLowerTree(pivot, end);
        result->MaxX = result->RightSon->MaxX;
        result->Max = max(result->LeftSon->Max, result->RightSon->Max);
    }
    return result;
}

pair<int, TPoint*> GetMax(PLowerElem tree, int minX, int maxX) {
    if (minX > tree->MaxX || maxX < tree->MinX)
        return make_pair<int, TPoint*>(-inf, 0);
    if (minX <= tree->MinX && maxX >= tree->MaxX)
        return tree->Max;
    return max(GetMax(tree->LeftSon, minX, maxX), GetMax(tree->RightSon, minX, maxX));
}

struct TUpperElem;
typedef TUpperElem* PUpperElem;
struct TUpperElem {
    PLowerElem Tree;
    PUpperElem LeftSon;
    PUpperElem RightSon;
    vector<TPoint> Elems;
    int MinY;
    int MaxY;
    TUpperElem()
        : Tree(0)
        , LeftSon(0)
        , RightSon(0)
        , MinY(0)
        , MaxY(0)
    { }
};


PUpperElem MakeUpperTree(const vector<TPoint>& elems, int minY, int maxY) {
    if (elems.empty())
        return 0;
    PUpperElem result = new TUpperElem;
    result->Elems = elems;
    result->Tree = MakeLowerTree(result->Elems.begin(), result->Elems.end());
    result->MinY = minY;
    result->MaxY = maxY;
    if (minY < maxY) {
        int pivot = minY + (maxY - minY) / 2;
        vector<TPoint> lower, upper;
        for (size_t i = 0; i < elems.size(); ++i)
            if (elems[i].Y <= pivot)
                lower.push_back(elems[i]);
            else
                upper.push_back(elems[i]);
        result->LeftSon = MakeUpperTree(lower, minY, pivot);
        result->RightSon = MakeUpperTree(upper, pivot + 1, maxY);
    }
    return result;
}

pair<int, TPoint*> GetMax(PUpperElem tree, int minY, int maxY, int minX, int maxX) {
    if (minY > maxY || minX > maxX || !tree || minY > tree->MaxY || maxY < tree->MinY)
        return make_pair<int, TPoint*>(-inf, 0);
    if (minY <= tree->MinY && maxY >= tree->MaxY)
        return GetMax(tree->Tree, minX, maxX);
    return max(GetMax(tree->LeftSon, minY, maxY, minX, maxX), GetMax(tree->RightSon, minY, maxY, minX, maxX));
}

int CalcIn(PUpperElem root, int minY, int maxY, int minX, int maxX) {
    assert(minX < maxX && minY < maxY);
    pair<int, TPoint*> mx = max(GetMax(root, minY+1, maxY-1, minX, maxX), GetMax(root, minY, maxY, minX+1, maxX-1));
    if (mx.first == -inf)
        return 0;
    TPoint* p = mx.second;
    int add = 0;
    if ((p->Y == minY || p->Y == maxY) && p->X > minX && p->X < maxX)
        add = 1 + CalcIn(root, minY, maxY, minX, p->X) + CalcIn(root, minY, maxY, p->X, maxX);
    else if ((p->X == minX || p->X == maxX) && p->Y > minY && p->Y < maxY)
        add = 1 + CalcIn(root, minY, p->Y, minX, maxX) + CalcIn(root, p->Y, maxY, minX, maxX);
    else if (p->X > minX && p->X < maxX && p->Y > minY && p->Y < maxY)
        add = 3 + CalcIn(root, minY, p->Y, minX, p->X) + 
                  CalcIn(root, minY, p->Y, p->X, maxX) + 
                  CalcIn(root, p->Y, maxY, minX, p->X) + 
                  CalcIn(root, p->Y, maxY, p->X, maxX);
    return add;
}

int main() {

    int w, h, n;
    cin >> w >> h >> n;
    vector<TPoint> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].X >> p[i].Y;
        p[i].Value = n - i;
    }
    sort(p.begin(), p.end());

    PUpperElem root = MakeUpperTree(p, 0, h);
    int ans = 1 + CalcIn(root, 0, h, 0, w);

    cout << ans << endl;

    return 0;
}
