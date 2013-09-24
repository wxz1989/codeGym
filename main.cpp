//
//  main.cpp
//  GraphTheories
//
//  Created by Rakesh Gajjar on 9/4/13.
//  Copyright (c) 2013 Rakesh Gajjar. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

//sample input.
//First line of input
//9 10
//Second line of input.
//4 1 1 2 1 5 2 3 2 7 3 7 7 6 4 8 5 8 8 9


class GraphNode
{
public:
    GraphNode()
    {
        _vIndex = -1;
        _isProcessed = false;
    }
    GraphNode(int vIndex)
    {
        _vIndex = vIndex;
        _isProcessed = false;
    }
    int _vIndex;
    bool    _isProcessed;
};

class Graph {
    
    int __totalVertices;
    vector<GraphNode*>*     __pAdjList;
public:
    Graph()    {
        
        __totalVertices =0;
        __pAdjList = NULL;
    }
    
    Graph(int V)    {
        
        CreateGraph(V);
        
    }
    
    Graph*      CreateGraph(int noOfVertices);
    bool        Construct(int noOfVertices);
    void    PrintAdjList(void);
    void    ClearGraph(void);
    void    AddEdge(int source, int dest);
    void    BFS(int starNode, int noOfNodesTraversed);
    void    DFS(int starNode, int noOfNodesTraversed);
    
    void    TopoLogicalSort(void);
    void    ArticulationPoints(void);
};


bool
Graph::Construct(int noOfVertices) {
    
    bool r = false;
    if ( noOfVertices <= 0)
        return r;
    __totalVertices= noOfVertices;
    __pAdjList = new (std::nothrow) vector<GraphNode*>[__totalVertices];
    
    r = true;
    return r;
}
Graph*
Graph::CreateGraph(int noOfVertices){
    
    //Graph*  pGraph = NULL;
    //pGraph = new (std::nothrow) Graph(noOfVertices);
    
    __totalVertices= noOfVertices;
    __pAdjList = new (std::nothrow) vector<GraphNode*>[__totalVertices];
    //return pGraph;
    return NULL;
    
}
void
Graph::PrintAdjList(void) {
    
    GraphNode*  pTempNode = NULL;
    for ( int i = 0; i< __totalVertices ; i++) {
        
        cout<<"#"<<i+1<<" : ";
        for( int j = 1; j <__pAdjList[i].size() ;j++) {
            
            pTempNode = __pAdjList[i].at(j);
            if ( pTempNode != NULL)
                cout<<" "<<pTempNode->_vIndex;
            else {
                
                cout<<endl;
                continue;
            }
        }
        cout<<endl;
    }
}
void
Graph::ClearGraph(void) {
    
    GraphNode*  pTempNode = NULL;
    for ( int i = 0; i< __totalVertices ; i++) {
        
        if ( __pAdjList[i].size() >0 ) {
        
            pTempNode = __pAdjList[i].at(0);
            
            if ( pTempNode ) {
                
                delete pTempNode;
                pTempNode = NULL;
            }
            __pAdjList[i].clear();
        }
    }
    delete [] __pAdjList;
    return;
}
void 
Graph::AddEdge(int source, int dest) {

    int j=0;    
    GraphNode*      pSourceNode = NULL, *pDestinationNode = NULL;
    
    if( __pAdjList[source-1].size() == 0) {
        
        GraphNode*      pVertice = new (std::nothrow) GraphNode(source);
        __pAdjList[source-1].push_back(pVertice);
        pSourceNode = pVertice;
    }
    else {
        
        pSourceNode =  __pAdjList[source-1].at(0);
    }
    if( __pAdjList[dest-1].size() == 0) {
        
        GraphNode*      pVertice = new (std::nothrow) GraphNode(dest);
        __pAdjList[dest-1].push_back(pVertice);
        pDestinationNode = pVertice;
    }
    else {
        
        pDestinationNode =  __pAdjList[dest-1].at(0);
    }
    
    if ( pSourceNode == NULL )
        return;
    if ( pDestinationNode == NULL )
        return;
    
    __pAdjList[source-1].push_back(pDestinationNode);
    __pAdjList[dest-1].push_back(pSourceNode);
    
    return;
}

