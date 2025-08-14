#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> weightedAdj;
vector<int> heuristic;
unordered_map<int,string> nodeName;

void printPath(const vector<int>& path) {
    for (size_t i=0;i<path.size();i++) {
        cout << nodeName[path[i]];
        if (i+1 != path.size()) cout << "->";
    }
    cout << endl;
}

void BeamSearchWithHistory(int start, int goal, int beamWidth) {
    struct BeamHistNode {
        vector<int> path;
        int g;
        int h;
        int f() const { return g + h; }
    };
    vector<BeamHistNode> beam = { {{start}, 0, heuristic[start]} };
    vector<int> visitOrder;
    set<int> visitedNodes;
    while (!beam.empty()) {
        vector<BeamHistNode> all;
        for (auto &bn : beam) {
            int last = bn.path.back();
            if (!visitedNodes.count(last)) {
                visitedNodes.insert(last);
                visitOrder.push_back(last);
            }
            if (last == goal) {
                cout << "Path: ";
                printPath(bn.path);
                cout << "Total cost: " << bn.g << endl;
                cout << "Visited order: ";
                for (size_t i = 0; i < visitOrder.size(); i++) {
                    cout << nodeName[visitOrder[i]];
                    if (i + 1 != visitOrder.size()) cout << "->";
                }
                cout << endl;
                return;
            }
            for (auto &edge : weightedAdj[last]) {
                int v = edge.first;
                int cost = edge.second;
                if (find(bn.path.begin(), bn.path.end(), v) == bn.path.end()) {
                    auto np = bn.path;
                    np.push_back(v);
                    all.push_back({np, bn.g + cost, heuristic[v]});
                }
            }
        }
        sort(all.begin(), all.end(), [](const BeamHistNode &a, const BeamHistNode &b) {
            return a.f() < b.f();
        });
        if ((int)all.size() > beamWidth) all.resize(beamWidth);
        beam = all;
    }
    cout << "No path found by Beam Search with history.\n";
}

int main() {
    nodeName = {{0,"S"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"G"}};
    int n = 7; weightedAdj.assign(n,{});
    heuristic = {7,6,2,1,0,3,0};
    auto addWEdge = [&](int u,int v,int w){
        weightedAdj[u].push_back({v,w});
        weightedAdj[v].push_back({u,w});
    };
    addWEdge(0,1,2);
    addWEdge(0,2,4);
    addWEdge(1,3,3);
    addWEdge(1,4,5);
    addWEdge(2,4,1);
    addWEdge(3,5,2);
    addWEdge(4,5,1);
    addWEdge(5,6,2);
    int start = 0, goal = 6;
    cout << "Beam Search with history:\n";
    BeamSearchWithHistory(start,goal,2);
}
