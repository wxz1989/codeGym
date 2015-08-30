package Factory;

public class FactoryManager{
	private static Factory treeFactory = null;
	private static Factory linkedListFactory = null;
	private static Factory nodeFactory = null;
	
	private static boolean mInit = false;
	
	public static Factory GetManagedLinkedListFactory(){
		if (mInit == false ){
			FactoryImpl.Init();
			mInit = true;
		}
		if ( linkedListFactory == null ){
			Factory factory = FactoryImpl.GetFactory("linkedList_factory");
			linkedListFactory = factory;
		}
		return linkedListFactory;
	}
	public static Factory GetManagedTreeFactory(){
		if (mInit == false ){
			FactoryImpl.Init();
			mInit = true;
		}
		if ( treeFactory == null ){
			Factory factory = FactoryImpl.GetFactory("tree_factory");
			treeFactory = factory;
		}
		return treeFactory;
	}
	
	public static Factory GetManagedNodeFactory(){
		if (mInit == false ){
			FactoryImpl.Init();
			mInit = true;
		}
		if ( nodeFactory == null ){
			Factory factory = FactoryImpl.GetFactory("node_factory");
			nodeFactory = factory;
		}
		return nodeFactory;
	}
	public void finalize()	{
		treeFactory = null;
		nodeFactory = null;
		linkedListFactory = null;
	}
}