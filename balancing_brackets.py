def balancing_brackets(s):
    stack=[]
    unmatched_close = 0
    
    for char in s:
        if char == '(':
            stack.append(char)
        elif char == ')':
            if stack:
                stack.pop()
            else:
                unmatched_close += 1
            
    return len(stack) + unmatched_close

if __name__ == "__main__":
    s = input().strip()
    result = balancing_brackets(s)
    print(result)        