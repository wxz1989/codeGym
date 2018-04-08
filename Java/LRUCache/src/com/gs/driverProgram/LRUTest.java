package com.gs.driverProgram;

import java.lang.*;
import java.util.Random;
import com.gs.util.LRU.*;

public class LRUTest {
	public static void main(String args[]) {

		 LRUCache<Integer,Integer> cache = null;	     
	     cache = new LRUCache<Integer, Integer>();
	     
	     Random rKey = new Random();
	     Random rValue = new Random();

	     
	     while ( true ) {
	    	 try {
	    		 Thread.sleep(50);
	    	 }
	    	 catch ( Exception e) {
	    		 e.printStackTrace();
	    	 }
	    	 
	    	 int value = rValue.nextInt(20)+1;
	    	 int key = rKey.nextInt(10) + 1;
	    	 
	    	 //System.out.println("Key:[" + key + "], Value:["+ value + "]");
	    	 cache.set(key, value);
	    	 
	    	 //System.out.println("Get LeastRecently Used Key:[" + cache.getLeastRecentlyUsed()  + "]");
		     cache.getLRUStats();
	     }
	}
}
