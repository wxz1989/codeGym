/*
Author : Rakesh Gajjar
Date : 19/02/2016
Description : Array based implementation of the DisjointSet.
			Variation is linked list based representation of Disjoint Sets.
*/

#ifndef __DISJOINT_SETS_H__
#define __DISJOINT_SETS_H__

#include <vector>
#include <set>

class DisjointSets{
public:
	DisjointSets();
	virtual ~DisjointSets();
public :
	/* APIs for basic operation of Disjoint Sets*/
	bool Initialize(int sizeOfElement);
	bool FindSet(int one, int two);
	bool MergeSet(int one, int two);

	/* Getter APIs */
	const std::vector<int>* GetSetVector();
	int GetDisjointSetsCount();
	void PrintSets(void);
	void RemoveAll();

	void SetEdges(int edgeCount);
private:
	void CalculateSetCount();
	void PrepareSetVector();
private:
	int m_SetCounts;
	int m_SetElements;
	int m_SetEdges;				//use this for the referneces of a graph.
	std::vector<int>* m_pVectorSet;
	int* m_pMemberArray;
	std::set<int> totalSets;
};


#endif			//__DISJOINT_SETS_H__
