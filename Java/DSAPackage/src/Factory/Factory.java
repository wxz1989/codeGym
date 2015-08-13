package Factory;

import TreeLibrary.Node;
import TreeLibrary.Tree;

public abstract class Factory implements IFactory{
	public abstract Tree CreateTree();
	public abstract Node CreateNode();
}