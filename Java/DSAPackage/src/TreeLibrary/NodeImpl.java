package TreeLibrary;

class NodeImpl extends Node{
	/*
	 * Cardinal properties
	 */
	private Object mValue;
	private Node 	mNextRef;
	private Node	mPrevRef;

	public NodeImpl(){
		LogUtil.Begin();
		mValue = null;
		mNextRef = null;
		mPrevRef = null;
		LogUtil.End();
	}
	
	public void finalize(){
		LogUtil.Begin();
		mValue = null;
		mNextRef = null;
		mPrevRef = null;
		LogUtil.End();
	}
	
	public void SetValue(Object objValue){
		if ( objValue != null ){
			mValue = objValue;	
			objValue = null;
		}
		Diagnostics();
	}
	public Object Getvalue(){
		Diagnostics();
		return mValue;
	}
	
	public void SetNextReference(Node nextRef){
		mNextRef = nextRef;
		Diagnostics();
	}
	public void SetPrevReference(Node prevRef){
		mPrevRef = prevRef;
		Diagnostics();
	}
	
	public Node GetNextReference(){
		if ( mNextRef != null ){
			return mNextRef;
		} else {
			return null;
		}
	}
	public Node GetPrevReference(){
		if ( mPrevRef != null ){
			return mPrevRef;
		} else {
			return null;
		}
	}
	
	public void SetNull(Node refToMakeNull){
		refToMakeNull = null;
		Diagnostics();
	}
	
	private void Diagnostics(){
		LogUtil.Log("Node Status:[%s]", mValue.toString());
	}
}