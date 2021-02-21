/* ------------------------------------------------------------------|
给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。

如果不存在满足条件的子数组，则返回 0 。

 

示例 1：

输入：nums = [8,2,4,7], limit = 4
输出：2
解释：所有子数组如下：
[8] 最大绝对差 |8-8| = 0 <= 4.
[8,2] 最大绝对差 |8-2| = 6 > 4.
[8,2,4] 最大绝对差 |8-2| = 6 > 4.
[8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
[2] 最大绝对差 |2-2| = 0 <= 4.
[2,4] 最大绝对差 |2-4| = 2 <= 4.
[2,4,7] 最大绝对差 |2-7| = 5 > 4.
[4] 最大绝对差 |4-4| = 0 <= 4.
[4,7] 最大绝对差 |4-7| = 3 <= 4.
[7] 最大绝对差 |7-7| = 0 <= 4.
因此，满足题意的最长子数组的长度为 2 。
示例 2：

输入：nums = [10,1,2,4,7,2], limit = 5
输出：4
解释：满足题意的最长子数组是 [2,4,7,2]，其最大绝对差 |2-7| = 5 <= 5 。
示例 3：

输入：nums = [4,2,2,2,4,4,2,2], limit = 0
输出：3
 

提示：

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9
0 <= limit <= 10^9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。|
-------------------------------------------------------------------*/

/*
*
*	执行用时：120 ms, 在所有 C++ 提交中击败了94.57%的用户
*	内存消耗：50.8 MB, 在所有 C++ 提交中击败了76.45%的用户
*/

#include <iostream>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <stack>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}

};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

int longestSubarray(vector<int>& nums, int limit) {
    //两个双向队列，存放l和r之间的最大最小值
    deque<int> minVal, maxVal;
    int l = 0;
    int r = 0;
    int res = 0;
    while (r < nums.size()) {
        //保证队首是当前l-r之间的最大、最小值
        while (!minVal.empty() && nums[r] < minVal.back()) {
            minVal.pop_back();
        }
        while (!maxVal.empty() && nums[r] > maxVal.back()) {
            maxVal.pop_back();
        }
        //填入当前值
        minVal.emplace_back(nums[r]);
        maxVal.emplace_back(nums[r]);

        //将注释取消就要改成while，用if就是直接取得最大窗口，只减不增
        if (!minVal.empty() && !maxVal.empty() && maxVal.front() - minVal.front() > limit) {
            if (nums[l] == maxVal.front()) {
                maxVal.pop_front();
            }
            if (nums[l] == minVal.front()) {
                minVal.pop_front();
            }
            l++;
        }
        //res = max(res, r - l + 1);
        r++;
    }
    return r - l;
}

int main() {
    vector<int> nums = { 10,1,2,4,7,2 };
    longestSubarray(nums, 5);
}