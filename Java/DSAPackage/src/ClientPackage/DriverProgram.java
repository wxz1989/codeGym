package ClientPackage;
import Factory.Factory;
import Factory.FactoryProvider;
import TreeLibrary.*;


public class DriverProgram{
	
	public static void main(String args[]){

		/* Factory Provide is forcing this API on the user as 
		 * currently there is no other way
		 * and in future this api would be usefull as factories would be registered in a file and 
		 * would be read byt factory Provider and would be maintained byt it.
		 */
		FactoryProvider.Init();
		Tree treeHandle = null;
		Factory treeFactory= FactoryProvider.GetFactory("tree_factory");
		treeHandle = treeFactory.CreateTree();
		treeHandle.Init();
		
		for ( int i = 0; i < 5 ; i++){
			Long nodeValue = new Long(NodeValueGenerator.getRandomIntForNode());
			treeHandle.Insert(nodeValue);
			nodeValue = null;
		}		
		treeHandle = null; 
		treeFactory = null;	
	}
}