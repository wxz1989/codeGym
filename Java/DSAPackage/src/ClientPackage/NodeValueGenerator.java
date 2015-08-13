package ClientPackage;

import java.util.Random;

class NodeValueGenerator extends Object{
	
	private static Random randNumGenerator = new Random();;
	
	public NodeValueGenerator() {
		// TODO Auto-generated constructor stub
	}
	
	public void finalize(){
		randNumGenerator = null;
	}
	
	public static long getRandomLongForNode(){
		long randNum = randNumGenerator.nextLong();
		System.out.println("New RandomNumber is :"+ randNum );
		return randNum;
	}
	
	public static int getRandomIntForNode(){
		int randNum = randNumGenerator.nextInt();
		System.out.println("New RandomNumber is :"+ randNum );
		return randNum;
	}
}