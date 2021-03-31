
public class NumberUtils {
	// Prime checker
	public static boolean isPositivePrime(int number) {
		if (number < 2)
			return false;
		if (number == 2 || number == 3)
			return true;
		if (number % 2 == 0)
			return false;
		
		for (int i = 3; i < Math.sqrt(number) + 2; i+=2)
			if (number % i == 0)
				return false;
		
		return true;
	}
	// Recursive factorial calculation
	public static int factorial(int number) {
		if (number < 1)
			return -1;
		
		if (number == 1)
			return 1;
		
		return number * factorial(number - 1);
	}
	
	public static boolean isPerfect(int number) {
		if (number < 1)
			return false;
		
		int sumOfDivisors = 0;
		for (int i = number / 2; i > 0; i--)
			if (number % i == 0 )
				sumOfDivisors += i;

		return number == sumOfDivisors;
	}
	
	public static String getPerfects(int number) {
		String strReturn = "";
		
		if (number < 1)
			return strReturn;

		for (int i = 1; i <= number; i++)
			if(isPerfect(i))
				strReturn += i + ",";
		
		return strReturn;
	}
	
	public static boolean isSumDigits(int number, int someSum) {
		int sumOfDigits = 0;
		
		while (number > 0) {
			sumOfDigits += number % 10;
			number = number / 10;
		}
		
		return sumOfDigits == someSum;
	}
	
	public static boolean isAscending(int number) {
		int mostRightDigit = 0,
			nextLeftDigit  = 0;
		
		while (number > 0) {
			mostRightDigit = number % 10;
			number = number / 10;
			nextLeftDigit = number % 10;
			if (mostRightDigit <= nextLeftDigit)
				return false;
		}
		
		return true;
	}
	// Using array indexes, the method check if there are repeated digits.
	public static boolean areUniqueDigits(int number) {
		int currentDigit = 0;
		
		while (number != 0) {
			currentDigit = number % 10;
			
			if(isNumberDigit(currentDigit, number / 10))
				return false;
			
			number = number / 10;
		}
		
		return true;	
	}
	
	// Get one digit number and another number and returns whether the digit exists in number or not
	private static boolean isNumberDigit(int number, int inNumber) {
		// Check if the number is one digit
		if (number / 10 != 0) 
			return false;
		
		int currentDigit;
		
		do {
			currentDigit = inNumber % 10;
			
			if(currentDigit == number) 
				return true;
			
			inNumber = inNumber / 10;			
		}
		while (inNumber != 0);

		return false;
	}
	// Using the array indexes allows to know whether number is exists or not
	// It works like a table with pairs of number and truth data.
	public static boolean areDisjoint(int number1, int number2) {
		int currentDigit;
		
		while (number1 != 0) {
			currentDigit = number1 % 10;
			
			if(isNumberDigit(currentDigit, number2))
				return false;
			
			number1 = number1 / 10;
		}
		
		return true;	
	}
	
	public static void printNumberTriangle(int n) {
		if (n < 1)
			return;
		String numberTriangle = "";
		for(int i = 1; i <= n; i++) {
			for (int j = 1; j <= n-i; j++) 
				numberTriangle += "* ";
			for (int j = i; j >= 1; j--) 
				numberTriangle += j + " ";	
			numberTriangle += '\n';
		}
		System.out.println(numberTriangle);
	}
}
