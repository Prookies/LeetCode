#include <vector>

using std::vector;

class Solution1
{
public:
    // 只需要考虑个位数
    int getSingle(int val)
    {
        while (val > 10)
        {
            val %= 10;
        }

        return val;
    }

    vector<bool> prefixesDivBy5(vector<int> &A)
    {
        int n = A.size();
        vector<bool> ret(n, false);
        int num = 0;
        for (int i = 0; i < n; i++)
        {
            num = 2 * getSingle(num) + A[i];
            // cout << num << endl;
            if (num % 5 == 0)
            {
                ret[i] = true;
            }
        }

        return ret;
    }
};

class Solution2
{
public:
    vector<bool> prefixesDivBy5(vector<int> &A)
    {
        vector<bool> list;
        int prefix = 0;
        int length = A.size();
        for (int i = 0; i < length; i++)
        {
            prefix = ((prefix << 1) + A[i]) % 5;
            list.emplace_back(prefix == 0);
        }
        return list;
    }
};
