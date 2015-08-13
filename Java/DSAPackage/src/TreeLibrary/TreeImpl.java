package TreeLibrary;

import Factory.Factory;
import Factory.FactoryProvider;

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
		mNodeFactory = FactoryProvider.GetFactory("node_factory");
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
			/*while ( temp != null ){
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
			}*/
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
	
	/*
	 * Utility APIs
	 */
	public void Diagnostics(){
		Node tempNode = mRootNode; 
		while( tempNode  != null ){
			System.out.println("Node Status >>>" + "Value:" + tempNode.Getvalue() + " <<< ");
		}
	}
	public void Traversal(TreeTraversalType traversalType){
		
	}
}
