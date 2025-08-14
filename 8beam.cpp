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
struct BeamNode {
    vector<int> path;
    int cost;
    int h;
    int f() const { return cost+h; }
};
void BeamSearch(int start,int goal,int beamWidth){
    vector<BeamNode> beam = {{{start},0,heuristic[start]}};
    while(!beam.empty()){
        vector<BeamNode> all;
        for (auto &bn: beam){
            int last = bn.path.back();
            if (last == goal) { printPath(bn.path); return; }
            for (auto &p : weightedAdj[last]){
                if (find(bn.path.begin(),bn.path.end(),p.first)==bn.path.end()){
                    auto np = bn.path; np.push_back(p.first);
                    all.push_back({np, bn.cost+p.second, heuristic[p.first]});
                }
            }
        }
        sort(all.begin(),all.end(),[](auto&a,auto&b){return a.f()<b.f();});
        if ((int)all.size()>beamWidth) all.resize(beamWidth);
        beam = all;
    }
}
int main(){
    nodeName = {{0,"S"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"G"}};
    int n = 7;
    weightedAdj.assign(n,{});
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
    cout << "Beam Search:\n";
    BeamSearch(start,goal,2);
}
