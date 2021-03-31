import java.util.Arrays;

public class MyTester {
	public static void main(String[] args) {
		boolean toStringTest = true;
		boolean absArrayTest = true;
		boolean fillAllTest = true;
		boolean fillRangeTest = true;
		boolean containsTest = true;
		boolean getMaxPositionTest = true;
		boolean getMultTest = true;
		boolean getReverseTest = true;
		boolean reverseTest = true;
		boolean findMaxTest = true;
		boolean sumTablesTest = true;

		// toString() tests:
		toStringTest &= test(ArrayUtils.toString(new int[]{1, 2, 3}), "[1, 2, 3]", "toString basic case failed");
		toStringTest &= test(ArrayUtils.toString(new int[] {}), "[]", "toString empty test failed");
		int[] arr = new int[3];
		arr[0] = 0;
		arr[2] = 5;
		toStringTest &= test(ArrayUtils.toString(arr), "[0, 0, 5]", "toString non-initialized slot failed");
		// absArray() tests:
		absArrayTest &= test(ArrayUtils.absArray(null), null, "abs null case test failed");
		absArrayTest &= test(ArrayUtils.absArray(new int[] {1,-2,3}), new int[] {1,2,3}, "abs basic case failed");
		absArrayTest &= test(ArrayUtils.absArray(new int[] {-55, 6, 70, -8, 0}), new int[] {55,6,70,8,0},"second abs case failed");
		absArrayTest &= test(ArrayUtils.absArray(new int[0]), new int[0], "abs empty case failed");
		// fill() - all array test:
		arr = new int[]{1,2,3};
		ArrayUtils.fill(arr, 1);
		fillAllTest &= arr[0] == 1 && arr[1] == 1 && arr[2] == 1;
		test(arr[0] == 1 && arr[1] == 1 && arr[2] == 1, true, "fill (All) 1,2,3 case failed");
		arr = new int[] {3,5,3};
		ArrayUtils.fill(arr, 7);
		fillAllTest &= arr[0] == 7 && arr[1] == 7 && arr[2] == 7;
		test(arr[0] == 7 && arr[1] == 7 && arr[2] == 7, true, "fill (All) second case failed");
		arr = null;
		ArrayUtils.fill(arr, 1);
		fillAllTest &= arr == null;
		test(arr == null, true, "fill (All) null case failed");
		arr = new int[] {};
		ArrayUtils.fill(arr, 1);
		fillAllTest &= arr.length == 0;
		test(arr.length == 0, true, "fill (All) empty case failed");
		// fill() - range test:
		arr = new int[] {5, 7, 1, 6, 8};
		int value = 3,
			start = 2,
			end   = 4;
		
		int[] excepted = new int[] {5,7,2,2,8};
		
		ArrayUtils.fill(arr, value, start, end);
		fillRangeTest &= test(Arrays.equals(arr, excepted), true, "fill (Range) regular test failed");
		arr = null;
		value = 6;
		start = 7;
		end   = 8;
		ArrayUtils.fill(arr, value, start, end);
		fillRangeTest &= test(arr, null, "fill (Range) null test failed");
		arr = new int[0];
		value = 6;
		start = 1;
		end  = 0;
		ArrayUtils.fill(arr, value, start, end);
		fillRangeTest &= test(arr, new int[0], "fill (Range) empty test failed");
		arr = new int[] {1,-2,3,-4,7};
		value = 0;
		start = 1;
		end = 3;
		excepted = new int[] {1,0,0,-4,7};
		ArrayUtils.fill(arr, value, start, end);
		fillRangeTest &= test(arr, excepted, "fill (Range) regular test failed");
		
		arr = new int[] {1,5,8,7,1};
		value = 10;
		start = 3;
		end = 10;
		excepted = arr.clone();
		ArrayUtils.fill(arr, value, start, end);
		fillRangeTest &= test(arr, excepted, "fill (Range) out of range test 1 failed");
		
		start = 10;
		end = 20;
		fillRangeTest &= test(arr, excepted, "fill (Range) out of range test 2 failed");
		
		arr = new int[] {1,5,9,3};
		value=9;
		start=1;
		end=1;
		excepted = arr.clone();
		ArrayUtils.fill(arr, value, start, end);
		fillRangeTest &= test(arr, excepted, "fill (Range) out of range test 3 failed");
		
		// containsTest() tests:
		containsTest &= test(ArrayUtils.contains(
													null, 
													new int[] {1,2,3}
												), 
							false, 
							"contains null test 1 failed");
		
		containsTest &= test(ArrayUtils.contains(
													new int[] {1, 2, 3}, 
													null
												), 
							false, 
							"contains null test 2 failed");
		
		containsTest &= test(ArrayUtils.contains(
													new int[] {1, 7, 4, 5, 9}, 
													new int[] {7, 4, 5}
												), 
							true, 
							"contains regular test 1 failed");
		
		containsTest &= test(ArrayUtils.contains(
													new int[] {1, 7, 9, 8},
													new int[] {90}
												),
							false,
							"contains regular test 2 failed");
		
		containsTest &= test(ArrayUtils.contains(
													new int[] {1, 8, 3},
													new int[] {}
												),
							false,
							"contains empty test 1 failed");
		
		containsTest &= test(ArrayUtils.contains(
													new int[] {},
													new int[] {1, 2, 3}
												),
							false,
							"contains empty test 2 failed");
		
		
		// getMaxPositionTest() tests:
		getMaxPositionTest &= test(ArrayUtils.getMaxPosition(new int[] {1, 3, 7, 9, 3}), 
							3,
							"getMaxPosition regular test failed");
		
		getMaxPositionTest &= test(ArrayUtils.getMaxPosition(new int[] {}), 
				-1,
				"getMaxPosition empty test failed");

		getMaxPositionTest &= test(ArrayUtils.getMaxPosition(null), 
				-1,
				"getMaxPosition null test failed");

		getMaxPositionTest &= test(ArrayUtils.getMaxPosition(new int[] {9, 9, 7, 9, 8}), 
				0,
				"getMaxPosition repeat test failed");

		
		// getMultTest() tests:
		getMultTest &= test(ArrayUtils.getMult(null), Integer.MAX_VALUE, "getMult null test failed");
		getMultTest &= test(ArrayUtils.getMult(new int[]{}), Integer.MAX_VALUE, "getMult null test failed");
		getMultTest &= test(ArrayUtils.getMult(new int[] {1, 2, 7}), 14, "getMult regular test 1 failed");
		getMultTest &= test(ArrayUtils.getMult(new int[] {0, 9, 1, 8}), 0, "getMult zero test failed");
		getMultTest &= test(ArrayUtils.getMult(new int[] {9, 8, 70}), 5040, "getMult regular test 2 failed");		
		
		// getReverseTest() tests:
		getReverseTest &= test(ArrayUtils.getReverse(null), null, "getReverse null test failed");
		getReverseTest &= test(ArrayUtils.getReverse(new int[]{}), new int[]{}, "getReverse empty test failed", true);
		getReverseTest &= test(ArrayUtils.getReverse(new int[]{7, 8, 5, 9}), new int[]{9 ,5, 8, 7}, "getReverse regular test 1 failed", true);
		getReverseTest &= test(ArrayUtils.getReverse(new int[]{100, 0, 60, 9}), new int[]{9, 60, 0, 100}, "getReverse regular test 2 failed", true);
		// reverseTest() tests:
		arr = null;
		ArrayUtils.reverse(arr);
		reverseTest &= test(arr == null, true, "reverse null test failed");
		arr = new int[] {};
		ArrayUtils.reverse(arr);
		reverseTest &= test(Arrays.equals(arr, new int[] {}), true, "reverse empty test failed");
		arr = new int[] {1, 7, 4, 9};
		ArrayUtils.reverse(arr);
		reverseTest &= test(Arrays.equals(arr, new int[] {9, 5, 8, 7}), true, "reverse even test failed");
		arr = new int[] {8, 9, 4, 7, 1};
		ArrayUtils.reverse(arr);
		reverseTest &= test(Arrays.equals(arr, new int[] {1, 7, 4, 9, 8}), true, "reverse odd test failed");	
		
		// findMaxTest() tests:
		
		findMaxTest &= test(ArrayUtils.findMax(null), null, "findMax null test failed");
		findMaxTest &= test(ArrayUtils.findMax(new int[][] {}), null, "findMax empty test 1 failed");
		findMaxTest &= test(ArrayUtils.findMax(new int[][] {{1, 2, 3}, {4, 5, 1}}), new int[] {1,1}, "findMax regular test 1 failed", true);
		findMaxTest &= test(ArrayUtils.findMax(new int[][] {{1,2},{5,2},{90,8}}), new int[] {2, 0}, "findMax regular test 2 failed", true);
		findMaxTest &= test(ArrayUtils.findMax(new int[0][100]), null, "findMax empty test 2 failed");
		
		// sumTablesTest() tests:
		
		sumTablesTest &= test(ArrayUtils.sumTables(new int[][] {{1, 2},{3,4}}, null), null, "sumTables null test 1 failed", true);
		sumTablesTest &= test(ArrayUtils.sumTables(null, new int[][] {{1, 2},{3}}), null, "sumTables null test 2 failed", true);	
		int[][] table1 = {
				{1, 2},
				{3, 4}
		},
		table2 = {
				{5,6},
				{7,8}
		},
		exceptedOutput = {
				{6,8},
				{10,12}
		};
		sumTablesTest &= test(ArrayUtils.sumTables(table1, table2), exceptedOutput, "sumTables regular test failed");	
		
		table1 = new int[][]{
				{4, 5, 6},
				{7, 8, 9}
		};
		table2 = new int[][] {
			{1,2},
			{3, 4}
		};
		sumTablesTest &= test(ArrayUtils.sumTables(table1, table2), null, "sumTables not same size test failed");
		
		table1 = new int[][] {};
		table2 = new int[][] {};
		exceptedOutput = new int[][] {};
		sumTablesTest &= test(ArrayUtils.sumTables(table1, table2), exceptedOutput, "sumTables empty test failed");	
		// Table
		System.out.println("\nsuccess table:\n----------------------");
		System.out.print("toStringTest:\t\t"); printTestResult(toStringTest, true);
		System.out.print("absArrayTest:\t\t"); printTestResult(absArrayTest, true);
		System.out.print("fillAllTest:\t\t"); printTestResult(fillAllTest, true);
		System.out.print("fillRangeTest:\t\t"); printTestResult(fillRangeTest, true);
		System.out.print("containsTest:\t\t"); printTestResult(containsTest, true);
		System.out.print("getMaxPositionTest:\t"); printTestResult(getMaxPositionTest, true);
		System.out.print("getMultTest:\t\t"); printTestResult(getMultTest, true);
		System.out.print("getReverseTest:\t\t"); printTestResult(getReverseTest, true);
		System.out.print("reverseTest:\t\t"); printTestResult(reverseTest, true);
		System.out.print("findMaxTest:\t\t"); printTestResult(findMaxTest, true);
		System.out.print("sumTablesTest:\t\t"); printTestResult(sumTablesTest, true);
	}
	
