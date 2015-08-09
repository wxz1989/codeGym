package TreeLibrary;

import TreeLibrary.FactoryProvider;
import TreeLibrary.IFactory;
import TreeLibrary.INodeInterface;

public class DriverProgram{
	
	public static void main(String args[]){
		
		/* Factory Provide is forcing this API on the user as 
		 * currently there is no other way
		 * and in future this api would be usefull as factories would be registered in a file and 
		 * would be read byt factory Provider and would be maintained byt it.
		 */
		FactoryProvider.Init();
		
		IFactory factoryProvider = FactoryProvider.GetFactory("node_factory");
		INodeInterface nodeRef = factoryProvider.CreateNode();
		
		Integer nodeValue = new Integer(50);
		nodeRef.SetValue(nodeValue);
		
		factoryProvider = null;
		nodeRef = null;
	}
}