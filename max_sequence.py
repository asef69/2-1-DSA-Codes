def lexicographical_subsequence(s):
    n = len(s)
    if n == 0:
        return ""
    
    result = []
    i = 0
    
    while i < n:
        
        min_char = min(s[i:])
        
  
        j = i
        while j < n and s[j] != min_char:
            j += 1
        
        result.append(min_char)
        i = j + 1
    
    return ''.join(result)


if __name__ == "__main__":
    s = input().strip()
    result = lexicographical_subsequence(s)
    print(result)