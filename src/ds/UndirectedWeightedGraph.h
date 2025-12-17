#ifndef UNDIRECTED_WEIGHTED_GRAPH_H
#define UNDIRECTED_WEIGHTED_GRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <utility>

// Simple undirected, weighted graph using adjacency lists
class UndirectedWeightedGraph {
public:
    using Edge = std::pair<int,int>; // (to, weight)

    UndirectedWeightedGraph() : n(0) {}

    int addVertex(){ adj.emplace_back(); return n++; }

    void addEdge(int u, int v, int w){ ensureVertex(std::max(u,v)); adj[u].emplace_back(v,w); adj[v].emplace_back(u,w); }

    int vertexCount() const { return n; }

    const std::vector<Edge>& neighbors(int u) const { return adj[u]; }

    // BFS/DFS by topology (weights ignored for traversal order)
    std::vector<int> bfs(int start) const {
        std::vector<int> order; if(start<0||start>=n) return order;
        std::vector<bool> vis(n,false); std::queue<int> q; q.push(start); vis[start]=true;
        while(!q.empty()){
            int u=q.front(); q.pop(); order.push_back(u);
            for(const auto &e:adj[u]) if(!vis[e.first]){ vis[e.first]=true; q.push(e.first);}    
        }
        return order;
    }

    std::vector<int> dfs(int start) const {
        std::vector<int> order; if(start<0||start>=n) return order;
        std::vector<bool> vis(n,false); std::stack<int> st; st.push(start);
        while(!st.empty()){
            int u=st.top(); st.pop(); if(vis[u]) continue; vis[u]=true; order.push_back(u);
            for(int i=(int)adj[u].size()-1;i>=0;--i){ int v=adj[u][i].first; if(!vis[v]) st.push(v);}    
        }
        return order;
    }

private:
    void ensureVertex(int idx){ while(idx>=n) addVertex(); }
    int n; 
    std::vector<std::vector<Edge>> adj;
};

#endif // UNDIRECTED_WEIGHTED_GRAPH_H
