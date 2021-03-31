
public class Circle {
	private Point center;
	private double radius;
	
	public Circle() {
		center = new Point(0, 0);
		radius = 1;
	}
	
	public Circle(Point center, double radius) {
		this.center = center;
		this.radius = radius;
	}
	
	public Circle(Circle other) {
		this.center = other.center;
		this.radius = other.radius;
	}
	
	public double area() {
		return radius * radius * Math.PI;
	}
	
	public double perimeter() {
		return 2 * radius * Math.PI;
	}
	
	public boolean touches(Circle other) {
		double distanceBetweenCenters = getDistanceBetweenCenters(other);
		// Check weather whether they are touches internally or externally
		boolean touchesInternally = distanceBetweenCenters == radius + other.radius;
		boolean touchesExternally = distanceBetweenCenters == radius - other.radius;
		// Return the answer
		return touchesExternally || touchesInternally;
	}
	
	public boolean intersects(Circle other) {
		double distanceBetweenCenters = getDistanceBetweenCenters(other);
		return radius - other.radius < distanceBetweenCenters && distanceBetweenCenters < Math.abs(radius + other.radius); 
	}
	
	public boolean contains(Point p) {
		double distanceBetweenCenterAndPoint = center.distanceFrom(p);
		return distanceBetweenCenterAndPoint <= radius;
	}
	
	public boolean contains(Circle other) {
		double distanceBetweenCenters = getDistanceBetweenCenters(other);
		return distanceBetweenCenters < other.radius - radius;
	}
	
	public Circle subCircle() {
		double newX = center.getX() + (radius / 2);
		double newY = center.getY();
		Point newCenter = new Point(newX, newY);
		double newRadius = radius / 2;
		return new Circle(newCenter, newRadius);
	}
	
	/**
	 * @param other the Circle for distance checking
	 * @return the distance
	 */
	private double getDistanceBetweenCenters(Circle other) {
		return center.distanceFrom(other.center);
	}
	
	public Point getCenter() {
		return center;
	}
	
	public void setCenter(Point center) {
		this.center = center;
	}
	
	public double getRadius() {
		return radius;
	}
	
	public void setRadius(double radius) {
		if (radius > 0) 
			this.radius = radius;
	}
	
	public String toString() {
		String format = "Circle at (%.1f, %.1f), radius %.1f";
		return String.format(format, center.getX(), center.getY(), radius);
	}

	public boolean equals(Circle other) {
		boolean centerEquals = this.center.equals(other.center);
		boolean radiusEquals = this.radius == other.radius;
		return centerEquals && radiusEquals;
	}
}
