package Factory;
import LinkedList.*;

import NodePkg.Node;
import Tree.ITree;

interface IFactory{
	public ITree CreateTree();
	public Node CreateNode();
	public List CreateLinkedList();
}