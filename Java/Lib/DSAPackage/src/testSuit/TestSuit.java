package testSuit;

abstract class TestSuit implements ITestSuit{
	abstract public void PositiveTest();
	abstract public void NegativeTest();
	
	abstract public void NotifyResults();
	abstract public void PrintResult();
}