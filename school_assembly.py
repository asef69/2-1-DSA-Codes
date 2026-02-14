from collections import deque

def solve():
    n = int(input())
    queue = deque()
    
    for i in range(n):
        operation = list(map(int, input().split()))
        a = operation[0]
        
        if a == 1:
            pos = operation[1]
            id = operation[2]
            if pos == 0:
                queue.appendleft(id)
            else:
                queue.append(id)
                
        elif a == 2:
            pos = operation[1]
            if pos == 0 and queue:
                queue.popleft()
            elif pos == 1 and queue:
                queue.pop()
                
    return queue

if __name__ == "__main__":
    result = solve()
    if result:
        print(' '.join(map(str, result)))
    else:
        print()