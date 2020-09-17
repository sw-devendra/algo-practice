// https://leetcode.com/problems/critical-connections-in-a-network/
// Learning concept : https://www.youtube.com/watch?v=RYaakWv5m6o&t=1532s
// Coding approachg
//  DFS with following considerations:
//      - ids can be used as visited array, no need of separate visited array
//      - some actions has to be taken for both visited and unvisted neighbors, **EXCEPT PARENT node in DFS**
//              - So passing the parent becomes necessary
//              - actions :
//                  - if already visited, just update low value of current node
//                  - if not visited, (1) visit (2) update low value of current node (3) compare id of current node with neighbor to update critical connection
// Frequently missed points :
//     (1) Checking parent node
//     (2) To add critical connection, id of current node should be compared with low of neighbor, comparing lows of both will give pass all TCs but one.
//             To Do: Add simple example of failing case when lows of both are compared

class Solution {
    vector<vector<int>> adjList;
    vector<int> ids;
    vector<int> lows;
    vector<vector<int>> resultConnections;
    int lastId;
private:
    void init(int n, vector<vector<int>>& connections) {
        adjList = vector<vector<int>>(n);
        for (auto connection: connections) {
            adjList[connection[0]].push_back(connection[1]);
            adjList[connection[1]].push_back(connection[0]);
        }
        ids = vector<int>(n, -1);
        lows = ids;
        lastId = -1;
        resultConnections.clear();
    }
    void dfs(int node, int parent) { // Parent is never looked back as neighbor
        lastId++;
        ids[node] = lows[node] = lastId;
        for (auto neighbor: adjList[node]) {
            if (neighbor == parent)
                continue;
            
            if (ids[neighbor] == -1) { // not visited yet
                dfs(neighbor, node); // visit
                lows[node] = min(lows[neighbor], lows[node]); // update low of current
                if (ids[node] < lows[neighbor]) {  // check critical connection
                    // Found a critical connection
                    vector<int> conn(2);
                    conn[0] = node;
                    conn[1] = neighbor;
                    resultConnections.push_back(conn);
                }
            }
            else {
                lows[node] = min(lows[neighbor], lows[node]);
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        init(n, connections);
        dfs(0, -1);
        return resultConnections;
    }

};
