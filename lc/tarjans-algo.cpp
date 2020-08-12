// https://leetcode.com/problems/critical-connections-in-a-network/
class Solution {
private:
    vector<vector<int>> adjList;
    vector<int> id;
    vector<int> low;
    vector<vector<int>> res;
    int lastId;
private:   
   void findCritical(int node, int parent) {
       lastId++;
       low[node] = id[node] = lastId;
       for (auto v: adjList[node]) {
           if (parent == v) {
               continue;
           }
           if (id[v] == -1) {
               findCritical(v, node);
               low[node] = min(low[node], low[v]);
               if (low[v] > id[node]) {
                   vector<int> c;
                   c.push_back(node);
                   c.push_back(v);
                   res.push_back(c);
               }
           }
           else {
               low[node] = min(low[node], low[v]);
           }
       }
   }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
       adjList = vector<vector<int>>(n);
       for (auto c: connections) {
           adjList[c[0]].push_back(c[1]);
           adjList[c[1]].push_back(c[0]);
       }
        id = vector<int>(n, -1);
        low = vector<int>(n, -1);
        lastId = 0;
        res.clear();
       findCritical(0, -1);
       return res;
    }

};
