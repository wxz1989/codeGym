#ifndef _GRAPH_IMPL_
#define _GRAPH_IMPL_

#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <memory.h>

class Graph{

	int vertices;
	int edges;
	std::set<int> uV;;
	std::list<int>* pAdjList;
	int* pVisited; 
	int* pIndegree; 
	std::list<int> topoSort;
	
public:
	Graph(){
		vertices = 0;
		edges = 0;
		pAdjList = nullptr;
		pVisited = nullptr;
		pIndegree = nullptr;
	}

	Graph(int v, int e) : vertices(v), edges(e) {

		Alloc();
	}

	~Graph(){
		Release();
	}

	//Use this method if Graph is not initialized using it's parameterazied constructor
	bool Init(int v, int e){

		Release();

		vertices = v;
		edges = e;

		Alloc();
	}

	void AddEdge(int s, int d){
		//std::cout << s << d << vertices << edges ;
		if( s <= vertices && d <= vertices){
		//	std::cout << "Inserting" << std::endl;
			uV.insert(s);
			uV.insert(d);

			pAdjList[s].push_back(d);

			pIndegree[d] += 1;
		}
	}

	void RemoveEdge(int s, int d){
		//std::cout << s << d << vertices << edges ;
		if( s <= vertices && d <= vertices){
		//	std::cout << "Inserting" << std::endl;
			uV.erase(s);
			uV.erase(d);

			std::list<int>::iterator ite;
			std::cout << "AdjList:[" << s <<"]:" << std::endl;
			for (ite = pAdjList[s].begin(); ite != pAdjList[s].end(); ++ite){
				if ( *ite == d ){
					pAdjList[s].erase(ite);
					pIndegree[d] -= 1;
				}
			}
		}
	}

	void Release(){
		vertices = edges  = 0;

		if ( pAdjList ){ delete [] pAdjList;  pAdjList =  nullptr ;} 
		if ( pVisited ) { delete [] pVisited;  pVisited = nullptr; } 
		if ( pIndegree ) { delete [] pIndegree; pIndegree = nullptr; }

		uV.clear();
		topoSort.clear();
	}

	void Alloc(){

		pAdjList = new std::list<int> [vertices+1];
		pVisited = new int[vertices+1];
		memset(pVisited, 0, sizeof(int) * (vertices+1));
		pIndegree = new int [vertices+1]; 
		memset(pIndegree, 0, sizeof(int) * (vertices+1));
	}

	//MAIN FUNC: 
	void TopologicalSort();

	

	//NO BRAINER : Don't look at this function, it's only ment for debugging and to check Graph State
	void LogRecords(){
		std::cout << "V:["<< vertices <<"] E:[" << edges <<"]" << std::endl;

		std::list<int>::iterator ite;
		std::set<int>::iterator it;
		for (it=uV.begin(); it!=uV.end(); ++it){  
			std::cout << "*********************************" <<std::endl;
			std::cout << "AdjList:[" << *it <<"]: [";
			for (ite = pAdjList[*it].begin(); ite != pAdjList[*it].end(); ++ite){
				std::cout << *ite << " " ;
			}
			std::cout << "]" << std::endl;

			std::cout << "InDegree:[" << *it <<"]:" << pIndegree[*it]<<std::endl;
			std::cout << "Visited:[" << *it <<"]:" << pVisited[*it]<<std::endl;
			std::cout << "*********************************" << std::endl;
		}
	}


};






/* Array Implementation, Works are well are any other implementation but for dynamic allocation,  scalling and for PRACTICE used containers
int v, e;	
int visited[MAX];
int adjList[MAX][MAX];
int indegree[MAX];

void LogRecords(){
	cout << "V:["<< v <<"] E:[" << e<<"]" << endl;
	for ( int i = 0; i <=v ; i++){
		cout << "InDegree:[" << i<< "]:" << indegree[i] <<  endl;
		if ( visited[i] != 0 )
			cout << "Visited:[" <<i <<"]:" << visited[i] << endl;
		for ( int j = 0; j <=v ; j++){
			if ( adjList[i][j] != 0 )
				cout << "AdjList:[" <<i <<"][" <<j <<"]:" << adjList[i][j] << endl;
			
		}
	}
}

void TopologicalSort(){
	for ( int i = 0; i < MAX ; i++){
		for ( int j = 0; j < MAX ; j++){
			if ( adjList[i][j] != 0 ){
				indegree[j] += 1;
			}
		}
	}
	LogRecords();
}

void Relaese(){
	for ( int i = 0; i < MAX ; i++){
		indegree[i] = 0;
		visited[i] = 0;
		for ( int j = 0; j < MAX ; j++){
			adjList[i][j] = 0;
		}
	}
	v = e =0;
}
*/
#endif 			/*_GRAPH_IMPL_*/
