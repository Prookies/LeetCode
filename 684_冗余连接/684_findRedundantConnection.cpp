#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

// 如果一棵树有N个节点，则这棵树有N-1条边

class Solution1
{
public:
    int findf(vector<int> &sets, int e)
    {
        int root = sets[e];
        if (root != e)
        {
            root = findf(sets, root);
        }

        return root;
    }

    vector<int> merge(vector<int> &sets, int e1, int e2)
    {
        int root1 = findf(sets, e1);
        int root2 = findf(sets, e2);

        if (root1 != root2)
        {
            sets[root1] = sets[root2];
        }
        else
        {
            return {e1, e2};
        }
        return {};
    }

    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {

        int n = edges.size();

        vector<int> ret;
        if (n < 2)
        {
            return ret;
        }

        vector<int> sets(n + 1);

        for (int i = 0; i < n + 1; i++)
        {
            sets[i] = i;
            // cout << sets[i] << endl;
        }

        for (int i = 0; i < n; i++)
        {
            ret = merge(sets, edges[i][0], edges[i][1]);
            if (!ret.empty())
            {
                return ret;
            }
        }

        return ret;
    }
};

class Solution2
{
    int Find(vector<int> &parent, int index)
    {
        if (parent[index] != index)
        {
            parent[index] = Find(parent, parent[index]);
        }
        return parent[index];
    }

    void Union(vector<int> &parent, int index1, int index2)
    {
        parent[Find(parent, index1)] = Find(parent, index2);
    }

    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        int nodesCount = edges.size();
        vector<int> parent(nodesCount + 1);
        for (int i = 1; i <= nodesCount; ++i)
        {
            parent[i] = i;
        }

        for (auto &edge : edges)
        {
            int node1 = edge[0], node2 = edge[1];
            if (Find(parent, node1) != Find(parent, node2))
            {
                Union(parent, node1, node2);
            }
            else
            {
                return edge;
            }
        }
        return vector<int>{};
    }
};