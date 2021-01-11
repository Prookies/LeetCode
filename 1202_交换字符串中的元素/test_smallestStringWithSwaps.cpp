#include <vector>
#include <string>
#include <map>
#include <algorithm>

using std::map;
using std::sort;
using std::string;
using std::vector;

class Solution
{
public:
    int findf(vector<int> &sets, int val)
    {
        int f = sets[val];
        if (f != val)
        {
            f = findf(sets, f);
        }
        return f;
    }

    void merge(vector<int> &sets, int e1, int e2)
    {
        int f1 = findf(sets, e1);
        int f2 = findf(sets, e2);
        if (f1 < f2)
        {
            sets[f2] = f1;
        }
        else
        {
            sets[f1] = f2;
        }
    }

    string smallestStringWithSwaps(string s, vector<vector<int>> &pairs)
    {
        string ret(s);

        int n = s.size();
        vector<int> sets(n);

        for (int i = 0; i < n; i++)
        {
            sets[i] = i;
        }

        for (auto &pair : pairs)
        {
            merge(sets, pair[0], pair[1]);
        }

        map<int, vector<int>> comb;

        for (int i = 0; i < n; i++)
        {
            comb[findf(sets, sets[i])].push_back(i);
        }

        // for(auto iter = comb.begin(); iter != comb.cend(); iter++)
        // {
        //     for(int i = 0; i < iter->second.size(); i++)
        //     {
        //         cout << iter->second[i] << " ";
        //     }
        //     cout << endl;
        // }

        for (auto iter = comb.begin(); iter != comb.cend(); iter++)
        {
            string temp;
            for (int i = 0; i < iter->second.size(); i++)
            {
                temp += s[iter->second[i]];
            }
            sort(temp.begin(), temp.end());

            for (int i = 0; i < iter->second.size(); i++)
            {
                ret[iter->second[i]] = temp[i];
            }
        }

        return ret;
    }
};