
public class Square extends Rectangle {
	public Square(double length) {
		super(length, length);		
	}
	
	public void setWidth(double w) {
		super.setWidth(w);
		super.setHeight(w);
	}
	
	public void setHeight(double h) {
		super.setWidth(h);
		super.setHeight(h);		
	}
	public String toString() {
		return "Square: length = [" + width + "]";
	}
	public double area() {
		return width * width;
	}
	public double perimeter() {
		return 4 * width;
	}
}
