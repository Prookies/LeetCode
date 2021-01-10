#include <vector>
#include <string>

using std::string;
using std::to_string;
using std::vector;

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {
        vector<string> ret;
        int i = 0;
        int n = nums.size();
        while (i < n)
        {
            int low = i;
            i++;
            while (i < n && nums[i] == nums[i - 1] + 1)
            {
                i++;
            }

            int high = i - 1;
            string temp = to_string(nums[low]);
            if (low < high)
            {
                temp.append("->");
                temp.append(to_string(nums[high]));
            }
            ret.push_back(move(temp)); // 通过使用move，避免不必要的拷贝操作
        }

        return ret;
    }
};