package TreeLibrary;

import Factory.Factory;

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
}