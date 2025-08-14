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

struct BnBHNode {
    vector<int> path;
    int g,h;
    bool operator<(const BnBHNode&o) const { return g+h > o.g+o.h; }
};

void BranchAndBoundEstimatedList(int start,int goal){
    vector<vector<int>> explored;
    priority_queue<BnBHNode> pq;
    pq.push({{start},0,heuristic[start]});
    while(!pq.empty()){
        auto cur=pq.top(); pq.pop();
        explored.push_back(cur.path);
        int last=cur.path.back();
        if (last==goal){
            printPath(cur.path);
            cout << "Total cost: " << cur.g << endl;
            cout << "Explored paths:\n";
            for (auto &p : explored){
                printPath(p);
            }
            return;
        }
        for (auto &p : weightedAdj[last]){
            if (find(cur.path.begin(),cur.path.end(),p.first)==cur.path.end()){
                auto np=cur.path;
                np.push_back(p.first);
                pq.push({np, cur.g+p.second, heuristic[p.first]});
            }
        }
    }
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
    cout << "Branch and Bound with estimated list:\n";
    BranchAndBoundEstimatedList(start,goal);
}
