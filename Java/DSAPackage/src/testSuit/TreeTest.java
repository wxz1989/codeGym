package testSuit;

class TreeTest extends TestSuit{
	public void PositiveTest(){
		/* Factory Provide is forcing this API on the user as 
		 * currently there is no other way
		 * and in future this api would be usefull as factories would be registered in a file and 
		 * would be read byt factory Provider and would be maintained byt it.
		 */
		/*
		Tree treeHandle = null;
		Factory treeFactory= FactoryManager.GetManagedTreeFactory();
		treeHandle = treeFactory.CreateTree();
		treeHandle.Init();
		
		//for ( int i = 0; i < 5 ; i++){
//			Long nodeValue = new Long(NodeValueGenerator.getRandomIntForNode());
		treeHandle.Insert(null);
		
		;
		treeHandle.Traversal(TreeTraversalTypes.IN_ORDER);
		treeHandle.Traversal(TreeTraversalTypes.PRE_ORDER);
		treeHandle.Traversal(TreeTraversalTypes.POST_ORDER);
		
	//		nodeValue = null;
		
		
		*/
		
		
		
//		}		
		//treeHandle = null; 
		//treeFactory = null;
	}
	public void NegativeTest(){
		
	}
	@Override
	public void NotifyResults() {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void PrintResult() {
		// TODO Auto-generated method stub
		
	}
}