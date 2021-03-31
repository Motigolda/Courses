

public class Tester {
	
	public static void main(String[] args) {
		
		// Tests for isPositivePrime()
		reportTest(NumberUtils.isPositivePrime(7) == true, 1);    
		reportTest(NumberUtils.isPositivePrime(10) == false, 2);  

		

		// Test for factorial()
		reportTest(NumberUtils.factorial(4) == 24, 3); 
		
		// Tests for isPerfect()
		reportTest(NumberUtils.isPerfect(8) == false, 4);   
		reportTest(NumberUtils.isPerfect(28) == true, 5);   
		
		// Tests for printPerfects()
		reportTest(NumberUtils.getPerfects(1000).equals("6,28,496,"), 6);   
			
		// Tests for isSumDigits()
		reportTest(NumberUtils.isSumDigits(1234, 10) == true, 7);   
		reportTest(NumberUtils.isSumDigits(1234, 11) == false, 8); 

		// Test for isAscending()
		reportTest(NumberUtils.isAscending(1234) == true, 9); 
		

		// Test for areUniqueDigits()
		reportTest(NumberUtils.areUniqueDigits(1231) == false, 10); 
		reportTest(NumberUtils.areUniqueDigits(4321) == true, 11);  

		// Test for areDisjoint()
		reportTest(NumberUtils.areDisjoint(123, 45687) == true, 12);
		reportTest(NumberUtils.areDisjoint(1234, 45687) == false, 123);
		
		// Test for printNumberTriangle()
		NumberUtils.printNumberTriangle(3);
	}
	
	/**
	 * The method reports if the test failed or passed, according to the given condition.
	 * @param condition Condition to check. False value means that the test has failed.
	 * @param testNum Test number.
	 */
	private static void reportTest(boolean condition, int testNum) {
		if(! condition)
			System.err.println("FAILED TEST " + testNum + ".");
		else
			System.out.println("PASSED TEST " + testNum + ".");
	}
}
