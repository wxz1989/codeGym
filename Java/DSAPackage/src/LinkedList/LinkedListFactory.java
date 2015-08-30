package LinkedList;


import NodePkg.Node;
import Tree.Tree;
import Factory.*;

public class LinkedListFactory extends Factory{

	@Override
	public Tree CreateTree() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Node CreateNode() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public List CreateLinkedList() {
		// TODO Auto-generated method stub
		return new ListImpl();
	}
	
}