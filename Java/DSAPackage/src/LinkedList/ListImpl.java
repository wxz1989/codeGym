package LinkedList;

import Factory.*;
import NodePkg.Node;

import java.util.ArrayDeque;
import java.util.LinkedList;
import java.util.Queue;

import org.omg.CORBA.Current;

import CommonUtil.LogUtil;
import RandNumGenerator.NodeValueGenerator;

class ListImpl extends List{
	private int nodeCount = 0;
	Node mHeadNode = null;
	
	public boolean Insert(Node nodeToInsert){
		
		LogUtil.Begin();
		LogUtil.End();
		return false;
	}
	public void InsertAt(Node nodeToInsert, int iIndex){
		
	}
	public boolean Delete(Node nodeToDelete){
		return false;
	}
	public Node Search(Node nodeToInsert){
		return null;
	}
	
	public boolean Insert(int nodeToInsert){
		
		LogUtil.Begin();
				
		Integer value = new Integer(nodeToInsert);
		/*
		 * Using managed node factory object, you don't have to delete factory object. 
		 * It will be deleted by the owner itself(FactoryManager)
		 */
		Factory nodeFactory= FactoryManager.GetManagedNodeFactory();
		Node newNode =  nodeFactory.CreateNode();
		newNode.SetValue(value);
		
		if (mHeadNode == null ){
			mHeadNode = newNode;
			nodeCount++;
		} else {
			Node tempNode = null;
			tempNode = mHeadNode;
			while (tempNode.GetNextReference() != null){
				tempNode = tempNode.GetNextReference();
			}
			tempNode.SetNextReference(newNode);
			nodeCount++;
		}
		
		LogUtil.End();
		return false;
	}
	public void InsertAt(int nodeToInsert, int iIndex){
		LogUtil.Begin();
		
		
		if ( iIndex < 0 || nodeCount <= 0 || iIndex > nodeCount){
			StringBuilder builder = new StringBuilder();
			builder.append("Insertion is possible only between ");
			builder.append("0 and ");
			builder.append(nodeCount);
			System.out.println(builder.toString());
			return;
		}
		Integer value = new Integer(nodeToInsert);
		/*
		 * Using managed node factory object, you don't have to delete factory object. 
		 * It will be deleted by the owner itself(FactoryManager)
		 */
		Factory nodeFactory= FactoryManager.GetManagedNodeFactory();
		Node newNode =  nodeFactory.CreateNode();
		newNode.SetValue(value);
		
		if (mHeadNode == null ){
			mHeadNode = newNode;
			nodeCount++;
		} else {				//Node is not the first one to be inserted
			
			int count = 0;
			Node tempNode = mHeadNode;
			while ( tempNode != null ){
				
				if ( count == iIndex-1 ){
					newNode.SetNextReference(tempNode.GetNextReference());
					tempNode.SetNextReference(newNode);
					nodeCount++;
					break;
				}
				tempNode = tempNode.GetNextReference();
				count++;
			}
		}
		
		LogUtil.End();
	}
	public boolean Delete(int nodeToInsert){
		
		System.out.println("Deleting["+ nodeToInsert +"]");
		
		if (mHeadNode == null ) {
			return false;
		}
		
		int nodeValue = Integer.parseInt(mHeadNode.Getvalue().toString()); 
		if( nodeValue == nodeToInsert ) {
			
			Node tempNode = mHeadNode;
			mHeadNode = mHeadNode.GetNextReference();
			tempNode = null;
			
			nodeCount--;
			if ( nodeCount < 0){
				nodeCount = 0;
			}
			return true;
		}
		
		Node tempNode = null;
		tempNode = mHeadNode;

		while ( tempNode != null ){
			nodeValue = Integer.parseInt(tempNode.GetNextReference().Getvalue().toString()); 
			if( nodeValue == nodeToInsert ) {
				
				if (tempNode.GetNextReference().GetNextReference() != null ){
					tempNode.SetNextReference(tempNode.GetNextReference().GetNextReference());	
				} else {
					tempNode.SetNextReference(null);
				}
				
				nodeCount--;
				if ( nodeCount < 0){
					nodeCount = 0;
				}
				return true;
			}
			tempNode = tempNode.GetNextReference();
		}
		
		return false;
	}
	public Node Search(int nodeToInsert){
		if ( mHeadNode == null ) {
			return null;
		}
		
		int nodeValue = Integer.parseInt(mHeadNode.Getvalue().toString()); 
		if( nodeValue == nodeToInsert ) {
			return mHeadNode;
		}
		
		Node tempNode = null;
		tempNode = mHeadNode;

		while ( tempNode != null ){
			nodeValue = Integer.parseInt(tempNode.Getvalue().toString()); 
			if( nodeValue == nodeToInsert ) {
				return tempNode;
			}
			tempNode = tempNode.GetNextReference();
		}
		return null;
	}
	
