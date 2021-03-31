
public class Person {
	private String name;
	private int id;
	private double height;
	private double weight;
	private double temperature;
	private boolean hasMask;
	
	public Person() 
	{
		this.name        = "";
		this.id          = -1;
		this.height      = -1.0;
		this.weight      = -1.0;
		this.temperature = -1.0;
		this.hasMask     = false;
	}
	
	public Person(String name, int id, double weight, double height, double temperature, boolean hasMask)
	{
		this.name = name;
		this.id = id;
		this.weight = weight;
		this.height = height;
		this.temperature = temperature;
		this.hasMask = hasMask;
	}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		if(id > 0)
			this.id = id;
	}

	public double getHeight() {
		return height;
	}

	public void setHeight(double height) {
		if(height > 0)
			this.height = height;
	}

	public double getWeight() {
		return weight;
	}

	public void setWeight(double weight) {
		if(weight > 0)
			this.weight = weight;
	}

	public double getTemperature() {
		return temperature;
	}

	public void setTemperature(double temperature) {
		if(temperature > 0)
			this.temperature = temperature;
	}

	public boolean isHasMask() {
		return hasMask;
	}

	public void setHasMask(boolean hasMask) {
		this.hasMask = hasMask;
	}

	public String toString() {
		String retStr = String.format("Person %s, %d: height=%.2f, weight=%.2f, temp=%.2f", 
				this.name, this.id, this.height, this.weight, this.temperature);
		
		if (hasMask)
			retStr += " (is wearing a mask)";
		else
			retStr += " (is not wearing a mask)";

		return retStr;
	}
	
	public double toFahrenheit() {
		return this.temperature * 1.8 + 32;
	}
	
	public double temperature(boolean isCelsius) {
		if(isCelsius)
			return this.temperature;
		else
			return toFahrenheit();
	}
	
	public double bmi() {
		double heightInMeters = this.height / 100;
		return this.weight / (heightInMeters * heightInMeters);
	}
	
	public String bmiDescription() {
		String desc = "";
		
		double bmi = this.bmi();
		
		if(bmi < 18.5) 
			desc = "underweight";
		else if(bmi >= 18.5 && bmi <= 24.9)
			desc = "normal";
		else 
			desc = "overweight";
		
		return desc;
	}
	
	public boolean shouldBeInQuarantine() {
		boolean should = false;
		double bmi = bmi();
		
		if (bmi < 20 && temperature > 37.8 && !hasMask) 
			should = true;
		if (bmi >= 20 && temperature > 38.1 && !hasMask)
			should = true;
		
		return should;
	}
	public void incrementTemperature(double num) {
		if(num > 0)
			temperature += num;
	}
}
