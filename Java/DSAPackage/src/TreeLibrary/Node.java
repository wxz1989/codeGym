package TreeLibrary;

public abstract class Node extends Object implements INode
{
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
	abstract public void SetValue(Object objValue);
	abstract public Object Getvalue();
	
	abstract public void SetNextReference(Node nextRef);
	abstract public void SetPrevReference(Node prevRef);
	
	abstract  public Node GetNextReference();
	abstract public Node GetPrevReference();
	
	abstract public void SetNull(Node refToMakeNull);
}