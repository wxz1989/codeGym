package TreeLibrary;

public class TreeFactory extends AbstractFactory{
	public ITreeInterface CreateTree(){
		return new TreeImpl	();
	}
	public INodeInterface CreateNode(){
		//ToDo: Do nothing as, tree factory is not responsible for creating Node.
		return null;
	}
}