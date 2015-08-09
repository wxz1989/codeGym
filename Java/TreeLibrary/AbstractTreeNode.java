package TreeLibrary;

abstract class AbstractTreeNode implements INodeInterface{
	
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
	abstract public void SetValue(Object objValue);
	abstract public Object Getvalue(Object objValueToGet);
	abstract public void SetNextReference(INodeInterface nextRef);
	abstract public void SetPrevReference(INodeInterface prevRef);
	abstract public void SetNull(INodeInterface refToMakeNull);
}