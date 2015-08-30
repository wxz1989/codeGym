package Factory;

import NodePkg.Node;

import LinkedList.*;
import Tree.Tree;

public abstract class Factory implements IFactory{
	public abstract Tree CreateTree();
	public abstract Node CreateNode();
	public abstract List CreateLinkedList();
}
