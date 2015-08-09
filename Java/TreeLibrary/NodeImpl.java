package TreeLibrary;

class NodeImpl extends AbstractNode {
	/*
	 * Cardinal properties
	 */
	private Object mValue;
	private INodeInterface 	mNextRef;
	private INodeInterface	mPrevRef;

	public void SetValue(Object objValue){
		mValue = objValue;
		System.out.println("Value to set:"+ objValue.toString());
		System.out.println("Node Status >>> \n"+ mValue.toString());
	}
	public Object Getvalue(Object objValueToGet){
		//ToDo: Do nothing
		System.out.println("Node Status >>> \n"+ mValue.toString());
		System.out.println("Value to set:"+ objValueToGet.toString());
		return mValue;
	}
	
	public void SetNextReference(INodeInterface nextRef){
		//ToDo: Do nothing
		mNextRef = nextRef;
		System.out.println("Node Status >>> \n"+ mValue.toString());
	}
	public void SetPrevReference(INodeInterface prevRef){
		//ToDo: Do nothing
		mPrevRef = prevRef;
		System.out.println("Node Status >>> \n"+ mValue.toString());
	}
	
	public void SetNull(INodeInterface refToMakeNull){
		//ToDo: Do nothing
		refToMakeNull = null;
		System.out.println("Node Status >>> \n"+ mValue.toString());
	}
	
	private void Diagnostics(){
		System.out.println("Node Status >>> \n"+ mValue.toString());
		System.out.println(" <<< ");
	}
}