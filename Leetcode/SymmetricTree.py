# Amrit Murali, Leetcode #101 Symmetric Tree
# Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).
class TreeNode: # defining a tree node for a binary search tree
  def __init__(self, val=0, left=None, right=None):
    self.val = val
    self.left = left
    self.right = right

# building bst from an array
def buildTree(nums):
  if not nums:
    return None
  root = TreeNode(nums[0])
  q = [root]
  i = 1
  while i < len(nums):
    curr = q.pop(0)
    if i < len(nums):
      curr.left = TreeNode(nums[i])
      q.append(curr.left)
      i += 1
    if i < len(nums):
      curr.right = TreeNode(nums[i])
      q.append(curr.right)
      i += 1
    return root

def isSymmetric(root):
  def helper(left, right):
    if left == None and right == None: # if its a leaf, return true
      return True
    elif left == None or right == None: # one side = assymmetric
      return False
    elif left.val == right.val: # if mirror nodes have same value, check if subtrees are symmetric
      return helper(left.left, right.right) and helper(left.right, right.left)
    else:
      return false
  return helper(root.left, root.right)

# Test Cases

root = buildTree([1,2,2,3,4,4,3])
print(isSymmetric(root)) # True

root2 = TreeNode(1)
print(isSymmetric(root2)) # True

root3 = TreeNode(1, None, TreeNode(2))
print(isSymmetric(root3)) # False

# Time Complexity: O(n) where n is the size of the nums array
# Space Complexity: O(n) if the tree is unbalanced and O(log(n)) if the tree is balanced (the call stack depth during recursion)

    