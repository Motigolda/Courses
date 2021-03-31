
public class City {
	
	private String 	name;
	private String 	country;
	private int 	numQuarantined;
	private int 	numSick;
	private int 	numHealthy;
	private double 	coronaScore;
	private String 	color;
	final String 	red		= "Red";
	final String 	green	= "Green";
	final String 	orange	= "Orange";
	final double 	lowCoronaRate 	= 0.3;
	final double 	mediumCoronaRate= 0.7;
	
	public City(String name, String country, int numHealthy,
			int numSick, int numQuarantined) {
		this.name = name;
		this.country = country;
		this.numQuarantined = numQuarantined;
		this.numSick = numSick;
		this.numHealthy = numHealthy;
		updateCoronaScore();
	}
	
	public City(City other) {
		this.name = other.name;
		this.country = other.country;
		this.numQuarantined = other.numQuarantined;
		this.numSick = other.numSick;
		this.numHealthy = other.numHealthy;
	}
	
	public City(City city1, City city2) {
		this.name = city1.name + '-' + city2.name;
		this.country = city1.country;
		this.numHealthy = city1.numHealthy + city2.numHealthy;
		this.numSick = city1.numSick + city2.numSick;
		this.numQuarantined = city1.numQuarantined + city2.numQuarantined;	
	}

	public String getName() {
		return name;
	}

	public String getCountry() {
		return country;
	}

	public int getNumQuarantined() {
		return numQuarantined;
	}

	public int getNumSick() {
		return numSick;
	}

	public int getNumHealthy() {
		return numHealthy;
	}

	public double getCoronaScore() {
		return coronaScore;
	}

	public String getColor() {
		return color;
	}
	
	public int getPopulation() {
		return this.numHealthy 
			+ this.numQuarantined 
			+ this.numSick;
	}
	
	public double getSickRatio() {
		return ((double)this.numSick / 
				(double)getPopulation());
	}
	
	public double getQuarantinedRatio() {
		return ((double)this.numQuarantined / 
				(double)getPopulation());
	}
	
	public double getHealthyRatio() {
		return (((double)this.numHealthy) / 
				((double)getPopulation()));
	}
	
	// This method updates the corona score and the color of the city. 
	private void updateCoronaScore() {
		this.coronaScore = (double)(numSick + numQuarantined) / getPopulation();
		if (this.coronaScore < lowCoronaRate)
			this.color = green;
		else if (this.coronaScore >= mediumCoronaRate)
			this.color = red;
		else
			this.color = orange;
	}
	
	public boolean equals(City other) {
		return this.name == other.name 
			&& this.country == other.country;
	}
	
	public boolean saferThan(City other) {
		return this.numSick < other.numSick 
			&& this.numQuarantined < other.numQuarantined;
	}
		
	public boolean biggerThan(City other) {
		return this.getPopulation() > other.getPopulation();
	}
	
	public void addHealthyResidents(int numHealthy) {
		if (numHealthy > 0)
			this.numHealthy += numHealthy;	
		updateCoronaScore();
	}
	
	public void sendToQuarantine(int numNewQuarantine) {
		if (numNewQuarantine <= 0) return;
		
		if (numNewQuarantine > this.numHealthy) {
			this.numQuarantined += this.numHealthy;
			this.numHealthy = 0;
		}
		else {
			this.numHealthy -= numNewQuarantine;
			this.numQuarantined += numNewQuarantine;
		}
		updateCoronaScore();
	}
	
	public void releaseFromQuarantine(int numNewHealthy) {
		if (numNewHealthy <= 0) return;
		
		if (numNewHealthy >= numQuarantined) {
			numHealthy += numQuarantined;
			numQuarantined = 0;
		}
		else {
			numHealthy += numNewHealthy;
			numQuarantined -= numNewHealthy;
		}
		updateCoronaScore();
	}
	
	public void releaseFromHospital(int numGotHealthy) {
		if (numGotHealthy <= 0) return;
		
		if (numGotHealthy > numSick) {
			numHealthy += numSick;
			numSick = 0;
		}
		else {
			numSick -= numGotHealthy;
			numHealthy += numGotHealthy;
		}
		updateCoronaScore();
	}
	
	public void multiplySickResidents(int factor) {
		if (factor <= 1) return;
		
		int newSicksNumber = numSick * (factor - 1);
		
		if (newSicksNumber > getPopulation() - numSick) {
			numSick += numQuarantined + numHealthy;
			numQuarantined = 0;
			numHealthy = 0;
		}
		else {
			if (newSicksNumber <= numQuarantined) {
				numQuarantined -= newSicksNumber;
				numSick += newSicksNumber;
			}
			else {
				numSick += newSicksNumber;
				newSicksNumber -= numQuarantined;
				numQuarantined = 0;
				numHealthy -= newSicksNumber;
			}
		}
		updateCoronaScore();
	}
	
	private double showInPercents(double data) {
		return data * 100.0;
	}
	
	public String toString() {
		String template = "City %s, %s has %d residents " 
						+ "(healthy: %d, sick: %d, quarantined: %d). " 
						+ "%%healthy = %.2f%%, Corona score: %.3f (%s)";
		
		String retStr = String.format(template, 
				name, 
				country, 
				getPopulation(), 
				this.numHealthy, 
				this.numSick, 
				this.numQuarantined, 
				showInPercents(getHealthyRatio()), 
				this.coronaScore, 
				this.color
				);
		
		return retStr;
		
	}
	
}
