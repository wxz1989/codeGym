package testSuit;

import Factory.Factory;
import Factory.FactoryManager;
import RandNumGenerator.NodeValueGenerator;
import Tree.Tree;
import Tree.TreeTraversalTypes;

public class TreeTest extends TestSuit{
	public void PositiveTest(){
		/* Factory Provide is forcing this API on the user as 
		 * currently there is no other way
		 * and in future this api would be usefull as factories would be registered in a file and 
		 * would be read byt factory Provider and would be maintained byt it.
		 */
		
		Factory treeFactory= FactoryManager.GetManagedTreeFactory();
		Tree treeHandle = treeFactory.CreateTree();
		
		for ( int i = 0; i < 10 ; i++){
			Integer nodeValue = new Integer(NodeValueGenerator.getRandomIntForNode(100));
			System.out.println("New Node Value for BST : "+ nodeValue.toString());
			treeHandle.Insert(nodeValue);
		}
		System.out.println("\nInorder : ");
		treeHandle.Traversal(TreeTraversalTypes.IN_ORDER);
		System.out.println("\nPreOrder : ");
		treeHandle.Traversal(TreeTraversalTypes.PRE_ORDER);
		System.out.println("\nPortOrder : ");
		treeHandle.Traversal(TreeTraversalTypes.POST_ORDER);
		
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