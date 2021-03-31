
public class Tester {
	public static void main(String[] args) {
		Person p1 = new Person();
		System.out.println(p1);
		System.out.println("--------------------------------------");
		Person p2 = new Person("Shay", 3014892, 75, 183,36.9, true);
		System.out.println("p2 info:");
		System.out.println(p2);
		System.out.println("bmi:" + p2.bmi() + " (" + p2.bmiDescription() + ")");
		System.out.println("temp. in Celsius: " + p2.temperature(true));
		System.out.println("temp. in Fahrenheit: " + p2.temperature(false));
		System.out.println("p2 shouldBeInQuarantine? " +p2.shouldBeInQuarantine());
		p2.incrementTemperature(3.8);
		System.out.println(p2);
		System.out.println("p2 shouldBeInQuarantine? " +p2.shouldBeInQuarantine());
		p2.setHasMask(false);
		System.out.println(p2);
		System.out.println("p2 shouldBeInQuarantine? " +p2.shouldBeInQuarantine());
		System.out.println("--------------------------------------");
		Person p3 = new Person("Shay", 3014892, 45, 160, 38, false);
		System.out.println("p3 info:");
		System.out.println(p3);
		System.out.println("bmi:" + p3.bmi() + " (" + p3.bmiDescription() + ")");
		System.out.println("p3 shouldBeInQuarantine? " +p3.shouldBeInQuarantine());
		p3.setTemperature(36.5);
		System.out.println("p3 shouldBeInQuarantine? " +p3.shouldBeInQuarantine());
	}
}
