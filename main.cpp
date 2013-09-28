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
#include <map>

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
    map<int, map<int, GraphNode*>*>*  __pAdjMap;
public:
    Graph()    {
        
        __totalVertices =0;
        __pAdjMap = NULL;
    }
    
    Graph(int V)    {
        
        CreateGraph(V);
        
    }
    
    Graph*  CreateGraph(int noOfVertices);
    bool    Construct(int noOfVertices);
    void    PrintAdjList(void);
    void    ClearGraph(void);
    void    AddEdge(int source, int dest);
    
    GraphNode* FindNode(int Source, int Destination);
    
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
    __pAdjMap = new (std::nothrow) map<int, map<int, GraphNode*>*>;
    
    r = true;
    return r;
}
Graph*
Graph::CreateGraph(int noOfVertices){
    
    //Graph*  pGraph = NULL;
    //pGraph = new (std::nothrow) Graph(noOfVertices);
    
    __totalVertices= noOfVertices;
    __pAdjMap = new (std::nothrow) map<int, map<int, GraphNode*>*>;
    //return pGraph;
    return NULL;
    
}
void
Graph::PrintAdjList(void) {
    
    GraphNode*  pNode = NULL;
    std::map<int, GraphNode*>::iterator mapItrSource;
    std::map<int, map<int, GraphNode*>*>::iterator mapItrDesti;
    
    std::cout<<"ADJACENCY LIST USING HASHMAP"<<endl;
    
    if ( __pAdjMap == NULL)
        return;
    
    if (__pAdjMap->size() ==0 )
        return;
    
    for ( mapItrDesti = __pAdjMap->begin() ; mapItrDesti != __pAdjMap->end(); ++mapItrDesti) {
        
        map<int, GraphNode*>*  pAdjList = NULL;
        
        pAdjList = mapItrDesti->second;
        
        if (pAdjList != NULL && mapItrDesti != __pAdjMap->end()) {
            
            std::cout<<"#"<<mapItrDesti->first;
            for ( mapItrSource = pAdjList->begin(); mapItrSource != pAdjList->end(); ++mapItrSource){
                
                pNode = mapItrSource->second;
                
                if ( pNode != NULL && mapItrSource != pAdjList->end())
                    std::cout<<" "<<pNode->_vIndex;
                
                pNode = NULL;
            }
            std::cout<<endl;
        }
    }
}
void
Graph::ClearGraph(void) {
    
    GraphNode* pNode = NULL;
    while (!__pAdjMap->empty()) {
        
        map<int, GraphNode*>*  pAdjList = NULL;
        pAdjList = __pAdjMap->begin()->second;
        
        if (pAdjList != NULL ) {
            
            while (!pAdjList->empty()) {
                
                pNode = pAdjList->begin()->second;
                
                pAdjList->erase(pAdjList->begin());
            }
            pAdjList->clear();
            delete pAdjList;
            pAdjList = NULL;
        }
        __pAdjMap->erase(__pAdjMap->begin());
    }
    
    __pAdjMap->clear();
    delete __pAdjMap;
    __pAdjMap = NULL;
    
}
void 
Graph::AddEdge(int source, int dest) {

    GraphNode*      pSourceNode = NULL, *pDestinationNode = NULL;
    std::map<int, map<int, GraphNode*>*>::iterator mapItrSource;
    std::map<int, map<int, GraphNode*>*>::iterator mapItrDesti;

    if ( __pAdjMap->size() == 0 ) {
        
        map<int, GraphNode*>*   pLocalMap = NULL;
        
        pSourceNode = new (std::nothrow) GraphNode(source);
        pDestinationNode = new (std::nothrow) GraphNode(dest);
        
        pLocalMap = new (std::nothrow) map<int, GraphNode*>;
        pLocalMap->insert(std::pair<int, GraphNode*>(dest, pDestinationNode));
        
        __pAdjMap->insert(std::pair<int, map<int, GraphNode*>*>(source, pLocalMap));
        
        pLocalMap = NULL;
        pLocalMap = new (std::nothrow) map<int, GraphNode*>;
        pLocalMap->insert(std::pair<int, GraphNode*>(source, pSourceNode));
        
        __pAdjMap->insert(std::pair<int, map<int, GraphNode*>*> (dest, pLocalMap));
        
    }
    else {
        
        GraphNode*     pNode = NULL;
        
        pNode = FindNode(source, dest);
        
        //Adding destination to source...
        map<int, GraphNode*>* pLocalList = NULL;
        mapItrSource =  __pAdjMap->find(source);
        
        pLocalList = mapItrSource->second;
        if( pLocalList != NULL && mapItrSource != __pAdjMap->end()) {
            
            if ( pNode == NULL)
                pDestinationNode = new (std::nothrow) GraphNode(dest);
            else
                pDestinationNode = pNode;
            
            pLocalList->insert(std::pair<int, GraphNode*>(dest, pDestinationNode));
        }
        else {
            
            map<int, GraphNode*>*     pLocaList = NULL;
            pLocaList = new (std::nothrow) map<int, GraphNode*>;
            
            if ( pNode == NULL)
                pDestinationNode = new (std::nothrow) GraphNode(dest);
            else
                pDestinationNode = pNode;
            
            pLocaList->insert(std::pair<int, GraphNode*>(dest, pDestinationNode));
            
            __pAdjMap->insert(std::pair<int, map<int, GraphNode*>*> (source, pLocaList));

        }
        //Addition of destination to source is done...
        
        
        //Adding source to the destination..
        
        pNode = NULL;
        pNode = FindNode(dest, source);
        
        pLocalList = NULL;
        mapItrDesti =  __pAdjMap->find(dest);
        
        pLocalList = mapItrDesti->second;
        if( pLocalList != NULL && mapItrDesti != __pAdjMap->end()) {
            
            if ( pNode == NULL)
                pSourceNode = new (std::nothrow) GraphNode(source);
            else
                pSourceNode = pNode;
            
            pLocalList->insert(std::pair<int, GraphNode*>(source, pSourceNode));
        }
        else {
            
            map<int, GraphNode*>*     pLocaList = NULL;
            pLocaList = new (std::nothrow) map<int, GraphNode*>;
            
            if ( pNode == NULL)
                pSourceNode = new (std::nothrow) GraphNode(source);
            else
                pSourceNode = pNode;
            
            pLocaList->insert(std::pair<int, GraphNode*>(source, pSourceNode));
            
            __pAdjMap->insert(std::pair<int, map<int, GraphNode*>*> (dest, pLocaList));
            
        }
        //Addition of source to destinaton is done...
    }

    return;
}

