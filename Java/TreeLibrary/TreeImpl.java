package TreeLibrary;


class TreeImpl extends AbstractTree{
	
	private INodeInterface mRootNode;
	private boolean mIsTreeBalanced;
	private int mNodeCount;
	
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
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
	public INodeInterface GetRootNode(){
		return mRootNode;
	}
	
	public void SetRootNode(INodeInterface newRootNode){
		if ( mRootNode != null ){
			mRootNode = null;
		}
		mRootNode=newRootNode;
	}
	/*
	 * Manipulation APIs
	 */
	public boolean Insert(Object objValue){
		
		mNodeCount++;
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
		System.out.println("Node Status >>>");
		System.out.println("Value:" + this.toString());
		System.out.println(" <<< ");
	}
	public void Traversal(TreeTraversalType traversalType){
		
	}
}