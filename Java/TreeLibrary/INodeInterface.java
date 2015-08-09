package TreeLibrary;

interface INodeInterface{
	
	
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
	public void SetValue(Object objValue);
	public Object Getvalue(Object objValueToGet);
	
	public void SetNextReference(INodeInterface nextRef);
	public void SetPrevReference(INodeInterface prevRef);
	
	public void SetNull(INodeInterface refToMakeNull);
}