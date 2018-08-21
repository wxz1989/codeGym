#include<iostream>
#include <conio.h>

using namespace std;

#define MAX_SIZE 1000
#define DICT_SIZE 26

string alphaDict[MAX_SIZE];

struct trieNode{
	int alphabets[DICT_SIZE][MAX_SIZE];
	char value;
};

struct SuffixNode;

typedef SuffixNode SNode;
typedef SuffixNode* SNodePtr;
typedef SuffixNode** SNodeDPtr;

struct SuffixNode{
	SNodePtr suff[DICT_SIZE];
	std::string value;
	char charVal;

	SuffixNode(){
		for (int i = 0; i < DICT_SIZE; i++){
			suff[i] = nullptr;
		}
		charVal = '\0';
		value = "";
	}
	void Release(){
		for (int i = 0; i < DICT_SIZE; i++){
			if (suff[i] != nullptr){
				delete suff[i];
				suff[i] = nullptr;
			}
		}
		charVal = '\0';
		value = "";
	}
};

typedef struct trieNode TTNode;
typedef struct trieNode* TTNodePtr;
typedef struct trieNode** TTNodeDPtr;

int K;
char suffix[MAX_SIZE] = { '\0' };

SNodePtr sRootNode;
TTNode rootNode;

int strLength(char suffix[]){
	int length = 0;
	while (suffix[length++] != '\0'){}
	return length-1;
}
void Release(SNodePtr pRoot){

	for (int i = 0; i < DICT_SIZE; i++){
		if (pRoot != nullptr){
			if (pRoot->suff[i] != nullptr){
				Release(pRoot->suff[i]);
				delete pRoot->suff[i];
				pRoot->suff[i] = nullptr;
			}
		}
	}
	
}
void Reset(){
	for (int i = 0; i < DICT_SIZE; i++){
		for (int j = 0; j < DICT_SIZE; j++){
			rootNode.alphabets[i][j] = -1;
		}
	}
	for (int i = 0; i < MAX_SIZE; i++) {
		alphaDict[i] = "";
	}
	rootNode.value= '\0';
}

void AddToTrie(string input, int dictionaryIndex){
	int chaining = 0;
	int i = 0;
	int j = 0;

	int indexToPut = input[0] - 'a';
	while (rootNode.alphabets[indexToPut][j] != -1){ j++;  }
	rootNode.alphabets[indexToPut][j] = dictionaryIndex;

	if (sRootNode == nullptr){
		sRootNode = new SNode();
		SNodePtr pNewNode = new SNode();
		pNewNode->value = input;
		pNewNode->charVal = input[0];
		sRootNode->suff[indexToPut] = pNewNode;
	}
	else {
		SNodePtr pTempRoot = nullptr;
		pTempRoot = sRootNode;

		while (pTempRoot->suff[indexToPut]){
			pTempRoot = pTempRoot->suff[indexToPut];
		}
		SNodePtr pNewNode = new SNode();
		pNewNode->value = input;
		pNewNode->charVal = input[0];
		pTempRoot->suff[indexToPut] = pNewNode;
	}
}
void AddSuffix(std::string input, int k){
	if (input.size() == 0){ return; }
	unsigned int i = 0;
	for (i = 0; i < input.size(); i++){
		alphaDict[i] = input.substr(i,input.length());
		AddToTrie(alphaDict[i],i);
	}
}

string findKthSuffix(int suffixIndex){
	int kthElement = 0;
	int j = 0;
	if (suffixIndex > 0 ){ 
		for (int i = 0; i < DICT_SIZE;i++){
			if (rootNode.alphabets[i][0] != -1){
				while (rootNode.alphabets[i][j++] != -1 ){
					
				}
				kthElement++;
				if (kthElement == suffixIndex){
					int index = rootNode.alphabets[i][0];
					return alphaDict[index];
				}
			}
			else {

			}
		}
	}
	return string("");
}
int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	The freopen function below opens input.txt in read only mode and
	sets your standard input to work with the opened file.
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/


	freopen("KthSuffixSampleInput.txt", "r", stdin);
	cin >> T;

	/*
	Read each test case from standard input.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		Reset();
		cin >> K;
		string suffixStr;
		cin >> suffix;
		suffixStr.append(suffix);
		AddSuffix(suffixStr, K);
		string answer = findKthSuffix(K);

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		Please, implement your algorithm from this section.
		*/
		/////////////////////////////////////////////////////////////////////////////////////////////
		cout << "# " << test_case << " " << answer.c_str() << endl;
	}
	_getche();
	return 0;//Your program should return 0 on normal termination.
}
