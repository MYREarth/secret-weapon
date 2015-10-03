#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

//#define DBG

struct TEdge {
    int C;
    int F;
    int Back;
    int To;
    TEdge()
        : C(0)
        , F(0)
        , Back(0)
        , To(0)
    { }
};

typedef vector< vector<TEdge> > TGraph;

void AddEdge(TGraph *g, int from, int to, int c) {
    g->at(from).push_back(TEdge());
    g->at(to).push_back(TEdge());  
    g->at(from).back().Back = g->at(to).size() - 1;
    g->at(to).back().Back = g->at(from).size() - 1;
   
    g->at(from).back().C = c;
    g->at(from).back().To = to;
    g->at(to).back().To = from;
}


class FlowFinder {
    int From;
    int To;
    TGraph *G;
    int Step;
    vector<bool> Used;
  public:
    bool Dfs(int v) {
        Used[v] = true;
        if (v == To)
            return true;
        for (size_t i = 0; i < G->at(v).size(); ++i) {
            TEdge &edge = G->at(v)[i];
            if (!Used[edge.To] && edge.C - edge.F >= Step && Dfs(edge.To)) {
                edge.F += Step;
                G->at(edge.To)[edge.Back].F -= Step;
                return true; 
            }
        }
        return false;
    }
    int CalcMaxFlow(TGraph *g, int from, int to, int firstStep = 1<<30) {
        G = g;
        From = from;
        To = to;
        Step = firstStep;
        int flow = 0;
        while (Step > 0) {
            Used.assign(g->size(), false);
            if (Dfs(From))
                flow += Step;
            else
                Step /= 2;
        }
        return flow;
    }
    void STCut(vector<int> *result) {
        result->resize(Used.size() - 2);
        for (size_t i = 0; i + 2 < Used.size(); ++i)
            result->at(i) = 1 - static_cast<int>(Used[i]);
    }
};

void BuildGraph(
        const vector< pair<int, int> > &unary,
        const vector< vector<int> > &binary, 
        TGraph *g, int &s, int &t)
{
#ifdef DBG
    cerr << "In BuildGraph" << endl;
#endif

    s = unary.size();
    t = s + 1;
    g->assign(unary.size() + 2, vector<TEdge>());
    for (size_t v = 0; v < unary.size(); ++v)
        if (unary[v].first > 0)
            AddEdge(g, v, t, unary[v].first);
        else
            AddEdge(g, s, v, unary[v].second);
    for (size_t i = 0; i < binary.size(); ++i) {
        AddEdge(g, binary[i][0], binary[i][1], binary[i][2]);
        AddEdge(g, binary[i][1], binary[i][0], binary[i][2]);
    }
}

void CanonizeStructure(
        const vector< vector<int> > &unary,
        const vector< vector<int> > &binary,
        vector< pair<int, int> > *resUnary,
        vector< vector<int> > *resBinary)
{
#ifdef DBG
    cerr << "In CanonizeStructure" << endl;
#endif
    
    int vNum = unary.size();
    int eNum = binary.size();
    resUnary->resize(vNum);
    resBinary->assign(eNum, vector<int>(3));
    for (int i = 0; i < vNum; ++i)
        resUnary->at(i) = make_pair(2 * unary[i][0], 2 * unary[i][1]);
    for (int i = 0; i < eNum; ++i) {
        int u = binary[i][0];
        int v = binary[i][1];
        int e[2][2];
        for (int first = 0; first < 2; ++first)
            for (int second = 0; second < 2; ++second)
                e[first][second] = 2 * binary[i][2 + first * 2 + second];
        resUnary->at(u).first += e[0][0];
        e[0][1] -= e[0][0];
        e[0][0] = 0;
        resUnary->at(u).second += e[1][1];
        e[1][0] -= e[1][1];
        e[1][1] = 0;
        int half = (e[1][0] + e[0][1]) / 2;
        assert(half >= 0);
        resUnary->at(u).second -= half - e[1][0];
        resUnary->at(v).second += half - e[1][0];
        resBinary->at(i)[0] = u;
        resBinary->at(i)[1] = v;
        resBinary->at(i)[2] = half;
        assert(half >= 0);
    }
    for (int i = 0; i < vNum; ++i) {
        int mn = min(resUnary->at(i).first, resUnary->at(i).second);
        resUnary->at(i).first -= mn;
        resUnary->at(i).second -= mn;
    }
}


void Input(vector< vector<int> > *unary, vector< vector<int> > *binary) {
    int vNum, eNum;
    cin >> vNum >> eNum;

#ifdef DBG
    cerr << "Input: V = " << vNum << ". E = " << eNum << endl;
#endif

    assert(vNum > 0 && eNum >= 0);
    unary->assign(vNum, vector<int>(2));
    binary->assign(eNum, vector<int>(6));
    for (int i = 0; i < vNum; ++i)
        for (int j = 0; j < 2; ++j)
            cin >> unary->at(i)[j];
    for (int i = 0; i < eNum; ++i)
        for (int j = 0; j < 6; ++j)
            cin >> binary->at(i)[j];
}

int Evaluate(
        const vector< vector<int> > &unary,
        const vector< vector<int> > &binary,
        const vector<int> &labels) 
{
    int n = labels.size();
    assert(n == static_cast<int>(unary.size()));
    int result = 0;
    for (int i = 0; i < n; ++i)
        result += unary[i][labels[i]];
    for (size_t i = 0; i < binary.size(); ++i) {
        int u = binary[i][0];
        int v = binary[i][1];
        result += binary[i][2 + labels[u] * 2 + labels[v]];
    }
    return result;
}

void Output(int energy, const vector<int> &labels) {
    cout << energy << endl;
    for (size_t i = 0; i < labels.size(); ++i)
        cout << labels[i] << (i + 1 < labels.size() ? " " : "");
    cout << endl;
}

int main() {

    vector< vector<int> > rawUnary, rawBinary;
    vector< pair<int, int> > unary;
    vector< vector<int> > binary;
    Input(&rawUnary, &rawBinary);
    CanonizeStructure(rawUnary, rawBinary, &unary, &binary);
    TGraph graph;
    int s, t;
    BuildGraph(unary, binary, &graph, s, t);
    FlowFinder finder;
    finder.CalcMaxFlow(&graph, s, t);
    vector<int> labels;
    finder.STCut(&labels);
    Output(Evaluate(rawUnary, rawBinary, labels), labels);

    return 0;
}
