package Tree;

import CommonUtil.LogUtil;
import Factory.*;
import NodePkg.Node;

class TreeImpl extends Tree{
	
	private Node mRootNode;
	private boolean mIsTreeBalanced;
	private int mNodeCount;
	
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
		
		//Root Node 
		Integer newValue = new Integer("55");
		newNode.SetValue(newValue);
		
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);
		
		mRootNode = newNode;
		newValue = null;
		
		
		//Root-Right node
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}
		
		newValue =  new Integer("88");
		newNode.SetValue(newValue);
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);
		
		mRootNode.SetNextReference(newNode);
		newValue = null;
		
		//Root-Left Node 
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}
		
		newValue = new Integer("49");
		newNode.SetValue(newValue);
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);
		
		mRootNode.SetPrevReference(newNode);
		newValue = null;
		
		
		//Root-Left-Right Node 
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}

		newValue = new Integer("50");
		newNode.SetValue(newValue);
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);

		mRootNode.GetPrevReference().SetNextReference(newNode);
		newValue = null;
		
		//Root-Right-Left Node 
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}

		newValue = new Integer("59");
		newNode.SetValue(newValue);
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);

		mRootNode.GetNextReference().SetPrevReference(newNode);
		newValue = null;
		
		//Root-left-left Node 
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}

		newValue = new Integer("51");
		newNode.SetValue(newValue);
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);

		mRootNode.GetPrevReference().SetPrevReference(newNode);
		newValue = null;
		
		//Root-right-right  Node 
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}

		newValue = new Integer("99");
		newNode.SetValue(newValue);
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);

		mRootNode.GetNextReference().SetNextReference(newNode);
		newValue = null;
		
		/*
		if ( objValue == null || mNodeFactory == null ){
			return false;
		}
		
		newNode = mNodeFactory.CreateNode();
		if ( newNode == null ){
			return false;
		}
		
		newNode.SetValue(objValue);
		newNode.SetNextReference(null);
		newNode.SetPrevReference(null);
		
		objValue = null;
		
		if ( mRootNode == null ){			//If root node is null then this one should be the root node.
			mRootNode = newNode;
			return true;
		} 
		else {
			System.out.println("Current Node:"+ newNode.Getvalue().toString() + "\nRoot Node:"  +  mRootNode.Getvalue().toString());
						
			Node temp = mRootNode;
			/* Tree Insertion logic, but may not be accurate.
			 * while ( temp != null ){
				int value1 =  Integer.parseInt(newNode.Getvalue().toString());
				int value2 =  Integer.parseInt(mRootNode.Getvalue().toString());
				
				//Check values of the nodes in question and insert accordingly (Small element on left and large elemtn on right)
				if ( value1 >= value2 ){
					if ( mRootNode.GetNextReference() != null ){
						temp = mRootNode.GetNextReference();
					} else {			//there are not left and right elements, then make one
						mRootNode.SetNextReference(newNode);
					}

				} else {
					if ( mRootNode.GetPrevReference() != null ){
						temp = mRootNode.GetPrevReference();
					} else {			//there are not left and right elements, then make one
						mRootNode.SetPrevReference(newNode);
					}
				}
			}
		}
		mNodeCount++;
		*/
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
		while( rootNode != null ){
			InOrder(rootNode.GetPrevReference());
			System.out.print("Nodevalue:" + rootNode.Getvalue().toString() +" \n");
			InOrder(rootNode.GetNextReference());
		}
		return;
	}
	
	private void PreOrder(Node rootNode){
		
		while( rootNode != null ){
			System.out.print("Nodevalue:" + rootNode.Getvalue().toString()+" \n");
			PreOrder(rootNode.GetPrevReference());
			PreOrder(rootNode.GetNextReference());
		}
		return;
	}
	
	private void PostOrder(Node rootNode){
		while( rootNode != null ){
			PostOrder(rootNode.GetPrevReference());
			PostOrder(rootNode.GetNextReference());
			System.out.print("Nodevalue:" + rootNode.Getvalue().toString()+" \n");
		}
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
}
