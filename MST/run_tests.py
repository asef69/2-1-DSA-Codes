import subprocess
import os
import re

def extract_mst_output(full_output):
    """Extract MST results from full program output."""
    lines = full_output.strip().split('\n')
    mst_start = -1
    
    # Find the line that starts with "Total weight"
    for i, line in enumerate(lines):
        if line.strip().startswith("Total weight"):
            mst_start = i
            break
    
    if mst_start == -1:
        return full_output.strip()
    
    # Return from the MST start to the end
    return '\n'.join(lines[mst_start:]).strip()

def parse_edges(output):
    """Parse edges from output, handling any format."""
    edges = set()
    lines = output.strip().split('\n')
    
    # Skip header lines (total weight and root node)
    for line in lines[2:]:
        line = line.strip()
        if line:
            # Extract all numbers from the line
            numbers = re.findall(r'\d+', line)
            if len(numbers) >= 2:
                u, v = sorted([int(numbers[0]), int(numbers[1])])
                edges.add((u, v))
    
    return edges

def compare_outputs(actual_output, expected_output, test_name):
    """Compare actual and expected outputs."""
    # Extract MST portion from actual output
    actual_mst = extract_mst_output(actual_output)
    
    # Compare the complete MST output first (exact match)
    if actual_mst == expected_output:
        return True, "✅ Exact match!"
    
    # Parse edges for more detailed comparison
    actual_edges = parse_edges(actual_mst)
    expected_edges = parse_edges(expected_output)
    
    # Compare edge sets
    if actual_edges == expected_edges:
        return True, "✅ Edge sets match (format difference only)"
    
    # Get differences
    missing_edges = expected_edges - actual_edges
    extra_edges = actual_edges - expected_edges
    
    error_msg = "❌ Edge sets don't match\n"
    if missing_edges:
        error_msg += f"   Missing edges: {sorted(missing_edges)[:5]}\n"
        if len(missing_edges) > 5:
            error_msg += f"   ... and {len(missing_edges) - 5} more\n"
    
    if extra_edges:
        error_msg += f"   Extra edges: {sorted(extra_edges)[:5]}\n"
        if len(extra_edges) > 5:
            error_msg += f"   ... and {len(extra_edges) - 5} more\n"
    
    return False, error_msg

def get_total_weight(output):
    """Extract total weight from output."""
    lines = output.strip().split('\n')
    if lines and lines[0].strip().startswith("Total weight"):
        try:
            return int(re.search(r'\d+', lines[0]).group()) # type: ignore
        except:
            return None
    return None

def get_root_node(output):
    """Extract root node from output."""
    lines = output.strip().split('\n')
    if len(lines) > 1 and lines[1].strip().startswith("Root node"):
        try:
            return int(re.search(r'\d+', lines[1]).group()) # type: ignore
        except:
            return None
    return None

def analyze_failure(actual_output, expected_output, test_name):
    """Analyze and display detailed differences."""
    print(f"\n{'='*80}")
    print(f"FAILED TEST: {test_name}")
    print(f"{'='*80}")
    
    actual_mst = extract_mst_output(actual_output)
    actual_lines = actual_mst.split('\n')
    expected_lines = expected_output.split('\n')
    
    # 1. Compare total weight
    actual_weight = get_total_weight(actual_mst)
    expected_weight = get_total_weight(expected_output)
    
    if actual_weight != expected_weight:
        print(f"\n❌ TOTAL WEIGHT MISMATCH:")
        print(f"   Expected: {expected_weight}")
        print(f"   Got:      {actual_weight}")
        if actual_weight is not None and expected_weight is not None:
            diff = actual_weight - expected_weight
            if diff > 0:
                print(f"   Your MST is {diff} heavier")
            elif diff < 0:
                print(f"   Your MST is {-diff} lighter")
    
    # 2. Compare root node
    actual_root = get_root_node(actual_mst)
    expected_root = get_root_node(expected_output)
    
    if actual_root != expected_root:
        print(f"\n❌ ROOT NODE MISMATCH:")
        print(f"   Expected: {expected_root}")
        print(f"   Got:      {actual_root}")
    
    # 3. Compare edges
    actual_edges = parse_edges(actual_mst)
    expected_edges = parse_edges(expected_output)
    
    print(f"\n📊 EDGE COMPARISON:")
    print(f"   Expected edges: {len(expected_edges)}")
    print(f"   Actual edges:   {len(actual_edges)}")
    
    missing_edges = expected_edges - actual_edges
    extra_edges = actual_edges - expected_edges
    
    if missing_edges:
        print(f"\n❌ Missing edges ({len(missing_edges)}):")
        for edge in sorted(missing_edges)[:10]:
            print(f"   {edge[0]} - {edge[1]}")
        if len(missing_edges) > 10:
            print(f"   ... and {len(missing_edges) - 10} more")
    
    if extra_edges:
        print(f"\n❌ Extra edges ({len(extra_edges)}):")
        for edge in sorted(extra_edges)[:10]:
            print(f"   {edge[0]} - {edge[1]}")
        if len(extra_edges) > 10:
            print(f"   ... and {len(extra_edges) - 10} more")
    
    # 4. Check if valid MST (n-1 edges)
    try:
        with open(test_name, 'r') as f:
            first_line = f.readline().strip()
            n = int(first_line.split()[0])
        
        print(f"\n📐 GRAPH INFO:")
        print(f"   n = {n} vertices")
        print(f"   MST should have {n-1} edges")
        
        if len(actual_edges) == n-1:
            print(f"   ✅ Your MST has correct number of edges")
        else:
            print(f"   ❌ Your MST has {len(actual_edges)} edges, expected {n-1}")
            
        if len(expected_edges) == n-1:
            print(f"   ✅ Expected MST has correct number of edges")
        else:
            print(f"   ⚠️  Expected MST has {len(expected_edges)} edges, expected {n-1}")
            
    except Exception as e:
        pass
    
    print(f"\n📋 SUMMARY:")
    print(f"   Expected edges: {sorted(expected_edges)}")
    print(f"   Your edges:     {sorted(actual_edges)}")

