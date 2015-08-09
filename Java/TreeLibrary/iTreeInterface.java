package TreeLibrary;

interface ITreeInterface{
	
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
	public boolean Init();
	public boolean ClearUp();
	
	public INodeInterface GetRootNode();
	public void SetRootNode(INodeInterface newRootNode);
	
	/*
	 * Manipulation APIs
	 */
	public boolean Insert(Object objValue);
	public Object Find(Object objValueToFind);
	public boolean Delete(Object objValueToFind);
	
	/*
	 * Utility APIs
	 */
	public void Diagnostics();
	public void Traversal(TreeTraversalType traversalType);
}