void
Graph::BFS(int startNode, int noOfNodesTraversed) {
    
    GraphNode*      pTempNode = NULL, *pPushNode = NULL;
    std::map<int, map<int, GraphNode*>*>::iterator mapItr;
    std::map<int, GraphNode*>::iterator mapItrLocal;
    map<int, GraphNode*>*       pLocalMap = NULL;
    
    queue<GraphNode*> bfsQueue;

    
    if(startNode < 0 || startNode > __totalVertices) {
        
        std::cout<<"Invalid node to start"<<endl;
        return;
    }
    
    std::cout<<"Breadth First Search:";
    
    pTempNode = FindNode(0, startNode);
    if ( pTempNode != NULL)
        pTempNode->_isProcessed = true;
    else
        return;
    
    bfsQueue.push(pTempNode);
    noOfNodesTraversed++;
    
    pTempNode = NULL;

    while(bfsQueue.empty() == false) {
    
        pTempNode = bfsQueue.front();
        if( pTempNode != NULL) {
            
            std::cout<<" "<<pTempNode->_vIndex;
            bfsQueue.pop();
        }
        
        mapItr = __pAdjMap->find(pTempNode->_vIndex);
        pLocalMap = mapItr->second;
        
        if ( pLocalMap != NULL && mapItr != __pAdjMap->end()) {
            
            for ( mapItrLocal = pLocalMap->begin(); mapItrLocal != pLocalMap->end(); ++ mapItrLocal) {
                
                pPushNode = mapItrLocal->second;

                if ( pPushNode != NULL && mapItrLocal != pLocalMap->end()) {
                    
                    if ( pPushNode->_isProcessed == false) {
                        
                        pPushNode->_isProcessed = true;
                        bfsQueue.push(pPushNode);
                        noOfNodesTraversed++;
                    }
                }
            }
        }
    }
    std::cout<<endl;
    return;
}

