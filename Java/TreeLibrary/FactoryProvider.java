package TreeLibrary;

import java.util.*;

class FactoryProvider{
	
	//ToDo: Implement  a file(XML/JSON/Manifest file) module or implement a Serialize method
	 /* which read registered factories with this factory provider
	 *  every Concrete factory should have it's own manifest file stored in the same directory where this project resides.
	 * with name similar  to the name of that factory
	 * there would be a module which will parse all the manifest files and would maintain their list with factory provided.
	 */
	private static HashSet<String>  supportedFactories;
	public static void Init(){
		PrepareRegisteredFactoryList();
	}
	private static void PrepareRegisteredFactoryList(){
		supportedFactories.add(FactoryTypes.NODE_FACTORY);
		supportedFactories.add(FactoryTypes.TREE_FACTORY);
	}
	public static IFactory GetFactory(String strFacType){
		
		if ( supportedFactories.contains(strFacType) == false){ return null; }
		
		if ( strFacType.equalsIgnoreCase(FactoryTypes.NODE_FACTORY) == true ){
			return new NodeFactory();
		} else if (strFacType.equalsIgnoreCase(FactoryTypes.TREE_FACTORY) == true ){
			return new TreeFactory();
		}
		return null;
	}
}