package ClientPackage;

import testSuit.*;

public class DriverProgram{
	
	public static void main(String args[]){
		LLTest linkedListTest  = new LLTest();
		
		linkedListTest.PositiveTest();
		//linkedListTest.NegativeTest();
		
		linkedListTest = null;
	}
}