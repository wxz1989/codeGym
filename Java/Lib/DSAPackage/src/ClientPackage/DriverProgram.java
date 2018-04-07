package ClientPackage;

import testSuit.*;


public class DriverProgram{
	
	public static void main(String args[]){
		
		//Self made test suit for API testing.
		
		/*positive test cases
		 * 
		 */
		
		//LinkedList Test
		LLTest linkedListTest  = new LLTest();
		linkedListTest.PositiveTest();
		
		//Tree Test
		TreeTest ttTest = new TreeTest();
		ttTest.PositiveTest();
	
		/* Negative test cases
		 * 
		 */
		
		linkedListTest = null;
		ttTest = null;
	}
}