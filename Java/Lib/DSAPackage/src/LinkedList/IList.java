package LinkedList;

import NodePkg.Node;

interface IList{
	public boolean Insert(Node nodeToInsert);
	public void InsertAt(Node nodeToInsert, int iIndex);
	public boolean Delete(Node nodeToDelete);
	public Node Search(Node nodeToSearch);
	
	public void Traverse();
	public boolean RemoveAll();
	public boolean DeleteAll();
	
	public Node GetHeadNode();
	public int Size();
	public Node GetRandom();
	
	/*
	 * Possible I.Q. API implementation
	 * 1. Reverse LL
	 * 2. Sort a LL
	 * 3. Sort a linked list which is sorted alternatively
	 * 4. Clone LL
	 * 5. Remove duplicate items
	 */
	
	/*
	 * Non-recursive implementation of reverse API
	 * this API doesn't return updated HeadNode, call GetHeadNode to get updated headNode.
	 */
	public void Reverse();
	public Node ReverseLite();
	
	/*
	 * Recursive implementation of reverse API
	 */
	public Node ReverseR();
	
	public Node ReverseKElements(int noToSwap);
	
	public void Sort();
	public void SortAlternativeElements();
	public void Clone();
	public void RemoveDuplicate();	
	
	public boolean Insert(int nodeToInsert);
	public void InsertAt(int nodeToInsert, int iIndex);
	public boolean Delete(int nodeToDelete);
	public Node Search(int nodeToSearch);
}