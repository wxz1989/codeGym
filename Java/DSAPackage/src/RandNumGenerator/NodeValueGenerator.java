package RandNumGenerator;

import java.util.Random;

public class NodeValueGenerator extends Object{
	
	private static Random randNumGenerator = new Random();
	
	public NodeValueGenerator() {
		// TODO Auto-generated constructor stub
	}
	
	public void finalize(){
		randNumGenerator = null;
	}
	
	public static long getRandomLongForNode(){
		long randNum = randNumGenerator.nextLong();
		return randNum;
	}
	
	public static int getRandomIntForNode(int bound){
		if ( bound >=0 ){
			int randNum = randNumGenerator.nextInt(bound);
			return randNum;
		}
		return -1;
	}
	
	public static int getRandomIntForNode(){
		int randNum = randNumGenerator.nextInt();
		return randNum;
	}
}