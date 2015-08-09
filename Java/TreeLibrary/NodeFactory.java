package TreeLibrary;

class NodeFactory extends AbstractFactory{
	public INodeInterface CreateNode(){
		return new NodeImpl();
	}

	@Override
	public ITreeInterface CreateTree() {
		// TODO Auto-generated method stub
		System.out.println("I am not able to do so!");
		return null;
	}
}