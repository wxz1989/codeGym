package NodePkg;

import Factory.Factory;
import LinkedList.List;
import Tree.Tree;

public class NodeFactory extends Factory{
	public Node CreateNode(){
		return new NodeImpl();
	}

	@Override
	public Tree CreateTree() {
		// TODO Auto-generated method stub
		System.out.println("I am not able to do so!");
		return null;
	}

	@Override
	public List CreateLinkedList() {
		// TODO Auto-generated method stub
		return null;
	}
}