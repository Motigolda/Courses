
public class ArrayUtils {
	public static String toString(int[] arr) {
		if (isNull(arr))
			return null;
		
		if (isIntArrayEmpty(arr))
			return "[]";
		
		String innerPart = "";
		for (int i = 0; i < arr.length; i++)
			innerPart += arr[i] + ", ";

		innerPart = innerPart.substring(0, innerPart.length() - 2);
		
		return "[" + innerPart + "]";
	}
	
	public static int[] absArray(int[] arr) {
		if(isNull(arr))
			return null;
		
		if(isIntArrayEmpty(arr))
			return new int[0];
		
		int[] retArray = new int[arr.length];
		
		for (int i = 0; i < arr.length; i++)
			retArray[i] = Math.abs(arr[i]);
		
		return retArray;
		
	}
	
	public static void fill(int[] arr, int value) {
		if(isNull(arr) || isIntArrayEmpty(arr))
			return;
		
		for (int i = 0; i < arr.length; i++)
			arr[i] = value;
	}
	
	public static void fill(int[] arr, int value, int start, int end) 
	{
		if(isNull(arr) || isIntArrayEmpty(arr))
			return;
		
		if(end <= start || start >= arr.length || end > arr.length)
			return;
		
		for (int i = start; i < end; i++)
			arr[i] = value;
	}
	
	public static boolean contains(int[] arr1, int[] arr2) {
		if(isNull(arr1) || isNull(arr2) || isIntArrayEmpty(arr2))
			return false;
		
		for (int i = 0; i < arr2.length; i++)
			if(!contains(arr1, arr2[i]))
				return false;
		
		return true;
	}
	
	public static int getMaxPosition(int[] arr) {
		if(isNull(arr) || isIntArrayEmpty(arr))
			return -1;
		
		int maxNumberIndex = 0,
			biggestNumber = Integer.MIN_VALUE;
		
		for (int i = 0; i < arr.length; i++) {
			if (arr[i] > biggestNumber)
			{
				maxNumberIndex = i;
				biggestNumber = arr[i];
			}
		}

		return maxNumberIndex;
	}
	
	public static int getMult(int[] arr) {
		if(isNull(arr) || isIntArrayEmpty(arr))
			return Integer.MAX_VALUE;
		
		int mult = 1;
		for (int i = 0; i < arr.length; i++)
			mult *= arr[i];
		
		return mult;
	}
	
	public static int[] getReverse(int[] arr) {
		if(isNull(arr))
			return null;
		
		if(isIntArrayEmpty(arr))
			return new int[0];
		
		int[] retArray = arr.clone();
		reverse(retArray);
		
		return retArray;
	}
	
	public static void reverse(int[] arr) {
		if(isNull(arr))
			return;
		
		if (isIntArrayEmpty(arr))
			return;
		
		int swap;
		
		for (int i = 0; i < arr.length / 2; i++) {
			swap = arr[i];
			arr[i] = arr[arr.length - i - 1];
			arr[arr.length - i - 1] = swap;
		}
		
	}
	
	public static int[] findMax(int[][] arr) {
		if(isNull(arr) || arr.length == 0 || arr[0].length == 0)
			return null;
		
		int biggestNumber = Integer.MIN_VALUE;
		int[] biggestNumberIndex = new int[2];
		for (int i = 0; i<arr.length; i++) {
			for (int j = 0; j < arr[i].length; j++) {
				if(arr[i][j] > biggestNumber) {
					biggestNumber = arr[i][j];
					biggestNumberIndex[0] = i;
					biggestNumberIndex[1] = j;
				}
			}
		}
		
		
		return biggestNumberIndex;
	}
	
	public static int[][] sumTables(int[][] table1, int[][] table2) {
		if (isNull(table1) 
				|| isNull(table2)
				|| isIntArrayEmpty(table1)
				|| table1.length != table2.length 
				|| table1[0].length != table2[0].length)
			return null;
		
		int[][] sumTable = new int[table1.length][table1[0].length];
		for (int i = 0; i < sumTable.length; i++)
			for (int j = 0; j < sumTable[0].length; j++)
				sumTable[i][j] = table1[i][j] + table2[i][j];
		
		
		return sumTable;
	}
	
	// private methods
	private static boolean isNull(int[][] arr) {
		return arr == null;
	}
	private static boolean isNull(int[] arr) {
		return arr == null;
	}
	private static boolean isIntArrayEmpty(int[] array) {
		return array.length == 0;
	}
	private static boolean isIntArrayEmpty(int[][] array) {
		return array.length == 0;
	}
	private static boolean contains(int[] arr, int value) {
		if(isNull(arr))
			return false;
		
		for(int i = 0; i < arr.length; i++)
			if (arr[i] == value)
				return true;
		
		return false;
	}
}
