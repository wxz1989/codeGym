package testSuit;

import Factory.Factory;
import Factory.FactoryManager;
import LinkedList.List;
import NodePkg.Node;
import RandNumGenerator.NodeValueGenerator;

public class LLTest extends TestSuit{
	public void PositiveTest(){
		Factory listFactory  = FactoryManager.GetManagedLinkedListFactory();
		List myList = listFactory.CreateLinkedList();
		System.out.println("Current List Size:" +  myList.Size());
		
		myList.InsertAt(100, -1);
		
		myList.Reverse();
		
		for ( int i = 0; i< 10 ; i++){
			int newValue = NodeValueGenerator.getRandomIntForNode(100);
			myList.Insert(newValue);
			System.out.println("List Size After Insertion:" +  myList.Size());
		}
		System.out.println("Current List Size:" +  myList.Size());
		myList.Traverse();
		
		
		System.out.println("Start Random Number Insert AT");
		for ( int i = 0; i< 10 ; i++){
			int newValue = NodeValueGenerator.getRandomIntForNode(100);
			int newIndex = NodeValueGenerator.getRandomIntForNode(myList.Size());
			myList.InsertAt(newValue, newIndex);
			myList.Traverse();
			System.out.println("List Size After Insertion:" +  myList.Size());
		}
		System.out.println("Current List Size:" +  myList.Size());
		myList.Traverse();
		System.out.println("END Random Number Insert AT");
		
		System.out.println("Reverse Recursively++");		
		myList.ReverseLite();
		System.out.println("Reverse Recursively--");
		
		System.out.println("Traverse ++");
		myList.Traverse();
		System.out.println("Traverse --");
		
		System.out.println("Reverse Recursively++");		
		myList.ReverseR();
		System.out.println("Reverse Recursively--");
		myList.Traverse();
		
		myList.Reverse();
		myList.Traverse();
		
		myList.ReverseKElements(3);
		
		int valueToDelete = 50;
		Node foundNode = myList.Search(valueToDelete);
		if ( foundNode != null ){
			System.out.println("Found Node Value:" + foundNode.Getvalue().toString());
			myList.Delete(valueToDelete);
			myList.Traverse();
		} else {
			System.out.println("Node not found");
		}
		System.out.println("Current List Size:" +  myList.Size());
		
		System.out.println("Starting random number generation" );
		Node randNode = null;
		int value = -1;
		while ( myList.Size() > 0 ) {
			
			try{
				randNode = myList.GetRandom();
				value = Integer.parseInt(randNode.Getvalue().toString());
				
			} catch (NullPointerException e){
				System.out.println("Exception raised");
				e.printStackTrace();
				myList.Traverse();
				break;
			}
			myList.Delete(value);
			System.out.println("Size After Deletion :"+ myList.Size() );
			myList.Traverse();
		}
		System.out.println("Ending random number generation");
		myList.Traverse();
		
		myList.RemoveAll();
		System.out.println("Current List Size:" +  myList.Size());
		
		myList = null;
	}
	
	@Override
	public void NegativeTest() {
		// TODO Auto-generated method stub

		Factory listFactory  = FactoryManager.GetManagedLinkedListFactory();
		List myList = listFactory.CreateLinkedList();
		System.out.println("Current List Size:" +  myList.Size());
		
		myList.InsertAt(-500000, -200);
		
		for ( int i = 0; i< 10 ; i++){
			int newValue = NodeValueGenerator.getRandomIntForNode(-50000);
			myList.Insert(newValue);
			System.out.println("List Size After Insertion:" +  myList.Size());
		}
		System.out.println("Current List Size:" +  myList.Size());
		myList.Traverse();
		
		
		System.out.println("Start Random Number Insert AT");
		for ( int i = 0; i< 10 ; i++){
			int newValue = NodeValueGenerator.getRandomIntForNode(-50000);
			int newIndex = NodeValueGenerator.getRandomIntForNode(myList.Size());
			myList.InsertAt(newValue, newIndex);
			myList.Traverse();
			System.out.println("List Size After Insertion:" +  myList.Size());
		}
		System.out.println("Current List Size:" +  myList.Size());
		myList.Traverse();
		System.out.println("END Random Number Insert AT");
		
		int valueToDelete = -12312938;
		Node foundNode = myList.Search(valueToDelete);
		if ( foundNode != null ){
			System.out.println("Found Node Value:" + foundNode.Getvalue().toString());
			myList.Delete(valueToDelete);
			myList.Traverse();
		} else {
			System.out.println("Node not found");
		}
		System.out.println("Current List Size:" +  myList.Size());
		
		System.out.println("Starting random number generation" );
		Node randNode = null;
		int value = -1;
		while ( myList.Size() > 0 ) {
			
			try{
				randNode = myList.GetRandom();
				value = Integer.parseInt(randNode.Getvalue().toString());
				
			} catch (NullPointerException e){
				System.out.println("Exception raised");
				e.printStackTrace();
				myList.Traverse();
				break;
			}
			myList.Delete(value);
			System.out.println("Size After Deletion :"+ myList.Size() );
			myList.Traverse();
		}
		System.out.println("Ending random number generation");
		myList.Traverse();
		
		myList.RemoveAll();
		System.out.println("Current List Size:" +  myList.Size());
		
		myList = null;
	}

	@Override
	public void NotifyResults() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void PrintResult() {
		// TODO Auto-generated method stub
		
	}
}