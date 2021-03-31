
public class Tester {
	public static void main(String[] args) {
		Circle circle = new Circle(3);
		System.out.println(circle.getRadius() == 3);
		System.out.println(circle.toString());
		circle.setRadius(0);
		System.out.println(circle.getRadius() == 1);
		circle.setRadius(-1);
		System.out.println(circle.getRadius() == 1);
		circle = new Circle(-123);
		System.out.println(circle.getRadius() == 1);
		
		Rectangle rect = new Rectangle(10, 4);
		System.out.println(rect.getWidth() == 10);
		System.out.println(rect.getHeight() == 4);
		System.out.println(rect.area() == 10 * 4);
		System.out.println(rect.perimeter() == 10 * 2 + 4 * 2);
		System.out.println();
		rect.setHeight(-1);
		System.out.println(rect.getHeight() == 1);
		rect.setWidth(-1);
		System.out.println(rect.getWidth() == 1);
		rect = new Rectangle(-1, -2);
		System.out.println(rect.getHeight() == 1);
		System.out.println(rect.getWidth() == 1);	
		System.out.println(rect.toString());
		
		Square square = new Square(5);
		System.out.println(square.getHeight() == 5);
		System.out.println(square.getWidth() == 5);
		square.setHeight(81);
		System.out.println(square.getHeight() == 81);
		System.out.println(square.getWidth() == 81);
		System.out.println(square.area() == 81*81);
		System.out.println(square.perimeter() == 81 * 4);
		square.setWidth(-1);
		System.out.println(square.getHeight() == 1);
		System.out.println(square.getWidth() == 1);
		square.setHeight(123);
		System.out.println(square.getHeight() == 123);
		System.out.println(square.getWidth() == 123);
		square.setWidth(-123);
		System.out.println(square.getWidth() == 1);
		System.out.println(square.getHeight() == 1);
		System.out.println(square.toString());
	}
}
