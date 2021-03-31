
public class Tester {
	private static int numFailed = 0;
	private static int numSuccess = 0;
	
	public static void main(String[] args) {
		int[] arr = {1, -3, 5, 6,  0, -4};
		String arrStr = ArrayUtils.toString(arr);
		reportTest(arrStr.equals("[1, -3, 5, 6, 0, -4]"), 1);
		
		int[] abs = ArrayUtils.absArray(arr);
		arrStr = ArrayUtils.toString(arr);
		String absStr = ArrayUtils.toString(abs);
		reportTest(arrStr.equals("[1, -3, 5, 6, 0, -4]"), 2);
		reportTest(absStr.equals("[1, 3, 5, 6, 0, 4]"), 3);
		
		int[] arr2 = {1, -3, 5, 6,  0, -4};
		ArrayUtils.fill(arr2, 0);
		String arr2Str = ArrayUtils.toString(arr2);
		reportTest(arr2Str.equals("[0, 0, 0, 0, 0, 0]"), 4);
		
		int[] arr3 = {1, -3, 5, 6,  9, -4};
		ArrayUtils.fill(arr3, 0, 1, 4);
		String arr3Str = ArrayUtils.toString(arr3);
		reportTest(arr3Str.equals("[1, 0, 0, 0, 9, -4]"), 5);
		
		int[] arr4 = {1, 2, 3};
		int[] arr5 = {1, 2, 3, 4};
		reportTest(ArrayUtils.contains(arr4, arr5) == false, 6);
		reportTest(ArrayUtils.contains(arr5, arr4) == true, 7);
		
		int[] arr6 = {1, -3, 5, 6,  9, -4};
		int[] arr6Reversed = ArrayUtils.getReverse(arr6);
		String arr6ReversedStr = ArrayUtils.toString(arr6Reversed);
		reportTest(arr6ReversedStr.equals("[-4, 9, 6, 5, -3, 1]"), 8);
		
		int[] arr7 = {1, -3, 5, 6,  9, -4};
		ArrayUtils.reverse(arr7);
		String arr7Str = ArrayUtils.toString(arr7);
		reportTest(arr7Str.equals("[-4, 9, 6, 5, -3, 1]"), 9);
		
		int[] arr8 = {1, -3, 5, 6,  9, -4};
		int maxPos = ArrayUtils.getMaxPosition(arr8);
		reportTest(maxPos == 4, 10);
		
		int[] arr9 = {1, 2, 3};
		int mult = ArrayUtils.getMult(arr9);
		reportTest(mult == 6, 11);
		
		int[][] arr10 = {{1, 4, 2}, {16, 9 , 0}};
		int[] res = ArrayUtils.findMax(arr10);
		reportTest(res[0] == 1, 12);
		reportTest(res[1] == 0, 13);
		
		int[][] arr11 = {{1, 4}, 
						  {16, 0}};
		int[][] arr12 = {{0, 6},
					      {4, 9}};
		int[][] resSum = ArrayUtils.sumTables(arr11, arr12);
		reportTest(resSum[0][0] == 1, 14);
		reportTest(resSum[0][1] == 10, 15);
		reportTest(resSum[1][0] == 20, 16);
		reportTest(resSum[1][1] == 9, 17);
		
		
		System.out.println("num. test failed: " +  numFailed);
		System.out.println("num. test passed: " + numSuccess);
		
		System.out.println("Done!");
	}
	
	
	/**
	 * The method reports if the test failed or passed, according to the given condition.
	 * @param condition Condition to check. False value means that the test has failed.
	 * @param testNum Test number.
	 */
	private static void reportTest(boolean condition, int testNum) {
		if(! condition) {
			System.err.println("FAILED TEST " + testNum + ".");
			numFailed++;
		}
		else {
			System.out.println("PASSED TEST " + testNum + ".");
			numSuccess++;
		}
	}
}
