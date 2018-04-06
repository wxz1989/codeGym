package com.rakesh.threads;

import java.lang.*;
import java.util.*;
 
class CriticalResource {
	
	private final long MIN = 0;
	private final long MAX = 10;
	private static long counter;
	
	CriticalResource(){ counter = 0; }
	
	public void Increment() {
		if ( counter < MAX ) {
			++counter; 
		} else {
			counter = MAX;
		}
	}
	public long GetCS() { return counter; }
	
	public void Decrement() {
		if( counter > MIN )
			--counter;
		else
			counter=0;
	}
	
	public long GetMin() { return MIN; }
	public long GetMax() { return MAX; }
	
}
class Producer implements Runnable{
	private  CriticalResource cs;
	
	Producer(CriticalResource c){ cs = c; }
	
	public void run() {
		synchronized(cs) {
			while(true) {
				
				if( cs.GetCS() == cs.GetMax() ) {
					try {
						cs.wait();
					} catch ( Exception exe ) {
						exe.printStackTrace();
					}
				} else {
					try {
						Thread.sleep(500);
						cs.Increment();
					} catch ( Exception exe ) {
						exe.printStackTrace();
					}
					System.out.println("Produced:[" + cs.GetCS() + "]");
					cs.notify();
				}
			}
		}
	}
}

class Consumer implements Runnable{
	
	private  CriticalResource cs;
	private final long THREAD_SLEEP_TIME;

	Consumer(CriticalResource c, long st){ cs = c; THREAD_SLEEP_TIME = st;}
	public void run() {
		System.out.println( Thread.currentThread().getName() + " is up and waiting...");
		while (true) {
			synchronized ( cs ) {
				if ( cs.GetCS() == cs.GetMin() ) {
					try {
						cs.wait();
					} catch (Exception exe ) {
						exe.printStackTrace();
					}
				} else {
					System.out.println(Thread.currentThread().getName() +"[" + cs.GetCS() + "]");
					try {
						Thread.sleep(THREAD_SLEEP_TIME);
						cs.Decrement();
					} catch ( Exception exe ) {
						exe.printStackTrace();
					}
					cs.notify();
				}
			}
		}
	}
}

public class ThreadTest  {
	
	private static final int POOL_SIZE = 5;
	public static void main(String args[]) {
		
		CriticalResource cs = new CriticalResource();
		
		Thread p = new Thread (new Producer(cs));
		p.start();
		
		/*Thread c1 = new Thread(new Consumer(cs, 500), "Consumer_1");
		c1.start();
		
		Thread c2 = new Thread(new Consumer(cs,50), "Consumer_2");
		c2.start();
		
		Thread c3 = new Thread(new Consumer(cs,1000), "Consumer_3");
		c3.start();	
		
		Thread c4 = new Thread(new Consumer(cs,500), "Consumer_4");
		c4.start();	
		
		Thread c5 = new Thread(new Consumer(cs,10000), "Consumer_5");
		c5.start();*/
		
		for ( int i = 0; i< POOL_SIZE;i++) {
			String tName = "Consumer_" + (i+1);
			(new Thread(new Consumer(cs,100), tName)).start();
		}
		
		cs = null;		
	}
}
