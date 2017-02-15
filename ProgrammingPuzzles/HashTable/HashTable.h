#include <iostream>
#include <string.h>
#include <memory>
#include <vector>

class HashNode{

	unsigned long hashKey;
	int hashValue;
public:
	void SetKey(unsigned long key){
		hashKey = key;
	}
	void SetValue(int value){
		hashValue = value;
	}

	unsigned long GetKey(){
		return hashKey;
	}
	int GetValue(){
		return hashValue;
	}
};

typedef HashNode* HNodePtr;
typedef HashNode** HNodeDPtr;

typedef std::shared_ptr<HashNode> HashNodeSPtr;

class HashTable{
	static const unsigned long long HASH_TABLE_SIZE=99; //999999999;
private:
	int hashSize;
	HNodeDPtr pHashTable;
	//std::vector<HashNodeSPtr> hashNodeSPtrArray;
	//HashNodeSPtr sPtrArray[HASH_TABLE_SIZE];
public:
	HashTable();
	~HashTable();

	bool Put(std::string, int value);
	int Get(std::string);
	bool Find(std::string);

	void Print();
	void Clear();
private:
	HNodePtr CreateNewNode();
	size_t GenerateHashKey(std::string);

	void PutImpl(std::string key, int value);
	int GetImpl(std::string key);
};

//Using Smart pointer for understanding and for ease of use

