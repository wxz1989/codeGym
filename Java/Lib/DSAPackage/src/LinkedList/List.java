package LinkedList;

import NodePkg.Node;

public abstract class List extends Object implements IList{
	abstract public boolean Insert(Node nodeToInsert);
	abstract public void InsertAt(Node nodeToInsert, int iIndex);
	abstract public boolean Delete(Node nodeToDelete);
	abstract public Node Search(Node nodeToSearch);
	
	abstract public Node GetHeadNode();
	abstract public int Size();
	abstract public Node GetRandom();
	
	/*
	 * Non-recirsive API, consuming extra memory and swaping pointers
	 * @see LinkedList.IList#Reverse()
	 */
	abstract public void Reverse();
	/*
	 * Non recursive, no extra memory consumption API.
	 * Reversing Linked list pointers and not swapping it's values.
	 * @see LinkedList.IList#ReverseLite()
	 * 
	 */
	abstract public Node ReverseLite();
	
	/*
	 * Recursive API, swaping pointers but doesn't return the new head pointer
	 * @see LinkedList.IList#ReverseR(NodePkg.Node)
	 */
	abstract public Node ReverseR();
	abstract public Node ReverseKElements(int noToSwap);
	
	abstract public void Sort();
	abstract public void SortAlternativeElements();
	abstract public void Clone();
	abstract public void RemoveDuplicate();
	
	abstract public void Traverse();
	abstract public boolean RemoveAll();
	abstract public boolean DeleteAll();
	
	abstract public boolean Insert(int nodeToInsert);
	abstract public void InsertAt(int nodeToInsert, int iIndex);
	abstract public boolean Delete(int nodeToDelete);
	abstract public Node Search(int nodeToSearch);
}