#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int,int>>> weightedAdj;
unordered_map<int,string> nodeName;

void printPathWithCost(const vector<int>& path, int cost) {
    for (size_t i=0;i<path.size();i++) {
        cout << nodeName[path[i]];
        if (i+1 != path.size()) cout << "->";
    }
    cout << "  (Cost: " << cost << ")";
    cout << endl;
}

void OracleUtil(int u,int goal, vector<bool>& vis, vector<int>& path,int cost){
    path.push_back(u);
    if (u==goal) {
        printPathWithCost(path, cost);
    } else {
        vis[u] = true;
        for (auto &p : weightedAdj[u]){
            if (!vis[p.first]) {
                OracleUtil(p.first,goal,vis,path,cost+p.second);
            }
        }
        vis[u] = false;
    }
    path.pop_back();
}

void OracleAll(int start,int goal){
    vector<bool> vis(weightedAdj.size(),false);
    vector<int> path;
    OracleUtil(start,goal,vis,path,0);
}

int main() {
    nodeName = {{0,"S"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"G"}};
    int n = 7; weightedAdj.assign(n,{});
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
    cout << "Oracle (All paths with cost):\n";
    OracleAll(start,goal);
}
