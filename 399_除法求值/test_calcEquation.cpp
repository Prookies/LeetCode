#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>

using std::make_pair;
using std::pair;
using std::queue;
using std::string;
using std::unordered_map;
using std::vector;

class Solution1
{
public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        vector<double> result;
        int len_equations = equations.size(), len_values = values.size();
        if (len_equations != len_values || 0 == len_equations)
        {
            return result;
        }

        unordered_map<string, int> variables;
        int nvars = 0;
        int n = len_equations;
        for (int i = 0; i < n; i++)
        {
            if (variables.find(equations[i][0]) == variables.cend())
            {
                variables[equations[i][0]] = nvars++;
            }
            if (variables.find(equations[i][1]) == variables.cend())
            {
                variables[equations[i][1]] = nvars++;
            }
        }

        // 对于每个点，存储其直接连接到的所有点及对应的权值
        vector<vector<pair<int, double>>> edges(nvars);
        for (int i = 0; i < n; i++)
        {
            int va = variables[equations[i][0]], vb = variables[equations[i][1]];
            edges[va].push_back(make_pair(vb, values[i]));
            edges[vb].push_back(make_pair(va, values[i]));
        }

        vector<double> ret;
        for (const auto &q : queries)
        {
            double result = -1.0;
            if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end())
            {
                int ia = variables[q[0]], ib = variables[q[1]];
                if (ia == ib)
                {
                    result = 1.0;
                }
                else
                {
                    queue<int> points;
                    points.push(ia);
                    vector<double> ratios(nvars, -1.0);
                    ratios[ia] = 1.0;

                    while (!points.empty() && ratios[ib] < 0)
                    {
                        int x = points.front();
                        points.pop();

                        for (const auto [y, val] : edges[x])
                        {
                            if (ratios[y] < 0)
                            {
                                ratios[y] = ratios[x] * val;
                                points.push(y);
                            }
                        }
                    }
                    result = ratios[ib];
                }
            }
            ret.push_back(result);
        }
        return ret;
    }
};

class Solution2
{
public:
    int findf(vector<int> &f, vector<double> &w, int x)
    {
        if (f[x] != x)
        {
            int father = findf(f, w, f[x]);
            w[x] = w[x] * w[f[x]];
            f[x] = father;
        }
        return f[x];
    }

    void merge(vector<int> &f, vector<double> &w, int x, int y, double val)
    {
        int fx = findf(f, w, x);
        int fy = findf(f, w, y);
        f[fx] = fy;
        w[fx] = val * w[y] / w[x];
    }

    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        int nvars = 0;
        unordered_map<string, int> variables;

        int n = equations.size();
        for (int i = 0; i < n; i++)
        {
            if (variables.find(equations[i][0]) == variables.end())
            {
                variables[equations[i][0]] = nvars++;
            }
            if (variables.find(equations[i][1]) == variables.end())
            {
                variables[equations[i][1]] = nvars++;
            }
        }
        vector<int> f(nvars);
        vector<double> w(nvars, 1.0);
        for (int i = 0; i < nvars; i++)
        {
            f[i] = i;
        }

        for (int i = 0; i < n; i++)
        {
            int va = variables[equations[i][0]], vb = variables[equations[i][1]];
            merge(f, w, va, vb, values[i]);
        }
        vector<double> ret;
        for (const auto &q : queries)
        {
            double result = -1.0;
            if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end())
            {
                int ia = variables[q[0]], ib = variables[q[1]];
                int fa = findf(f, w, ia), fb = findf(f, w, ib);
                if (fa == fb)
                {
                    result = w[ia] / w[ib];
                }
            }
            ret.push_back(result);
        }
        return ret;
    }
};

class Solution3
{
public:
    int findf(vector<int> &f, vector<double> &w, int x)
    {
        if (f[x] != x)
        {
            int father = findf(f, w, f[x]);
            w[x] = w[x] * w[f[x]];
            f[x] = father;
        }
        return f[x];
    }

    void merge(vector<int> &f, vector<double> &w, int x, int y, double val)
    {
        int fx = findf(f, w, x);
        int fy = findf(f, w, y);
        f[fx] = fy;
        w[fx] = val * w[y] / w[x];
    }

    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        int nvars = 0;
        unordered_map<string, int> variables;

        int n = equations.size();
        for (int i = 0; i < n; i++)
        {
            if (variables.find(equations[i][0]) == variables.end())
            {
                variables[equations[i][0]] = nvars++;
            }
            if (variables.find(equations[i][1]) == variables.end())
            {
                variables[equations[i][1]] = nvars++;
            }
        }
        vector<int> f(nvars);
        vector<double> w(nvars, 1.0);
        for (int i = 0; i < nvars; i++)
        {
            f[i] = i;
        }

        for (int i = 0; i < n; i++)
        {
            int va = variables[equations[i][0]], vb = variables[equations[i][1]];
            merge(f, w, va, vb, values[i]);
        }
        vector<double> ret;
        for (const auto &q : queries)
        {
            double result = -1.0;
            if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end())
            {
                int ia = variables[q[0]], ib = variables[q[1]];
                int fa = findf(f, w, ia), fb = findf(f, w, ib);
                if (fa == fb)
                {
                    result = w[ia] / w[ib];
                }
            }
            ret.push_back(result);
        }
        return ret;
    }
};
