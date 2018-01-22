#include "Graph_Impl.h"
#include <iostream>

using namespace std;


void Graph::TopologicalSort(){

	std::list<int>::iterator ite;
	std::set<int>::iterator it;

	for (it=uV.begin(); it!=uV.end();){  
		
		if ( pVisited[*it] == 1 ) { ++it; continue; }
		if ( pIndegree[*it] == 0 ){

			pVisited[*it] = 1;
			for (ite = pAdjList[*it].begin(); ite != pAdjList[*it].end(); ++ite){
				pIndegree[*ite] -= 1;
			}
			topoSort.push_back(*it);
			it = uV.begin();			
			continue;
		}
		++it;
	}
	for (ite = topoSort.begin(); ite != topoSort.end(); ++ite){ cout << *ite << " "; }
	cout << endl;
	return;
}
