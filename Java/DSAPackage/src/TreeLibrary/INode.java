package TreeLibrary;

interface INode{
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
	public void SetValue(Object objValue);
	public Object Getvalue();
	
	public void SetNextReference(Node nextRef);
	public void SetPrevReference(Node prevRef);
	
	public Node GetNextReference();
	public Node GetPrevReference();
	
	public void SetNull(Node refToMakeNull);
}