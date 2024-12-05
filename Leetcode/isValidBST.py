# Amrit Murali, Leetcode #98 Validate Binary Search Tree
# Given the root of a binary tree, check whether it is a valid BST.
class TreeNode:  # defining a tree node for a binary search tree

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


def isValidBST(root):

  def helper(min, max, root):
    # is the tree empty
    if (root is None):
      return True
    # is current node is in min,max range
    if (min is not None and root.val <= min):
      return False
    if (max is not None and root.val >= max):
      return False
    # if it is a leaf, it is a BST
    if (root.left is None and root.right is None):
      return True
    # check subtrees
    return helper(min, root.val, root.left) and helper(root.val, max,
                                                       root.right)

  return helper(None, None, root)


# Test Cases

root = buildTree([1, 2, 2, 3, 4, 4, 3])
print(isValidBST(root))  # False

root2 = TreeNode(1)
print(isValidBST(root2))  # True

root3 = TreeNode(1, None, TreeNode(0))
print(isValidBST(root3))  # False

# Time Complexity: O(n) where n is the size of the nums array
# Space Complexity: O(n) if the tree is unbalanced and O(log(n)) if the tree is balanced (the call stack depth during recursion)