void
Graph::DFS(int startNode, int noOfNodesTraversed) {
    
    GraphNode*      pTempNode = NULL, *pPushNode = NULL;
    
    std::map<int, map<int, GraphNode*>*>::iterator mapItr;
    std::map<int, GraphNode*>::iterator mapItrLocal;
    map<int, GraphNode*>*       pLocalMap = NULL;
    
    stack<GraphNode*>   dfsStack;
    
    if(startNode < 0 || startNode > __totalVertices) {
        
        std::cout<<"Invalid node to start"<<endl;
        return;
    }
    
    std::cout<<"Depth First Search:";
    
    pTempNode = FindNode(0, startNode);
    if ( pTempNode != NULL)
        pTempNode->_isProcessed = true;
    else
        return;
    
    dfsStack.push(pTempNode);
    
    std::cout<<" "<<pTempNode->_vIndex;
    noOfNodesTraversed++;
    
    pTempNode = NULL;
    
    while(dfsStack.empty() == false) {
        
        pTempNode = dfsStack.top();
        
    JUMP:
        mapItr = __pAdjMap->find(pTempNode->_vIndex);
        pLocalMap = mapItr->second;
        
        if ( pLocalMap != NULL && mapItr != __pAdjMap->end()) {
            
            for ( mapItrLocal = pLocalMap->begin(); mapItrLocal != pLocalMap->end(); ++ mapItrLocal) {
                
                pPushNode = mapItrLocal->second;
                
                if ( pPushNode != NULL && mapItrLocal != pLocalMap->end()) {
                    
                    if ( pPushNode->_isProcessed == false) {
                        
                        pPushNode->_isProcessed = true;
                        dfsStack.push(pPushNode);
                        
                        std::cout<<" "<<pPushNode->_vIndex;
                        
                        pTempNode = pPushNode;
                        
                        goto JUMP;
                        noOfNodesTraversed++;
                    }
                }
            }
        }
        if( pTempNode != NULL)   //The current node has been processed and all nodes connected to it have been traversed.
            dfsStack.pop();
    }
    
    std::cout<<endl;
    return;
}


GraphNode*
Graph::FindNode(int Source, int Destination) {

    GraphNode*  pNode = NULL;
    std::map<int, GraphNode*>::iterator mapItrSource;
    std::map<int, map<int, GraphNode*>*>::iterator mapItrDesti;
    
    if ( __pAdjMap == NULL)
        return NULL;
    
    if (__pAdjMap->size() ==0 )
        return NULL;
    
    for ( mapItrDesti = __pAdjMap->begin() ; mapItrDesti != __pAdjMap->end(); ++mapItrDesti) {
        
        map<int, GraphNode*>*  pAdjList = NULL;
        
        pAdjList = mapItrDesti->second;
        
        if (pAdjList != NULL && mapItrDesti != __pAdjMap->end()) {
            
            /*
            for ( mapItrSource = pAdjList->begin(); mapItrSource != pAdjList->end(); ++mapItrSource){
             
                pNode = mapItrSource->second;
                
                if ( pNode != NULL && mapItrSource != pAdjList->end()) {
                    
                    if ( pNode->_vIndex == Destination)
                        return pNode;
                }
            }*/
            mapItrSource = pAdjList->find(Destination);
            pNode = mapItrSource->second;
            
            if ( pNode != NULL && mapItrSource != pAdjList->end())
                return pNode;
            else
                continue;
        }
    }
    return NULL;
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