	public static boolean test(Object output, Object exceptedOutput, String failMessage) {
		boolean success = true;
		if(output == null && exceptedOutput == null) {
			return true;
		}
		else if (output == null && exceptedOutput != null || output != null && exceptedOutput == null){
			success = false; 
		}
		
		if (!success || !output.equals(exceptedOutput)) {
			if (exceptedOutput == null)
				exceptedOutput = new String("Null");
			if (output == null)
				output = new String("Null");			
			System.err.println("\n+----+\nTest failed.\nexcepted output: " +
								exceptedOutput.toString() + 
								"\noutput: " + output.toString());
			if(failMessage != null)
				System.err.println(failMessage);
			return false;
		}
		return true;
	}
	
	public static boolean test(int[] output, int[] exceptedOutput, String failMessage, boolean t) {

		if (!Arrays.equals(output, exceptedOutput)) {
			if(exceptedOutput == null)
				System.err.println("\n+----+\nTest failed.\nexcepted output: null" +
									"\noutput: " + output.toString());
			else
				System.err.println("\n+----+\nTest failed.\nexcepted output: " +
						exceptedOutput.toString() + 
						"\noutput: " + output.toString());
			if(failMessage != null)
				System.err.println(failMessage);
			return false;
		}
		return true;
	}
	public static boolean test(int[][] output, int[][] exceptedOutput, String failMessage, boolean t) {

		if (!Arrays.equals(output, exceptedOutput)) {
			if(exceptedOutput == null)
				System.err.println("\n+----+\nTest failed.\nexcepted output: null" +
									"\noutput: " + output.toString());
			else
				System.err.println("\n+----+\nTest failed.\nexcepted output: " +
						exceptedOutput.toString() + 
						"\noutput: " + output.toString());
			if(failMessage != null)
				System.err.println(failMessage);
			return false;
		}
		return true;
	}
	public static boolean test(Object output, Object exceptedOutput) {
		return test(output, exceptedOutput, null);
	}

	public static void printTestResult(boolean success, boolean newLine) {
		if (success)
			print(true);
		else
			printError(false);
		if (newLine)
			print("\n");
	}
	synchronized public static void print(Object obj) {
		System.out.print(obj);
	}
	synchronized public static void println(Object obj) {
		System.out.println(obj);
	}
	synchronized public static void printError(Object obj) {
		System.err.print(obj);
	}
}