void
Graph::BFS(int startNode, int noOfNodesTraversed) {
    
    GraphNode*      pTempNode = NULL, *pPushNode = NULL;
    queue<GraphNode*> bfsQueue;

    
    if(startNode < 1 || startNode > __totalVertices) {
        
        std::cout<<"Invalid node to start"<<endl;
        return;
    }
    
    std::cout<<"Breadth First Search:";
    
    pTempNode = __pAdjList[startNode-1].at(0);
    pTempNode->_isProcessed = true;
    bfsQueue.push(pTempNode);
    noOfNodesTraversed++;
    
    pTempNode = NULL;
    
    while(bfsQueue.empty() == false) {
    
        pTempNode = bfsQueue.front();
        if( pTempNode != NULL) {
            
            std::cout<<" "<<pTempNode->_vIndex;
            bfsQueue.pop();
        }
        
        for ( int i = 0; i< __pAdjList[pTempNode->_vIndex-1].size(); i++) {
            
            pPushNode = __pAdjList[pTempNode->_vIndex-1].at(i);
            if ( pPushNode->_isProcessed == false) {
                
                pPushNode->_isProcessed = true;
                bfsQueue.push(pPushNode);
                noOfNodesTraversed++;
            }
        }
    }
    std::cout<<endl;
    return;
}

void
Graph::DFS(int startNode, int noOfNodesTraversed) {
    
    int i =0;
    GraphNode*      pTempNode = NULL, *pPushNode = NULL;
    stack<GraphNode*>   dfsStack;
    
    if(startNode < 1 || startNode > __totalVertices) {
        
        std::cout<<"Invalid node to start"<<endl;
        return;
    }
    
    std::cout<<"Depth First Search:";
    
    pTempNode = __pAdjList[startNode-1].at(0);
    pTempNode->_isProcessed = true;
    dfsStack.push(pTempNode);
    
    std::cout<<" "<<pTempNode->_vIndex;
    noOfNodesTraversed++;
    
    pTempNode = NULL;
    
    while(dfsStack.empty() == false) {
        
        pTempNode = dfsStack.top();
        if( pTempNode != NULL) {
            
            dfsStack.pop();
        }
        
        for ( i = 0; i< __pAdjList[pTempNode->_vIndex-1].size(); i++) {
            
            pPushNode = __pAdjList[pTempNode->_vIndex-1].at(i);
            if ( pPushNode->_isProcessed == false) {
                
                pPushNode->_isProcessed = true;
                dfsStack.push(pPushNode);
                
                std::cout<<" "<<pPushNode->_vIndex;
                
                pTempNode = pPushNode;
                i= 0;
                noOfNodesTraversed++;
            }
        }
    }
    
    std::cout<<endl;
    return;
}

int main(int argc, const char * argv[])
{
    int V =0, E=0;
    int startNode=-1;
    
    int nodes= 0;
    int E1[50] = {0}, E2[50] = {0};
    // insert code here...
    
    std::cin>>V;
    std::cin>>E;
    
    Graph   grp1;
    grp1.Construct(V);
    
    Graph   grp2;
    grp2.Construct(V);
    
    for ( int i = 0; i <E;i++) {
        
        std::cin>>E1[i];
        std::cin>>E2[i];
        
        grp1.AddEdge(E1[i], E2[i]);
        grp2.AddEdge(E1[i], E2[i]);
    }
    
    grp1.PrintAdjList();
    
    std::cout<<"Enter start node for BFS:";
    std::cin>>startNode;
    
    grp1.BFS(startNode, nodes);
    grp1.ClearGraph();
    
    nodes=0;
    
    startNode = 0;
    std::cout<<"Enter start node for DFS:";
    std::cin>>startNode;

    
    grp2.DFS(startNode, nodes);
    grp2.ClearGraph();

    return 0;
}

