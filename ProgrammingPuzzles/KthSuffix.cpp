#include<iostream>
#include <conio.h>

using namespace std;

#define MAX_SIZE 1000
#define DICT_SIZE 26

string alphaDict[MAX_SIZE];


struct Indices{
	int orgIndex;
	int alphaDiff;
};

struct trieNode{

	int alphabets[DICT_SIZE][MAX_SIZE];
	Indices IndStore[DICT_SIZE][MAX_SIZE];
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

string sortString(std::string str){

	int alphabets[DICT_SIZE] = { 0 };
	//Initialize
	for (int i = 0; i < DICT_SIZE; i++){ alphabets[i] = 0; } // n = 26
	//Hash all characters keeping count of all
	for (unsigned int i = 0; i < str.length(); i++){ alphabets[str[i] - 'a']++; }  // n = m (String length)

	//Read hash and prepare sorted string
	string ret;
	for (int i = 0; i < DICT_SIZE; i++){			// n = 26
		if (alphabets[i] != 0) { 
			for (int j = 0; j < alphabets[i]; j++){   //n = M(no of times that character occured in that string) 26*m(length of the string)
				ret += ((char)'a' + i); 
			} 
		} 
	}
	return ret;
}


/*Time complexity of this would be
= n + m + 26 * m
=>removing constant it would be
= n + m + m
= n + 2m;
=	2m (twice the size of string, if string length is > 26)
*/

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
				cout << "Deleting:[" << pRoot->value.c_str() << "]" << endl; 
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
	
	/*rootNode.IndStore[indexToPut][j].orgIndex = dictionaryIndex;
	if (input.length() >= j )
		rootNode.IndStore[indexToPut][j].alphaDiff = input[j] - 'a';
	else 
		rootNode.IndStore[indexToPut][j].alphaDiff = input[0] - 'a';
	
	*/
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

string findKthSuffixRec(SNodePtr rootNode, int ind, int& found){

	string ret("");
	if (rootNode == nullptr || found > K){ 
		return ""; 
	}

	
	for (int i = ind; i< DICT_SIZE ;i++){
		if (rootNode->suff[i] != nullptr){
			found++;
			ret = findKthSuffixRec(rootNode->suff[i], i, found);
			if (found == K){
				return rootNode[i].value;
			}
		}
	}
	return ret;
}

string findKthSuffix(int suffixIndex){
	int kthElement = 0;
	int j = 0;
	if (suffixIndex > 0 ){ 
		for (int i = 0; i < DICT_SIZE;i++){
			if (rootNode.alphabets[i][0] != -1){
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

	string test("wvotseejlcuuubtiaynoriiqscofsarulkpkncnotjioonwwtbmtrfrbizzaelsofdstuzfepimejxipwvmwnsdbiqwdmohcqnswxcpdecjvildcrofjcfhcjiwcynvkgalswnvivhakxnrfeasymuvlpyzxdwbmazjoauepxetkpvwzsfvwkgrojsfcedgvgdgqebwanhozynbwcvovasdciowvckoroeesuxsgczrbztrktitnvpblhvemmjesnfnltvmzodsiknkeguqmkzjlzcbbdluzvhhfzbbhabnfwlrqnfspacvpharaizgkteuelezbejipwoavulaxajrjkvpttkmmuyrgxblyjcgmfldvmnuoerftaxnnrkgtavuasyjijotyemwm");
	cout << test.length() << endl;
	sortString("banana");
	return 0;

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
		int foundCount = 0;
		string answer = findKthSuffixRec(sRootNode, 0, foundCount);//findKthSuffix(K);

		Release(sRootNode);

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
