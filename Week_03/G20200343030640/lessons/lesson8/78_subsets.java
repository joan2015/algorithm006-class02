import java.util.*;

// 78. 子集
// 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
// 说明：解集不能包含重复的子集。

// 
class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> ans = new ArrayList<>();
        if (nums == null){
            return ans;
        }
        dfs(ans, nums, new ArrayList<Integer>(), 0);
        return ans;
    }
    private void dfs(List<List<Integer>> ans, int[] nums, List<Integer> list, int index){
        // terminator
        if(index == nums.length){
            ans.add(new ArrayList<Integer>(list));
            return;
        }
        dfs(ans, nums, list, index+1); // not pick the number at this index
        list.add(nums[index]);
        dfs(ans, nums, list, index+1); // pick the number at this index
        //reverse the current state
        list.remove(list.size()-1);
    }
}