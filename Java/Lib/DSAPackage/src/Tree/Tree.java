package Tree;

import NodePkg.Node;

public abstract class Tree extends Object implements ITree{
	
	abstract public boolean Init();
	abstract public boolean ClearUp();
	abstract public Node GetRootNode();
	
	abstract public void SetRootNode(Node newRootNode);
	/*
	 * Manipulation APIs
	 */
	abstract public boolean Insert(Object objValue);
	/*abstract public boolean Insert(int nodeVal);
	abstract public boolean Insert(String nodeValue);
	abstract public boolean Insert(long nodeVal);
	abstract public boolean Insert(double nodeValue);
	abstract public boolean Insert(float nodeValue);*/
	
	abstract public Object Find(Object objValueToFind);
	/*abstract public boolean Find(int nodeVal);
	abstract public boolean Find(String nodeValue);
	abstract public boolean Find(long nodeVal);
	abstract public boolean Find(double nodeValue);
	abstract public boolean Find(float nodeValue);*/
	
	abstract public boolean Delete(Object objValueToFind);
	/*abstract public boolean Delete(int nodeVal);
	abstract public boolean Delete(String nodeValue);
	abstract public boolean Delete(long nodeVal);
	abstract public boolean Delete(double nodeValue);
	abstract public boolean Delete(float nodeValue);*/
	
	/*
	 * Utility APIs
	 */
	abstract public void Diagnostics();
	abstract public void Traversal(int traversalType);
}