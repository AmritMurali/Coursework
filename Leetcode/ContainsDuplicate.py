# Amrit Murali, LeetCode 217.Contains Duplicate
# if the array contains a duplicate number, return true
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        s = set() # making a hashset
        for x in nums:
            if x in s:
                return True
            s.add(x)
        return False
        