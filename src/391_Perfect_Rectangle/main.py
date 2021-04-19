
from typing import List

class Solution:
    # Runtime: 352 ms, faster than 71.54%
    # Memory Usage: 21.7 MB, less than 12.20%
    def isRectangleCover(self, rectangles: List[List[int]]) -> bool:
        # 分析一下behavior特性，一个矩形四个顶点，完美矩形的话，我们将所有顶点分为3类
        # 经由1个顶点的集合，size=4，每个顶点仅出现一次，且四个点能构成一个矩形
        # 经由2个顶点的集合，每个顶点的出现次数必定是2的倍数
        # 经由4个顶点的集合，每个顶点的出现次数必定是4的倍数

        def getArea(heads):
            minx, maxx = float('inf'), float('-inf')
            miny, maxy = float('inf'), float('-inf')

            for head in heads:
                minx = min(minx, head[0])
                maxx = max(maxx, head[0])
                miny = min(miny, head[1])
                maxy = max(maxy, head[1])
            return (maxx - minx) * (maxy - miny)

        helper = {}
        # 大意了，还需要加入面积来判断
        area = 0

        # 现在开始统计顶点
        for rect in rectangles:
            # 得到四个顶点的二维坐标
            x, y, a, b = rect
            topleft  = (x, b)
            topright = (a, b)
            botleft  = (x, y)
            botright = (a, y)
            area += (a - x) * (b - y)

            for point in [topleft, topright, botleft, botright]:
                if point in helper:
                    # helper.del(point) 语法错误
                    # del helper[point] # 必须保证point一定存在，这里适用
                    helper.pop(point, None) # 可以容许point不存在，这里也适用
                else:
                    helper[point] = 1

        if len(helper) != 4:
            return False

        # 要看四个点是否能够组成矩形；我觉得rectangles里面的数据能够保证是矩形吧
        # heads = [key for key, val in enumerate(helper)]
        # 还是对python不熟悉啊，这里仅仅遍历了主键，而且主键存储于‘val’里面，第一个'key'这里是index
        heads = [key for i, (key, val) in enumerate(helper.items())]
        # return True
        return getArea(heads) == area


if __name__ == "__main__":
    gua = Solution()
    rtn = gua.isRectangleCover(rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]])
    print("expect result = True, actual result = ", rtn)

    rtn = gua.isRectangleCover(rectangles=[[1,1,2,2],[1,1,2,2],[3,2,4,4]])
    print("expect result = False, actual result = ", rtn)

    rtn = gua.isRectangleCover(rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[2,2,4,4]])
    print("expect result = False, actual result = ", rtn)

    rtn = gua.isRectangleCover(rectangles = [[1,1,2,3],[1,3,2,4],[3,1,4,2],[3,2,4,4]])
    print("expect result = False, actual result = ", rtn)

    rtn = gua.isRectangleCover(rectangles = [[1,1,3,3],[3,1,4,2],[1,3,2,4],[3,2,4,4]])
    print("expect result = False, actual result = ", rtn)