def run_program(test_file):
    """Run the program and capture output."""
    if not os.path.exists(test_file):
        return None
    
    with open(test_file, 'r') as f:
        result = subprocess.run(["./prim"], stdin=f, capture_output=True, text=True)
    
    return result.stdout.strip()

def main():
    # Compile the program
    print("🔧 Compiling offline_prim.cpp...")
    result = subprocess.run(["g++", "-o", "prim", "-std=c++11", "offline_prim.cpp"], 
                          capture_output=True, text=True)
    
    if result.returncode != 0:
        print("❌ Compilation failed!")
        print(result.stderr)
        return
    
    print("✅ Compilation successful!\n")
    
    # Test cases
    test_cases = [
        ("test1.txt", "out1.txt"),
        ("test2.txt", "out2.txt"),
        ("test3.txt", "out3.txt"),
        ("test4.txt", "out4.txt"),
        ("test5.txt", "out5.txt"),
        ("test6.txt", "out6.txt"),
        ("test7.txt", "out7.txt"),
        ("test8.txt", "out8.txt"),
        ("test9.txt", "out9.txt"),
        ("test10.txt", "out10.txt"),
    ]
    
    results = []
    
    for i, (test_file, expected_file) in enumerate(test_cases, 1):
        print(f"\n{'='*60}")
        print(f"TEST {i}: {test_file}")
        print(f"{'='*60}")
        
        # Check if files exist
        if not os.path.exists(test_file):
            print(f"❌ Test file {test_file} not found!")
            results.append(False)
            continue
        
        if not os.path.exists(expected_file):
            print(f"❌ Expected output file {expected_file} not found!")
            results.append(False)
            continue
        
        # Run program
        actual_output = run_program(test_file)
        if actual_output is None or actual_output == "":
            print("❌ Program produced no output!")
            results.append(False)
            continue
        
        # Read expected output
        with open(expected_file, 'r') as f:
            expected_output = f.read().strip()
        
        # Compare outputs
        success, message = compare_outputs(actual_output, expected_output, test_file)
        
        if success:
            print(f"✅ PASSED - {message}")
            results.append(True)
        else:
            print(f"❌ FAILED - {message}")
            results.append(False)
            
            # Show weight comparison
            actual_mst = extract_mst_output(actual_output)
            actual_weight = get_total_weight(actual_mst)
            expected_weight = get_total_weight(expected_output)
            
            if actual_weight is not None and expected_weight is not None:
                print(f"   Your weight:     {actual_weight}")
                print(f"   Expected weight: {expected_weight}")
            
            # Ask if user wants detailed analysis
            choice = input("\n🔍 Show detailed analysis? (y/n): ").lower()
            if choice == 'y':
                analyze_failure(actual_output, expected_output, test_file)
    
    # Summary
    print(f"\n{'='*80}")
    print("TEST SUMMARY")
    print(f"{'='*80}")
    
    passed = sum(results)
    total = len(results)
    
    print(f"Passed: {passed}/{total}")
    print(f"Failed: {total - passed}/{total}")
    
    if passed < total:
        print(f"\n❌ Failing tests:")
        for i, (test_file, _) in enumerate(test_cases):
            if not results[i]:
                print(f"  - {test_file}")
    else:
        print("\n🎉 All tests passed! Your implementation is correct!")
    
    print(f"\n{'='*80}")

if __name__ == "__main__":
    main()