#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using ll=long long ;
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update> orderedMultiset;
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> a1(1, nums[0]), a2(1, nums[1]);
        orderedMultiset st1, st2;
        st1.insert(nums[0]);
        st2.insert(nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            //count the number of elem in st1 smaller than nums[i]+1;
            int a = st1.size() - st1.order_of_key(nums[i] + 1);
            int b = st2.size() - st2.order_of_key(nums[i] + 1);
            if (a > b) {
                a1.push_back(nums[i]);
                st1.insert(nums[i]);
            } 
            else if (b > a) {
                a2.push_back(nums[i]);
                st2.insert(nums[i]);
            } 
            else {
                if (a1.size() > a2.size()) {
                    {
                        a2.push_back(nums[i]);
                        st2.insert(nums[i]);
                    }
                } 
                else {
                    a1.push_back(nums[i]);
                    st1.insert(nums[i]);
                }
            }
        }
        a1.insert(a1.end(), a2.begin(), a2.end());
        return a1;
    }
};