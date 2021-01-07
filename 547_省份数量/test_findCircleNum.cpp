#include <vector>
#include <queue>

using std::queue;
using std::vector;

class Solution1
{
public:
    int findf(vector<int> &city_root, int end)
    {
        int f = city_root[end];
        if (f != end)
        {
            f = findf(city_root, f);
        }
        return f;
    }

    bool merge(vector<int> &city_root, int end1, int end2)
    {
        int f1 = findf(city_root, end1);
        int f2 = findf(city_root, end2);

        if (f1 != f2)
        {
            if (f1 < f2)
                city_root[f2] = f1;
            else
                city_root[f1] = f2;

            return true;
        }
        else
        {
            return false;
        }
    }

    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        if (0 == n)
        {
            return 0;
        }

        int ret = n;
        vector<int> city_root(n, -1);
        for (int i = 0; i < n; i++)
        {
            city_root[i] = i;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isConnected[i][j] != 0)
                {
                    if (merge(city_root, i, j))
                    {
                        ret--;
                    }
                }
            }
        }

        return ret;
    }
};

class Solution2
{
public:
    // 把连接在一起的节点都遍历，直到不能继续向下遍历为止
    void dfs(vector<vector<int>> &isConnected, vector<int> &visited, int provinces, int i)
    {
        for (int j = 0; j < provinces; j++)
        {
            if (isConnected[i][j] == 1 && !visited[j])
            {
                visited[j] = 1;
                dfs(isConnected, visited, provinces, j);
            }
        }
    }

    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int provinces = isConnected.size();
        vector<int> visited(provinces);
        int circles = 0;
        for (int i = 0; i < provinces; i++)
        {
            if (!visited[i])
            {
                dfs(isConnected, visited, provinces, i);
                circles++;
            }
        }
        return circles;
    }
};

class Solution3
{
public:
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int provinces = isConnected.size();
        vector<int> visited(provinces);
        int circles = 0;
        queue<int> Q;
        for (int i = 0; i < provinces; i++)
        {
            if (!visited[i])
            {
                Q.push(i);
                while (!Q.empty())
                {
                    int j = Q.front();
                    Q.pop();
                    visited[j] = 1;
                    for (int k = 0; k < provinces; k++)
                    {
                        if (isConnected[j][k] == 1 && !visited[k])
                        {
                            Q.push(k);
                        }
                    }
                }
                circles++;
            }
        }
        return circles;
    }
};

class Solution4
{
public:
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

    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int provinces = isConnected.size();
        vector<int> parent(provinces);
        for (int i = 0; i < provinces; i++)
        {
            parent[i] = i;
        }

        for (int i = 0; i < provinces; i++)
        {
            for (int j = i + 1; j < provinces; j++)
            {
                if (isConnected[i][j] == 1)
                {
                    Union(parent, i, j);
                }
            }
        }
        int circles = 0;
        for (int i = 0; i < provinces; i++)
        {
            if (parent[i] == i)
            {
                circles++;
            }
        }

        return circles;
    }
};