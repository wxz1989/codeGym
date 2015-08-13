package TreeLibrary;

import Factory.Factory;

public class TreeFactory extends Factory{
	public Tree CreateTree(){
		return new TreeImpl	();
	}
	public Node CreateNode(){
		//ToDo: Do nothing as, tree factory is not responsible for creating Node.
		return null;
	}
}