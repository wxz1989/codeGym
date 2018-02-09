#include "DisJointSets.h"
#include <iostream>

using namespace std;

DisjointSets::DisjointSets(){
	m_SetCounts = 0;
	m_SetElements = 0;
	m_SetEdges = 0;				//use this for the referneces of a graph.
	m_pVectorSet = NULL;
	m_pMemberArray = NULL;
}
DisjointSets::~DisjointSets(){

	if (m_pMemberArray){ delete[] m_pMemberArray; }
	if (m_pVectorSet){ delete[] m_pVectorSet; }
}

bool DisjointSets::Initialize(int sizeOfElement){

	if (sizeOfElement <= 0){ std::cout << "Initailization Failed! Acceptable values can be >=1 and <=1000." << std::endl; return false; }

	m_SetCounts = 0;
	m_SetElements = sizeOfElement;
	//m_SetEdges = sizeOfElement+1;				//use this for the referneces of a graph.
	m_pVectorSet = NULL;
	m_pMemberArray = new int[sizeOfElement+1];

	for (int i = 0; i < sizeOfElement+1; i++) { m_pMemberArray[i] = i; }

	return true;
}
bool DisjointSets::FindSet(int one, int two){

	if (m_pMemberArray[one] == m_pMemberArray[two]) { return true; }
	else { return false; }
}
bool DisjointSets::MergeSet(int one, int two){
	int TEMP = m_pMemberArray[one];
	for (int i = 1; i <=m_SetElements; i++) { if (m_pMemberArray[i] == TEMP) {  m_pMemberArray[i] = m_pMemberArray[two];  } }

	//CalculateSetCount();
	return true;
}

const std::vector<int>* DisjointSets::GetSetVector(){
	return m_pVectorSet;
}
int DisjointSets::GetDisjointSetsCount(){

	CalculateSetCount();
	return m_SetCounts;
}

void DisjointSets::CalculateSetCount(){
	if (m_pMemberArray == NULL){ std::cout << "Disjoint Set Array is empty!" << std::endl;  return; }

	/*****OLD CODE USING ARRAY BASED IMPLEMENTATION
	int count = 0;
	for (int i = 0; i < m_SetElements+1; i++){
		if (m_pMemberArray[i] == 0){ continue; }
		if (m_pMemberArray[i] != m_pMemberArray[i + 1]){
			count++;
		}
	}
	m_SetCounts = count;
	*/
	totalSets.clear();
	
	for (int i = 0; i < m_SetElements + 1; i++){
		if (m_pMemberArray[i] == 0){ continue; }
		totalSets.insert(m_pMemberArray[i]);
	}
	m_SetCounts = totalSets.size();
	
}
void DisjointSets::PrepareSetVector(){

	int setCount = 0;
	int setIndex = 0;
	if (m_SetCounts == 0){ return;  }
	int temp = m_pMemberArray[0];

	if (m_pVectorSet != NULL){  delete[] m_pVectorSet; m_pVectorSet = NULL; }

	m_pVectorSet = new vector<int>[m_SetCounts];
	for (std::set<int>::iterator it = totalSets.begin(); it != totalSets.end(); ++it){
		int setIndex = *it;
		for (int i = 0; i <= m_SetElements; i++){
			if (m_pMemberArray[i] == 0){ continue; }

			if (m_pMemberArray[i] == setIndex){
				m_pVectorSet[setCount].push_back(i);
			}
		}
		setCount++;
	}
	/* Old code: Array based Disjoint Set Code.
	for (int i = 0; i <= m_SetElements; i++){
		if (temp == 0){ temp = m_pMemberArray[i + 1]; continue; }

		if (temp != m_pMemberArray[i]){
			setIndex++;
			temp = m_pMemberArray[i + 1];
			m_pVectorSet[setIndex].push_back(i);
		}
		else {
			m_pVectorSet[setIndex].push_back(i);
		}
	}
	*/
}

void DisjointSets::PrintSets(void){

	if (m_SetCounts <= 0){ std::cout << "Empty set!" << std::endl; return; }

	PrepareSetVector();
	for (int i = 0; i<m_SetCounts; i++){
		std::cout << "Set " << i + 1 << "[";
		for (unsigned int j = 0; j < m_pVectorSet[i].size(); j++){
			std::cout << m_pVectorSet[i].at(j);

			if (j < (m_pVectorSet[i].size())-1){  std::cout<< ", "; }
		}
		std::cout << "]" << std::endl;
	}

	std::cout << "Set Array:" << "[";
	for (int i = 0; i <= m_SetElements; i++){
		std::cout << m_pMemberArray[i]<<" " ;
	}
	std::cout << "]" << std::endl;
	return;
}

void DisjointSets::RemoveAll(){
	delete [] m_pMemberArray;
	m_pMemberArray = NULL;

	delete[] m_pVectorSet;
	m_pVectorSet = NULL;

	m_SetCounts = 0;
	m_SetElements = 0;
	m_SetEdges = 0;				//use this for the referneces of a graph.
}

void DisjointSets::SetEdges(int edgeCount){
	m_SetEdges = edgeCount;
}
