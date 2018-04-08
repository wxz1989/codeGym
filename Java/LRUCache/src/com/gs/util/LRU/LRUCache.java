package com.gs.util.LRU;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;


class LRUStats{
	private boolean change = false;
	private int hitCount, misCount, evictCount;
	
	public LRUStats() {
		hitCount= 0;
		misCount= 0;
		evictCount = 0;
	}
	
	public LRUStats(int h, int m, int e) {
		hitCount = h;
		misCount = m;
		evictCount = e;
	}
	
	public void HitCount(Boolean up) {
		change = true;
		if ( up == true ) {
			hitCount++;
		} else {
			hitCount--;
		}
	}
	
	public void MisCount(Boolean up) {
		if ( up == true ) {
			misCount++;
		} else {
			misCount--;
		}
	}
	
	public void EvictCount(Boolean up) {
		if ( up == true ) {
			evictCount++;
		} else {
			evictCount--;
		}
	}
	
	public void ShowStats() {
		if ( change == true ) {

			System.out.println("**** LRU Stats **** ");
			System.out.println("Hit Count:[" + hitCount + "]");
			System.out.println("Mis Count:[" + misCount + "]");
			System.out.println("Evict  Count:[" + evictCount+ "]");
			System.out.println("******************* ");
		}
		change = false;
	}
}


public class LRUCache<K,V> {

	
	private LRUStats stats;
	private AbstractQueue<K> lruQ = null;
	private static final int DEFAULT_CACHE_SIZE = 512;
	private Map<K,V> lruMap = null;
	private int size = 0;
	
	public LRUCache(){ this(DEFAULT_CACHE_SIZE); }
	
	LRUCache(int s){
		
		size = s;
		lruQ = new ConcurrentLinkedQueue<K>();
		lruMap = new ConcurrentHashMap<K,V>();
		
		stats = new LRUStats();
	}
	
	public LRUStats getLRUStats() {
		stats.ShowStats();
		return stats;
	}
	
	public V get(K key) {
		V value = null;
		if ( lruQ.contains(key) ) {
			
			// Remove the key and add it to the back of the queue, 
			// hence maintaining the order of first element least recently used.
			
			lruQ.remove(key);
			lruQ.add(key);
			
			value = lruMap.get(key);
		} else {
			System.out.println("Cache Miss");
			stats.MisCount(true);
		}
		
		return value;
	}
	
	
	public K getLeastRecentlyUsed() {
		
		K front = null;
		if( lruQ.size() > 0 ) {
			front = lruQ.peek();
		}
		return front ;
	}
	
	public void set(K k, V v) {
		
		if ( lruQ.contains(k)) {			
			V value = lruMap.get(k);
			if( value == v){
				
				//no need to do anything with the map OR with the size of the Queue.
				//Only Re-Schuffle element in queue.
				
				lruQ.remove(k);
				lruQ.add(k);
				
				//Hit Count
				System.out.println("Key:["+ k + "],Value:[" + v  +"]");
				System.out.println("LRU :[" + getLeastRecentlyUsed() +  "]");
				stats.HitCount(true);
				
			} else {
				//This would be considered as a new insertion
				if (lruQ.size() >= size ) {
					lruQ.poll();
					
					stats.EvictCount(true);
				}
				
				stats.MisCount(true);
				//Miss Count
				lruQ.add(k);
				lruMap.put(k, v);
			}
			
		} else {
			if (lruQ.size() >= size ) {
				lruQ.poll();
				stats.EvictCount(true);
			}
			
			stats.MisCount(true);
			//Mis Count
			lruQ.add(k);
			lruMap.put(k, v);
		}
	}
}
