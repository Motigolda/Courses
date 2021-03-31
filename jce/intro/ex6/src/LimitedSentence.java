

public class LimitedSentence {
	private String sentence;
	private char delimiter;
	static private final int 	SENTENCEMAXLENGTH = 25,
								NUMTOCHANGECASE = 32;
	
	public LimitedSentence() {
		this(' ');
	}
	
	public LimitedSentence(char delimiter) {
		this.sentence = "";
		if (isLegalDelimiter(delimiter))
			this.delimiter = delimiter;
		else
			this.delimiter = ' ';
	}
	
	public LimitedSentence(LimitedSentence other) {
		this.sentence = new String(other.sentence);
		this.delimiter = other.getDelimiter();
	}

	public String getSentence() {
		return sentence;
	}

	public char getDelimiter() {
		return delimiter;
	}
	
	public char getFirstLetter() {
		if (!isSentenceEmpty(sentence))
			return sentence.charAt(0);
		return 0;
	}

	public char getMiddleLetter() {
		if(isSentenceEmpty(sentence))
			return 0;
		
		return sentence.charAt(sentence.length() / 2);
	}
	
	public char getLastLetter() {
		if (isSentenceEmpty(sentence)) 
			return 0;
		
		return sentence.charAt(sentence.length() - 1);
	}
	
	public boolean appendWordEnd(String toAppend) {
		if (! isLegalWord(toAppend) )
			return false;
		
		String newSentence;
		if (isSentenceEmpty(sentence))
			newSentence = toAppend;
		else
			newSentence = sentence + delimiter + toAppend;
		
		if (! isLegalSentence(newSentence))
			return false;
		
		sentence = newSentence;
		
		return true;
	}
	
	public boolean appendWordFront(String toAppend) {
		if (! isLegalWord(toAppend) )
			return false;
		
		String newSentence;
		if (isSentenceEmpty(sentence))
			newSentence = toAppend;
		else
			newSentence = toAppend + delimiter + sentence;;
		
		if (! isLegalSentence(newSentence))
			return false;
		
		sentence = newSentence;
		
		return true;
	}
	
	public String getIthWord(int i) {
		String word = "";
		int wordIndexer = 0;
		char currentChar;
		for (int j = 0; j < sentence.length(); j++) {
			currentChar = sentence.charAt(j);
			if (wordIndexer == i && currentChar != delimiter)
				word += currentChar;
			
			if (currentChar == delimiter) 
				wordIndexer++;
			
			if (wordIndexer > i)
				break;
		}
		return word;
	}

	public String getIthWordReversed(int i) {
		String ithWord = getIthWord(i);
		return getReversedString(ithWord);
	}
	
	public int countWords() {
		if (isSentenceEmpty(sentence))
			return 0;
		
		int numOfWords = 1;

		for (int i = 0; i < sentence.length(); i++)
			if (sentence.charAt(i) == delimiter)
				numOfWords++;
		
		return numOfWords;
	}
	
	public void reverseUpperLower() {
		String newSentence = "";
		for (int i = 0; i < sentence.length(); i++)
			newSentence += toggleLetterCase(sentence.charAt(i));
		
		sentence = newSentence;
	}
	
	public String toString() {
		return sentence;
	}
	
	// Private methods for rules validating.
	
	private static boolean isLegalDelimiter(char delimiter) {
		return !isEnglishLetter(delimiter);
	}
	
	private static boolean isLegalSentence(String sentence) {
		// Not to long
		if (sentence.length() > SENTENCEMAXLENGTH)
			return false;
		// If Empty - return true
		if (sentence.length() == 0)
			return true;
		
		// Includes one delimiter occurrence only
		boolean flagDelimiterFound = false;
		for (int i = 0; i < sentence.length(); i++) {
			if ( isEnglishLetter( sentence.charAt(i) ) ) {
					flagDelimiterFound = false;
			}
			else {
				if(flagDelimiterFound)
					return false;
				else
					flagDelimiterFound = true;
			}
		}
		// Trimmed 
		char firstLetter = sentence.charAt(0),
				lastLetter = sentence.charAt(sentence.length() - 1);
		
		if (! ( isEnglishLetter(firstLetter)) && isEnglishLetter(lastLetter) )
			return false;
		
		return true;
	}
	
	public static boolean isEnglishLetter(char c) {
		boolean isAsciiLowerCase = 'a' <= c && c <= 'z';
		boolean isAsciiUpperCase = 'A' <= c && c <= 'Z';
		return isAsciiLowerCase || isAsciiUpperCase;
	}
	
	private static boolean isSentenceEmpty(String sentence) {
		return sentence.length() == 0;
	}
	
	private static boolean isLegalWord(String word) {
		char currentChar;
		for (int i = 0; i < word.length(); i++) {
			currentChar = word.charAt(i);
			if (! isEnglishLetter(currentChar) )
				return false;
		}
		
		return true;		
	}

	private static String getReversedString(String str) {
		String newStr = "";
		
		for (int i = str.length() - 1; i >= 0; i--)
			newStr += str.charAt(i);
			
		return newStr;
	}
	
	private static char toggleLetterCase(char c) {
		if (! isEnglishLetter(c))
			return c;
		
		boolean asciiLowerCase = 'a' <= c && c <= 'z';
		
		if (asciiLowerCase)
			return (char)((int)c - NUMTOCHANGECASE);

		return (char)((int)c + NUMTOCHANGECASE);
	}
}
