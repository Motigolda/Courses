
public class MyTester {
	public static void main(String[] args) {
		
		
		
		/*
		int numOfFailedTests = 0;
		
		System.out.println("Test start.");

		//5
		sen = new LimitedSentence(' ');
		test(sen.appendWordFront("Gello"), true, "Failed to enter word in the front");
		test(sen.getSentence(), "Gello", "Wrong sentence gello");
		//6
		test(sen.appendWordEnd("Guys"), true, "Failed to enter word in the end");
		test(sen.getSentence(), "Gello Guys","Wrong sentence Gello Guys");
		//7
		LimitedSentence newSen = new LimitedSentence(sen);
		test(newSen.getSentence(), "Gello Guys", "failed with the copy constructor");
		test(newSen.getDelimiter(), ' ', "failed with the copy constructor");
		//8
		sen = new LimitedSentence();
		test(!newSen.getSentence().equals(sen.getSentence()), true, "Aliasing test failed");
		
		
		System.out.println("\n------\nNum of failed tests: " + numOfFailedTests);
	*/}
	
	public static boolean test(Object output, Object exceptedOutput, String failMessage) {
		if (!output.equals(exceptedOutput)) {
			System.err.println("\n+----+\nTest failed.\nexcepted output: " +
								exceptedOutput.toString() + 
								"\noutput: " + output.toString());
			if(failMessage != null)
				System.err.println(failMessage);
			return false;
		}
		return true;
	}
	
	public static boolean test(Object output, Object exceptedOutput) {
		return test(output, exceptedOutput, null);
	}

	public static boolean constructorsTests() {

		return false;
	}
}