	public void Traverse(){
		if ( mHeadNode == null || nodeCount == 0 ){
			return;
		}
		int count = 0;
		Node tempNode = null;
		tempNode = mHeadNode;
		System.out.println("Tree Data");
		while ( tempNode != null ){
			System.out.printf("%s ", tempNode.Getvalue().toString());
			if ( nodeCount > 1){
				if ( count < nodeCount-1 )
					System.out.printf("%s ", ",");
			}
			tempNode= tempNode.GetNextReference();
			count++;
		}
		System.out.println("");
	}

	public boolean RemoveAll(){
		if ( mHeadNode == null ) return false;
		while (mHeadNode!= null){
			mHeadNode = mHeadNode.GetNextReference();
			RemoveAll();
			mHeadNode = null;			// Make is ready for garbage collections
		}
		nodeCount = 0;
		return true;
	}
	public boolean DeleteAll(){
		if ( mHeadNode == null ) return false;
		while (mHeadNode!= null){
			mHeadNode = mHeadNode.GetNextReference();
			DeleteAll();
			mHeadNode  = null;		//Make is ready for garbage collection
		}	
		nodeCount = 0;
		return true;
	}
	
	public int Size(){
		return nodeCount;
	}
	
	public Node GetRandom(){
		int number = NodeValueGenerator.getRandomIntForNode(nodeCount);
		System.out.println("Probability of finding " +number+ " is [1/"+nodeCount+ "]");
		if( number == 0 ){
			return mHeadNode;
		}
		int iIndex = 0;
		Node tempNode = mHeadNode;
		while ( tempNode != null ){
			if ( number == iIndex ){
				return tempNode;
			}
			iIndex++;
			tempNode = tempNode.GetNextReference();
		}
		return null;
	}
	@Override
	/*
	 * this function non-recursively reverses existing linked list by swapping pointers
	 * but it uses extra memory and consumes time , takes a container and loops through it.
	 * 
	 */
	public void Reverse() {
		// TODO Auto-generated method stub
		/*
		 * This code reverses only values and not pointers
		 */
		if ( mHeadNode == null ){
			System.out.print("List is empty");
			return;
		}
		
		/*
		 * Could have used stack and would have implemented the same
		 */
		ArrayDeque<Node> deQueue = new ArrayDeque<Node>();
		while (mHeadNode.GetNextReference()!= null){
			deQueue.add(mHeadNode);
			mHeadNode = mHeadNode.GetNextReference();
		}
		System.out.print("Queue Size:" + deQueue.size());
		
		Traverse();
		Node tempNode = mHeadNode;
		while ( deQueue.size() > 0 ){
			Node popedNode = deQueue.pollLast();
			if ( tempNode != null){
				tempNode.SetNextReference(popedNode);
				tempNode = tempNode.GetNextReference();
				
				System.out.println("Current Queue Size:" + deQueue.size());
				
				if ( deQueue.size() == 0 ){
					popedNode.SetNextReference(null);
					System.out.print("assign null to the last element");
				}
			}
		}
		deQueue = null;
		Traverse();
	}
	@Override
	public void Sort() {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void SortAlternativeElements() {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void Clone() {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void RemoveDuplicate() {
		// TODO Auto-generated method stub
		
	}
	@Override
	public Node ReverseR() {
		// TODO Auto-generated method stub
		if ( mHeadNode == null  || mHeadNode.GetNextReference() == null ){
			return null;
		}
		Node current = mHeadNode; 
		mHeadNode = mHeadNode.GetNextReference();
		Node nextNode = mHeadNode;
		
		ReverseR();
		nextNode.SetNextReference(current);
		current.SetNextReference(null);
		return mHeadNode;
	}
	@Override
	public Node GetHeadNode() {
		// TODO Auto-generated method stub
		if ( mHeadNode != null ){
			return mHeadNode;
		}
		return null;
	}
	@Override
	public Node ReverseLite() {
		// TODO Auto-generated method stub
		Node prevNode = null;
		Node nextNode = null;
		if ( mHeadNode == null ){
			return null;
		}
		while (mHeadNode != null){
			nextNode = mHeadNode.GetNextReference();
			mHeadNode.SetNextReference(prevNode);
			
			prevNode = mHeadNode;
			mHeadNode = nextNode;
		}
		mHeadNode = prevNode;
		return mHeadNode;
	}
	@Override
	public Node ReverseKElements(int noToSwap) {
		// TODO Auto-generated method stub
		
		if ( mHeadNode == null || noToSwap <=1 || noToSwap  >= nodeCount){
			return null;
		}

		Node tempNode = mHeadNode;
		while ( tempNode != null ){
			Node prevNode = null;
			Node nextNode = null;
			int count = 0;
			do{
				try{
					nextNode = tempNode.GetNextReference();
					tempNode.SetNextReference(prevNode);
					prevNode = tempNode;
					tempNode = nextNode;
				}
				catch( NullPointerException e){
					e.printStackTrace();
				}
				count++;

			}while ( count < noToSwap ) ;
			
			if ( count == noToSwap){
				mHeadNode = prevNode;
			}
			
		}
		return null;
	}
}


