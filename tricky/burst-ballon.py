'''
- There is list of height of balloons from left to right
- We need to find minimum number of arrows needed to burst all ballons
- Arrows are shoot from left to right at a particular height
- When an arrow hits a balloon, it's height will reduce by one and it can burst another balloon to the lower (h -1) height, if it exists
  So single arrow can burst many balloons
'''
from typing import List
def minimumArrows(nums: List[int])-> int:
    burst = {} # lastBurst, count
    for n in nums:
        if not n in burst:
            burst[n] = 0

        burst[n] += 1
        if (n+1) in burst:
            burst[n+1] -= 1
            if burst[n+1] == 0:
                del burst[n+1]
    return sum(burst.values())
    
TCs = [[3,2,1],
        [1,2,3],
        [3,2,2,1],
        [2,4,5,6,4]]
for arr in TCs:
    print (arr, minimumArrows(arr))
