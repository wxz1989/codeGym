package Factory;

import TreeLibrary.ITree;
import TreeLibrary.Node;

interface IFactory{
	public ITree CreateTree();
	public Node CreateNode();
}