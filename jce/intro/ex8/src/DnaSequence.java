
public class DnaSequence {
	private String sequence;
	private int[] nucleotideCounts;
	
	public DnaSequence() {
		this("ACGT");
	}
	
	public DnaSequence(String sequence) {
		nucleotideCounts = new int[4];
		
		if(isDnaSequence(sequence))
			this.sequence = sequence;
		else
			this.sequence = "ACGT";
		
		updateLettersCount();
	}
	
	public DnaSequence(DnaSequence other) {
		sequence = other.getSequence();
		nucleotideCounts = other.getNucleotideCounts();	
	}
	
	public String getSequence() {
        return new String(sequence);
	}
	
	public int[] getNucleotideCounts() {
        return nucleotideCounts;
	}
	
	public void setSequence(String sequence) {
		if(isDnaSequence(sequence)) {
			this.sequence = sequence;
			updateLettersCount();
		}
	}
	
	public static boolean isDnaSequence(String sequence) {
		if (sequence.length() == 0)
			return true;
		
		char currentChar = Character.toLowerCase(sequence.charAt(0));
		
		if (currentChar != 'a' && currentChar != 'c' && currentChar != 'g' && currentChar != 't')
			return false;
		
		return isDnaSequence(sequence.substring(1));
	}
	
	public void changeCapitalization() {
		sequence = changeCapitaliziation(sequence);
	}
	
	public static boolean addArray(int[] arr1, int[] arr2) {
        if(arr1 == null || arr2 == null || arr1.length != arr2.length)
        	return false;
        
		return addArray(arr1, arr2, 0);
	}
	
	public void concatGenes(DnaSequence other) {
		sequence += other.getSequence();
		addArray(nucleotideCounts, other.getNucleotideCounts());
	}
	
	public String toString() {
        return String.format("%s: (%d, %d, %d, %d)", 
        		sequence, 
        		nucleotideCounts[0],
        		nucleotideCounts[1],
        		nucleotideCounts[2],
        		nucleotideCounts[3]);
	}	
	
	// private methods
	
	private void updateLettersCount() {
		int[] count = new int[4];
		nucleotideCounts = countLetters(sequence, count);
	}
	
	private int[] countLetters(String sequence, int[] count) {
		if (sequence.length() == 0) 
			return count;
		
		char currentChar = Character.toLowerCase(sequence.charAt(0));
		
		switch (currentChar) {
		case 'a':
			count[0]++; 
			break;
		case 'c':
			count[1]++;
			break;
		case 'g':
			count[2]++;
			break;
		case 't':
			count[3]++;
			break;
		}
		
		return countLetters(sequence.substring(1), count);
	}
	
	private String changeCapitaliziation(String sequence) {
		if (sequence.length() == 0)
			return "";
		
		char currentChar = sequence.charAt(0);
		
		if (Character.isLowerCase(currentChar))
			return Character.toUpperCase(currentChar) + changeCapitaliziation(sequence.substring(1));
		else
			return Character.toLowerCase(currentChar) + changeCapitaliziation(sequence.substring(1));
		
	}

	private static boolean addArray(int[] arr1, int[] arr2, int index) {
        if (arr1 == null || arr2 == null || arr1.length != arr2.length)
        	return false;
        
        if (index == arr1.length)
        	return true;
        
        arr1[index] += arr2[index];
        
        return addArray(arr1, arr2, index + 1);
	}
}
