public class MyTester {
	public static void main(String[] args) {
		System.out.println(NumberUtils.isPositivePrime(1) == false);
		System.out.println(NumberUtils.isPositivePrime(2) == true);
		System.out.println(NumberUtils.isPositivePrime(3) == true);
		System.out.println(NumberUtils.isPositivePrime(4) == false);
		System.out.println(NumberUtils.isPositivePrime(5) == true);
		System.out.println(NumberUtils.isPositivePrime(6) == false);
		System.out.println(NumberUtils.isPositivePrime(7) == true);
		System.out.println(NumberUtils.isPositivePrime(8) == false);	
		System.out.println(NumberUtils.isPositivePrime(9) == false);
		System.out.println(NumberUtils.isPositivePrime(10) == false);
		System.out.println(NumberUtils.isPositivePrime(11) == true);
		System.out.println(NumberUtils.isPositivePrime(12) == false);
		System.out.println(NumberUtils.isPositivePrime(13) == true);
		System.out.println(NumberUtils.isPositivePrime(14) == false);
		System.out.println(NumberUtils.isPositivePrime(15) == false);
		System.out.println(NumberUtils.isPositivePrime(16) == false);
		System.out.println(NumberUtils.isPositivePrime(17) == true);
		System.out.println(NumberUtils.isPositivePrime(18) == false);
		System.out.println(NumberUtils.isPositivePrime(19) == true);
		System.out.println(NumberUtils.isPositivePrime(20) == false);
		System.out.println(NumberUtils.isPositivePrime(21) == false);		
		System.out.println(NumberUtils.isPositivePrime(22) == false);
		System.out.println(NumberUtils.isPositivePrime(23) == true);
		System.out.println(NumberUtils.isPositivePrime(24) == false);
		System.out.println(NumberUtils.isPositivePrime(25) == false);
		System.out.println(NumberUtils.isPositivePrime(26) == false);		
		System.out.println(NumberUtils.isPositivePrime(27) == false);
		System.out.println(NumberUtils.isPositivePrime(28) == false);
		System.out.println(NumberUtils.isPositivePrime(29) == true);
		System.out.println(NumberUtils.isPositivePrime(30) == false);
		
		System.out.println(NumberUtils.factorial(-1) == -1);
		System.out.println(NumberUtils.factorial(-10) == -1);
		System.out.println(NumberUtils.factorial(-1123) == -1);
		System.out.println(NumberUtils.factorial(0) == -1);
		System.out.println(NumberUtils.factorial(1) == 1);
		System.out.println(NumberUtils.factorial(2) == 1*2);
		System.out.println(NumberUtils.factorial(3) == 1*2*3);
		System.out.println(NumberUtils.factorial(4) == 1*2*3*4);
		System.out.println(NumberUtils.factorial(5) == 1*2*3*4*5);
		System.out.println(NumberUtils.factorial(6) == 1*2*3*4*5*6);
		
		System.out.println(NumberUtils.isPerfect(496) == true);
		System.out.println(NumberUtils.isPerfect(8128) == true);
		System.out.println(NumberUtils.isPerfect(81283) == false);
		
		System.out.println(NumberUtils.isAscending(12345) == true);
		System.out.println(NumberUtils.isAscending(3345) == false);
		System.out.println(NumberUtils.isAscending(2357) == true);

		
		
		
		
		
	}
}
