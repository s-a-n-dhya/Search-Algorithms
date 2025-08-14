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

struct AStarNode {
    int node;
    int g,h;
    vector<int> path;
    bool operator<(const AStarNode&o) const { return g+h > o.g+o.h; }
};

void AStar(int start,int goal){
    priority_queue<AStarNode> pq;
    pq.push({start,0,heuristic[start],{start}});
    set<int> closed;
    while(!pq.empty()){
        auto cur=pq.top(); pq.pop();
        if (cur.node==goal){
            printPath(cur.path);
            cout << "Total cost: " << cur.g << endl;
            return;
        }
        if (closed.count(cur.node)) continue;
        closed.insert(cur.node);
        for (auto &p : weightedAdj[cur.node]){
            if (!closed.count(p.first)){
                auto np = cur.path;
                np.push_back(p.first);
                pq.push({p.first, cur.g+p.second, heuristic[p.first], np});
            }
        }
    }
}

int main() {
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
    cout << "A* algorithm:\n";
    AStar(start,goal);
}
