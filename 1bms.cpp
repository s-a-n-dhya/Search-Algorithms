#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> adj;
unordered_map<int,string> nodeName;


void printPath(const vector<int>& path) {
    for (size_t i=0; i<path.size(); i++) {
        cout << nodeName[path[i]];
        if (i+1 != path.size()) cout << "->";
    }
    cout << endl;
}


void BMSUtil(int u, int goal, vector<bool>& vis, vector<int>& path) {
    path.push_back(u);
    if (u == goal) {
        printPath(path);
    } else {
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v])
                BMSUtil(v, goal, vis, path);
        }
        vis[u] = false;
    }
    path.pop_back();
}

void BMS(int start, int goal) {
    vector<bool> vis(adj.size(), false);
    vector<int> path;
    BMSUtil(start, goal, vis, path);
}

int main() {
    nodeName = {{0,"S"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"G"}};
    
    int n = 7; 
    adj.assign(n, {});
    
    auto addEdge = [&](int u,int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(0,1);
    addEdge(0,2);
    addEdge(1,3);
    addEdge(1,4);
    addEdge(2,4);
    addEdge(3,5);
    addEdge(4,5);
    addEdge(5,6);

    int start = 0, goal = 6;

    cout << "British Museum Search (All paths):\n";
    BMS(start, goal);
}
