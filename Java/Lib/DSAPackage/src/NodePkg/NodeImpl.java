package NodePkg;

import CommonUtil.LogUtil;

public class NodeImpl extends Node{
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
	}
	public Object Getvalue(){
		return mValue;
	}
	
	public void SetNextReference(Node nextRef){
		mNextRef = nextRef;
	}
	public void SetPrevReference(Node prevRef){
		mPrevRef = prevRef;
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
	}
	
	private void Diagnostics(){
		LogUtil.Log("Node Status:[%s]", mValue.toString());
	}
}