package Tree;

import Factory.Factory;
import LinkedList.List;
import NodePkg.Node;

public class TreeFactory extends Factory{
	public Tree CreateTree(){
		return new TreeImpl	();
	}
	public Node CreateNode(){
		//ToDo: Do nothing as, tree factory is not responsible for creating Node.
		return null;
	}
	@Override
	public List CreateLinkedList() {
		// TODO Auto-generated method stub
		return null;
	}
}