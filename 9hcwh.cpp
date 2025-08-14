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
void HillClimbingWithHistory(int start, int goal) {
    vector<int> path;
    vector<bool> visited(weightedAdj.size(), false);
    vector<int> visitOrder;
    int cur = start;
    visited[cur] = true;
    path.push_back(cur);
    visitOrder.push_back(cur);
    int totalCost = 0;
    while (cur != goal) {
        int next = -1;
        int bestH = INT_MAX;
        int bestEdgeCost = INT_MAX;
        for (auto &edge : weightedAdj[cur]) {
            int v = edge.first;
            int cost = edge.second;
            if (!visited[v] && heuristic[v] < bestH) {
                bestH = heuristic[v];
                bestEdgeCost = cost;
                next = v;
            }
        }
        if (next == -1) break;
        totalCost += bestEdgeCost;
        cur = next;
        path.push_back(cur);
        visitOrder.push_back(cur);
        visited[cur] = true;
    }
    cout << "Path: ";
    printPath(path);
    cout << "Total cost: " << totalCost << endl;
    cout << "Visited order: ";
    for (size_t i = 0; i < visitOrder.size(); i++) {
        cout << nodeName[visitOrder[i]];
        if (i + 1 != visitOrder.size()) cout << "->";
    }
    cout << endl;
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
    cout << "Hill Climbing with history:\n";
    HillClimbingWithHistory(start,goal);
}
