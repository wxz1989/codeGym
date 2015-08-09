package TreeLibrary;


abstract class AbstractFactory implements IFactory{
	public abstract ITreeInterface CreateTree();
	public abstract INodeInterface CreateNode();
}