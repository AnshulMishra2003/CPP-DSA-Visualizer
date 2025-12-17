#ifndef UNDIRECTED_UNWEIGHTED_GRAPH_H
#define UNDIRECTED_UNWEIGHTED_GRAPH_H

#include <vector>
#include <queue>
#include <stack>

// Simple undirected, unweighted graph using adjacency lists
class UndirectedUnweightedGraph {
public:
    UndirectedUnweightedGraph() : n(0) {}

    int addVertex(){ adj.emplace_back(); return n++; }

    void addEdge(int u, int v){ ensureVertex(std::max(u,v)); adj[u].push_back(v); adj[v].push_back(u); }

    int vertexCount() const { return n; }

    const std::vector<int>& neighbors(int u) const { return adj[u]; }

    std::vector<int> bfs(int start) const {
        std::vector<int> order; if(start<0||start>=n) return order;
        std::vector<bool> vis(n,false); std::queue<int> q; q.push(start); vis[start]=true;
        while(!q.empty()){
            int u=q.front(); q.pop(); order.push_back(u);
            for(int v:adj[u]) if(!vis[v]){ vis[v]=true; q.push(v);}    
        }
        return order;
    }

    std::vector<int> dfs(int start) const {
        std::vector<int> order; if(start<0||start>=n) return order;
        std::vector<bool> vis(n,false); std::stack<int> st; st.push(start);
        while(!st.empty()){
            int u=st.top(); st.pop(); if(vis[u]) continue; vis[u]=true; order.push_back(u);
            for(int i=(int)adj[u].size()-1;i>=0;--i){ int v=adj[u][i]; if(!vis[v]) st.push(v);}    
        }
        return order;
    }

private:
    void ensureVertex(int idx){ while(idx>=n) addVertex(); }
    int n; 
    std::vector<std::vector<int>> adj;
};

#endif // UNDIRECTED_UNWEIGHTED_GRAPH_H
