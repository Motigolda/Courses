
public class Circle extends Shape {

	private double radius;
	
	public Circle(double r) {
		setRadius(r);
	}

	public double getRadius() {
		return radius;
	}

	public void setRadius(double r) {
		if(r > 0) 
			this.radius = r;
		else
			this.radius = 1;
	}

	public double area() {
		return Math.PI * radius * radius;
	}

	public double perimeter() {
		return 2 * Math.PI * radius;
	}
	public String toString() {
		return "Circle: radius = [" + radius + "]";
	}
}
