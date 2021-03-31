
public class CityTester {
	public static void main(String[] args) {
		City c1 = new City("TelAviv", "Israel", 350, 100, 50);
		System.out.println(c1);
		c1.sendToQuarantine(50);
		System.out.println(c1);
		c1.sendToQuarantine(250);
		System.out.println(c1);
		c1.sendToQuarantine(10);
		System.out.println(c1);
		c1.sendToQuarantine(100);
		System.out.println(c1);

		System.out.println("Adding healthy people:");
		c1.addHealthyResidents(51);
		System.out.println(c1);

		System.out.println("\n-------------------");
		System.out.println("Creating Yafo, a green city:");
		City c2 = new City("Yafo", "Israel", 180, 5, 15);
		System.out.println("c2.getHealthyRatio(): " + c2.getHealthyRatio());
		System.out.println("c2.getSickRatio(): " + c2.getSickRatio());
		System.out.println("c2.getQuarantinedRatio(): " + c2.getQuarantinedRatio());
		System.out.println(c2);
		c2.multiplySickResidents(2);
		System.out.println("c2 after running c2.multiplySickResidents(2):");
		System.out.println(c2);
		c2.multiplySickResidents(3);
		System.out.println("c2 after running c2.multiplySickResidents(3):");
		System.out.println(c2);
		c2.multiplySickResidents(4);
		System.out.println("c2 after running c2.multiplySickResidents(4):");
		System.out.println(c2);

		System.out.println("\n-------------------");
		System.out.println("Merging Cities:");
		City c3 = new City(c1, c2);
		System.out.println(c3);

		System.out.println("Realease from hospital & quarantine:");
		System.out.println("c3.releaseFromHospital(25):");
		c3.releaseFromHospital(25);
		System.out.println(c3);

		System.out.println("c3.releaseFromQuarantine(315):");
		c3.releaseFromQuarantine(315);
		System.out.println(c3);
		
		
		System.out.println("\n-------------------");
		System.out.println("c1: " + c1);
		System.out.println("c2: " + c2);
		System.out.println("c3: " + c3);
		
		System.out.println("c2 is safer than c3? " + c2.saferThan(c3));
		System.out.println("c3 is safer than c1? " + c3.saferThan(c1));
		System.out.println("c3 is bigger than c1? " + c3.biggerThan(c1));
		System.out.println("c1 is bigger than c3? " + c1.biggerThan(c3));
		System.out.println("c1 is bigger than c1? " + c1.biggerThan(c1));
		System.out.println("c1 equals c1? " + c1.equals(c1));
	}
}
 