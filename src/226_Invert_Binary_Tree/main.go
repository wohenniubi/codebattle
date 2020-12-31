package main

import "fmt"

type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

func invertTree(root *TreeNode) *TreeNode {
    if root == nil {
        return root
    }
    lhs := invertTree(root.Right)
    rhs := invertTree(root.Left)
    //root.Left = rhs 大意啦大意啦
    //root.Right = lhs
    root.Left = lhs
    root.Right = rhs
    return root
}

func main() {
  root := TreeNode{4,nil,nil}
  rtn := invertTree(&root)
  fmt.Printf("expect result = 4, actual result = %d\n", rtn.Val)
}


