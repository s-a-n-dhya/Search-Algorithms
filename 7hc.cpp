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
void HillClimbing(int start,int goal) {
    vector<int> path; int cur = start; path.push_back(cur);
    vector<bool> vis(weightedAdj.size(),false);
    vis[cur] = true;
    while(cur != goal) {
        int next=-1, best=INT_MAX;
        for (auto &p : weightedAdj[cur]){
            if (!vis[p.first] && heuristic[p.first] < best) {
                best = heuristic[p.first];
                next = p.first;
            }
        }
        if (next==-1) break;
        cur = next;
        path.push_back(cur);
        vis[cur] = true;
    }
    printPath(path);
}
int main() {
    nodeName = {{0,"S"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"G"}};
    int n = 7; weightedAdj.assign(n,{});
    heuristic = {7,6,2,1,0,3,0};
    auto addWEdge = [&](int u,int v,int w){
        weightedAdj[u].push_back({v,w});
        weightedAdj[v].push_back({u,w});
    };
    addWEdge(0,1,2); addWEdge(0,2,4); addWEdge(1,3,3); addWEdge(1,4,5);
    addWEdge(2,4,1); addWEdge(3,5,2); addWEdge(4,5,1); addWEdge(5,6,2);
    int start = 0, goal = 6;
    cout << "Hill Climbing:\n";
    HillClimbing(start,goal);
}
