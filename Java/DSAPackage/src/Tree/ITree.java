package Tree;

import NodePkg.Node;

public interface ITree{
	
	/*
	 * Exo-skeleton APIs, Initialization and cleanup
	 */
	public boolean Init();
	public boolean ClearUp();
	
	public Node GetRootNode();
	public void SetRootNode(Node newRootNode);
	
	/*
	 * Manipulation APIs
	 */
	public boolean Insert(Object objValue);
	/*public boolean Insert(int nodeVal);
	public boolean Insert(String nodeValue);
	public boolean Insert(long nodeVal);
	public boolean Insert(double nodeValue);
	public boolean Insert(float nodeValue);*/
	
	public Object Find(Object objValueToFind);
	/*public boolean Find(int nodeVal);
	public boolean Find(String nodeValue);
	public boolean Find(long nodeVal);
	public boolean Find(double nodeValue);
	public boolean Find(float nodeValue);*/
	
	public boolean Delete(Object objValueToFind);
/*	public boolean Delete(int nodeVal);
	public boolean Delete(String nodeValue);
	public boolean Delete(long nodeVal);
	public boolean Delete(double nodeValue);
	public boolean Delete(float nodeValue);*/
	
	/*
	 * Utility APIs
	 */
	public void Diagnostics();
	public void Traversal(int traversalType);
}
