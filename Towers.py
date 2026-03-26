def solve():
    import bisect
    n = int(input())
    a = list(map(int, input().split()))
    towers = []
    for cube in a:
        idx = bisect.bisect_right(towers, cube)
        if idx < len(towers):
            towers[idx] = cube
        else:
            towers.append(cube)
    print(len(towers))
    
if __name__=="__main__":
    solve()                
        
