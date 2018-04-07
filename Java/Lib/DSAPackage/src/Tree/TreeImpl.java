package Tree;

import CommonUtil.LogUtil;
import Factory.*;
import NodePkg.Node;

class TreeImpl extends Tree{
	
	private Node mRootNode;
	private boolean mIsTreeBalanced;
	private int mNodeCount;
	private int mHeightOfTree;
	
	private Factory mNodeFactory = null; 
	
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
	public TreeImpl() {
		// TODO Auto-generated constructor stub
		mRootNode = null;
		mIsTreeBalanced = false;
		mNodeFactory = FactoryManager.GetManagedNodeFactory();
		mNodeCount = 0;	
		mHeightOfTree = 0;
	}
	public void finalize(){
		mRootNode = null;
		mIsTreeBalanced = false;
		mNodeCount = 0;
	}
	
	public boolean Init(){
		mRootNode = null;
		mIsTreeBalanced = false;
		mNodeCount = 0;
		return true;
	}
	public boolean ClearUp(){
		mRootNode = null;
		return true;
	}
	public Node GetRootNode(){
		return mRootNode;
	}
	
	public void SetRootNode(Node newRootNode){
		if ( mRootNode != null ){
			mRootNode = null;
		}
		mRootNode=newRootNode;
	}
	/*
	 * Manipulation APIs
	 */
	public boolean Insert(Object objValue){
		
		LogUtil.Begin();
		Node newNode = null;
		
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}
		
		newNode.SetValue(objValue);

		if ( mRootNode == null ){			//If root node is null then this one should be the root node.
			mRootNode = newNode;
			return true;
		} 
		else {
			System.out.println("Current Node:"+ newNode.Getvalue().toString() + "\nRoot Node:"  +  mRootNode.Getvalue().toString());
						
			Node temp = mRootNode;
			/* Tree Insertion logic, but may not be accurate.*/
			int value1 =  Integer.parseInt(newNode.Getvalue().toString());
			 while ( temp != null ){
				
				int value2 =  Integer.parseInt(temp.Getvalue().toString());
				
				//Check values of the nodes in question and insert accordingly (Small element on left and large elemtn on right)
				if ( value1 >= value2 ){
					if ( temp.GetNextReference() != null ){
						temp = temp.GetNextReference();
					} else {			//there are not left and right elements, then make one
						temp.SetNextReference(newNode);
						temp = null;
					}
				} else {
					if ( temp.GetPrevReference() != null ){
						temp = temp.GetPrevReference();
					} else {			//there are not left and right elements, then make one
						temp.SetPrevReference(newNode);
						temp= null;
					}
				}
			}
		}
		mNodeCount++;
		LogUtil.End();
		return true;
	}
	public Object Find(Object objValueToFind){
		return null;
	}
	public boolean Delete(Object objValueToFind){
		mNodeCount--;
		return false;
	}
	
	
	private void InOrder(Node rootNode){
		
		if( rootNode == null){ return; }
		
		InOrder(rootNode.GetPrevReference());
		System.out.print(rootNode.Getvalue().toString() +", ");
		InOrder(rootNode.GetNextReference());
		return;
	}
	
	private void PreOrder(Node rootNode){
		
		if( rootNode == null){ return; }
		System.out.print(rootNode.Getvalue().toString()+", ");
		PreOrder(rootNode.GetPrevReference());
		PreOrder(rootNode.GetNextReference());
		return;
	}
	
	private void PostOrder(Node rootNode){
		
		if( rootNode == null){ return; }
		PostOrder(rootNode.GetPrevReference());
		PostOrder(rootNode.GetNextReference());
		System.out.print( rootNode.Getvalue().toString()+", ");
		return;
	}

	/*
	 * Utility APIs
	 */
	public void Diagnostics(){
		Node tempNode = mRootNode; 
		while( tempNode  != null ){
			System.out.println("Node Status >>>" + "Value:" + tempNode.Getvalue() + " <<< ");
		}
	}
	public void Traversal(int traversalType){
		if ( mRootNode == null ) return;
		
		System.out.println("Traversal Type:" + traversalType);

		System.out.println("Height of this Tree is :" + HeightR(mRootNode));
		
		if ( traversalType == 0 ){
			PreOrder(mRootNode);
		} else if ( traversalType == 1){
			PostOrder(mRootNode);
		} else if ( traversalType == 2){
			InOrder(mRootNode);
		} else {
			System.out.println("Junk");
		}
	}
	
	private int HeightR(Node rootNode){
		
		int left = 0, right = 0;
		/*if ( rootNode == null){ return 0; }
		else{ 
			left = HeightR(rootNode.GetPrevReference());
			right = HeightR(rootNode.GetNextReference());
		}

		return (left > right ? left+1: right+1);*/
		
		
		if ( rootNode == null ){ return 0;}
		
		left++;
		left += HeightR(rootNode.GetPrevReference());
		right++;
		right += HeightR(rootNode.GetNextReference());
		
		return (left > right ? left : right);
	}
}
