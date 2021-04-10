
from typing import List

class Solution:
    #Runtime: 140 ms, faster than 95.60%
    #Memory Usage: 15.1 MB, less than 56.25%
    def intervalIntersection(self, firstList: List[List[int]], secondList: List[List[int]]) -> List[List[int]]:
        # 因为已经排过序，且两个list内部的interval之间均没有joint，那么貌似就是直接遍历
        size1, size2 = len(firstList), len(secondList)
        
        pos1, pos2 = 0, 0
        rtn = []
        while pos1 < size1 and pos2 < size2:
            if firstList[pos1][0] <= secondList[pos2][0]:
                lhs = secondList[pos2][0]
                # 交集之后，左边界都以secondList[pos2]为准
                # A.begin ----- A.end
                # B.begin -- B.end
                #   B.begin - B.end
                #       B.begin - B.end
                #                       B.begin - B.end
                rhs = min(firstList[pos1][1], secondList[pos2][1])
                if rhs < lhs:
                    # 没有交集，必定是A较小，移动A
                    pos1 += 1
                else:
                    rtn.append([lhs, rhs])
                    if rhs == firstList[pos1][1]:
                        pos1 += 1
                    if rhs == secondList[pos2][1]:
                        pos2 += 1
            else:
                # 此时左边界都以firstList[pos1]为准
                lhs = firstList[pos1][0]
                rhs = min(firstList[pos1][1], secondList[pos2][1])
                if rhs < lhs:
                    # 没有交集，必定是B较小，移动B
                    pos2 += 1
                else:
                    rtn.append([lhs, rhs])
                    # 较小的右移，才有可能继续发现交集
                    if rhs == firstList[pos1][1]:
                        pos1 += 1
                    if rhs == secondList[pos2][1]:
                        pos2 += 1
        
        return rtn

if __name__ == "__main__":
    gua = Solution()
    rtn = gua.intervalIntersection(firstList=[[0,2],[5,10],[13,23],[24,25]],
                   secondList=[[1,5],[8,12],[15,24],[25,26]])
    print("expect result = [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]], actual result = ", rtn)

    rtn = gua.intervalIntersection(firstList=[],
                   secondList=[[1,3],[5,9]])
    print("expect result = [[]], actual result = ", rtn)

    rtn = gua.intervalIntersection(firstList=[[1,7]], secondList=[[5,10]])
    print("expect result = [[5,7]], actual result = ", rtn)

