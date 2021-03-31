
public class Tester {
	final static double ERR_THRESHOLD = 0.0001;
	public static boolean areCloseEnough(double num1,  double num2) {
		return Math.abs(num1 - num2) < ERR_THRESHOLD;
	}
	
	public static void reportTest(boolean condition, int testNum) {
		if(! condition)
			System.out.println("FAILED TEST " + testNum + ".");
		else
			System.out.println("PASSED TEST " + testNum + ".");
	}
	
	public static void main(String[] args) {
		Circle c1 = new Circle();
		Circle c2 = new Circle(c1);
		Circle c3 = new Circle(new Point(1, 2), 0.5);
		reportTest(c1.toString().equals("Circle at (0.0, 0.0), radius 1.0"), 1);
		reportTest(c2.toString().equals("Circle at (0.0, 0.0), radius 1.0"), 2);
		reportTest(c3.toString().equals("Circle at (1.0, 2.0), radius 0.5"), 3);
		reportTest(areCloseEnough(c3.area(), 0.785398164), 4);
		reportTest(areCloseEnough(c3.perimeter(), 3.141592654), 5);
		reportTest(!c3.equals(c2), 6);

		Circle c4 = new Circle(new Point(-3, 2), Math.sqrt(10));
		Circle c5 = new Circle(new Point(6, -1), Math.sqrt(40));
		
		Circle c6 = new Circle(new Point(2, 3),  3);
		Circle c7 = new Circle(new Point(1, -1),  4);
		
		reportTest(!c7.touches(c6), 7); // they intersect
		reportTest(!c4.intersects(c5), 8); // they touch
		reportTest(c6.contains(new Point(2, 3)), 9); 
		reportTest(!c4.contains(c5), 10); 
		reportTest(new Circle().subCircle().equals(new Circle(new Point(0.5, 0), 0.5)), 11); 
	}
}
