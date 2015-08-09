package TreeLibrary;

abstract class AbstractTree implements ITreeInterface{
	
	abstract public boolean Init();
	abstract public boolean ClearUp();
	abstract public INodeInterface GetRootNode();
	
	abstract public void SetRootNode(INodeInterface newRootNode);
	/*
	 * Manipulation APIs
	 */
	abstract public boolean Insert(Object objValue);
	abstract public Object Find(Object objValueToFind);
	abstract public boolean Delete(Object objValueToFind);
	
	/*
	 * Utility APIs
	 */
	abstract public void Diagnostics();
	abstract public void Traversal(TreeTraversalType traversalType);
}