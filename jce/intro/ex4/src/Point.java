
public class Point {
	/**
	 * X coordinate.
	 */
	private double x;
	
	/**
	 * Y coordinate.
	 */
	private double y;

	/**
	 * Default constructor.
	 */
	public Point() {
		this(0, 0);
	}

	/**
	 * Constructor.
	 * @param x Coordinate for x-axis.
	 * @param y Coordinate for y-axis.
	 */
	public Point(double x, double y) {
		this.x = x;
		this.y = y;
	}

	/**
	 * Copy constructor.
	 * @param p Object to copy.
	 */
	public Point(Point p) {
		this(p.x, p.y);
	}
	
	/**
	 * @return the distance of p from this.
	 */
	public double distanceFrom(Point p) {
		double dx = this.x - p.x;
		double dy = this.y - p.y;
		return Math.sqrt(dx*dx + dy*dy);
	}
	
	/**
	 * @param point to compare to.
	 * @return true if the given point equals this point.
	 */
	public boolean equals(Point p) {
		return this.x == p.x && this.y == p.y;
	}

	/**
	 * @return the x coordinate.
	 */
	public double getX() {
		return x;
	}

	/**
	 * @return the y coordinate.
	 */
	public double getY() {
		return y;
	}
	
	/**
	 * @return a String representation of the point.
	 */
	public String toString() {
		return "(" + x + ", " + y + ")";
	}
}
