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
	private static long THREAD_SLEEP_TIME;

	Consumer(CriticalResource c, long st){ cs = c; THREAD_SLEEP_TIME = st;}
	public void run() {
		System.out.println("Consumer is up and waiting...");
		while (true) {
			synchronized ( cs ) {
				if ( cs.GetCS() == cs.GetMin() ) {
					try {
						cs.wait();
					} catch (Exception exe ) {
						exe.printStackTrace();
					}
				} else {
					System.out.println(Thread.currentThread().getName() +" Consuming:[" + cs.GetCS() + "]");
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
	
	public static void main(String args[]) {
		
		CriticalResource cs = new CriticalResource();
		
		Thread p = new Thread (new Producer(cs));
		p.start();
		
		Thread c = new Thread(new Consumer(cs, 500), "Consumer_1");
		c.start();
		
		Thread c1 = new Thread(new Consumer(cs,100), "Consumer_2");
		c1.start();	
		
	}
}
