#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
unordered_map<int, string> nodeName;

void printPath(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << nodeName[path[i]];
        if (i + 1 != path.size()) cout << "->";
    }
    cout << endl;
}

bool DFSFromNode(int u, int goal, vector<bool>& vis, vector<int>& path, bool push=true) {
    if (push) path.push_back(u);
    vis[u] = true;
    if (u == goal) { printPath(path); return true; }
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (DFSFromNode(v,goal,vis,path)) return true;
        }
    }
    if (push) path.pop_back();
    vis[u] = false;
    return false;
}

void DFSandBFS(int start, int goal) {
    vector<bool> vis(adj.size(),false);
    queue<vector<int>> q;
    q.push({start});
    vis[start] = true;
    while(!q.empty()){
        auto path = q.front(); q.pop();
        int last = path.back();
        vector<bool> visDFS = vis;
        vector<int> pathDFS = path;
        if (DFSFromNode(last,goal,visDFS,pathDFS,false)) return;
        for (int v : adj[last]) {
            if (!vis[v]) {
                vis[v] = true;
                auto np = path; np.push_back(v);
                q.push(np);
            }
        }
    }
}

int main() {
    nodeName = {{0,"S"},{1,"A"},{2,"B"},{3,"C"},{4,"D"},{5,"E"},{6,"G"}};
    int n = 7;
    adj.assign(n,{});
    auto addEdge = [&](int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    };
    addEdge(0,1); addEdge(0,2); addEdge(1,3); addEdge(1,4);
    addEdge(2,4); addEdge(3,5); addEdge(4,5); addEdge(5,6);
    int start = 0, goal = 6;
    cout << "DFS+BFS:\n";
    DFSandBFS(start,goal);
}
