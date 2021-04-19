
from typing import List

class Solution:
    # Runtime: 60 ms, faster than 33.75%
    # Memory Usage: 14.9 MB, less than 35.12%
    def trap(self, height: List[int]) -> int:
        # 怎么感觉这是单调栈的问题呢
        st = []
        size = len(height)
        
        water = 0
        for i in range(size):
            # 硬指标：只有bar的高度大于才有可能接到雨水，然后水量还要考虑宽度和高度差
            bottom = 0 if not st else st[-1] # 因为每个bar高度非负，所以初始化为0
            while st and height[st[-1]] <= height[i]: # 带入数据发现应该要取等于
                # 以pop出来的那个较低bar的高度作为储水短板
                wide, tall = i-st[-1]-1, height[st[-1]] - bottom
                water += wide*tall 
                bottom = height[st[-1]] # 也相当于把这部分空缺填实心了
                st.pop(-1)
            
            # 跳出while循环说明当前是第一个或者最高的bar了——前面还有更高的
            # st.append(i) # 存入index要好一些；
            if st: # 大意了大意了，此时也可能再装一些水，例如[4,2,0,3,2,5], rtn = 9
                wide, tall = i-st[-1]-1, height[i] - bottom # 此时短板必然是当前板，因为前面的bar都被弹出了
                water += wide*tall
            st.append(i) # 存入index要好一些
        
        return water
    
if __name__ == "__main__":
    gua = Solution()
    rtn = gua.trap(height=[4,2,0,3,2,5])
    print("expect result = 9, actual result = ", rtn)

    rtn = gua.trap(height=[0,1,0,2,1,0,1,3,2,1,2,1])
    print("expect result = 6, actual result = ", rtn)

