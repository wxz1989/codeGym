#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
	hashSize = 0;
	pHashTable = new HashNode*[HASH_TABLE_SIZE];
	for ( int i = 0; i < HASH_TABLE_SIZE ;i++){
		pHashTable[i] = NULL;
	}
}
HashTable::~HashTable(){
	hashSize = 0;
}

bool HashTable::Put(std::string key, int value){
	
	PutImpl(key, value);

	return true;
}
int HashTable::Get(std::string key){

	int hashValue = GetImpl(key);
	return hashValue;
}

bool HashTable::Find(std::string key){
	int hashValue = GetImpl(key);

	return ((hashValue == -1) ? false : true);
}	

void HashTable::Print(){
	for ( int i = 0; i < HASH_TABLE_SIZE;i++){
		if ( pHashTable[i] != NULL ){
			cout << "Key:[" << pHashTable[i]->GetKey() <<"], Value:[" << pHashTable[i]->GetValue() << "]" << endl;
		}
	}
}

void HashTable::Clear(){
	for ( int i = 0; i < HASH_TABLE_SIZE ; i++){
		if ( pHashTable[i] != NULL ){
			delete pHashTable[i];
		}
	}
	delete [] pHashTable;
	pHashTable = NULL;
}


HNodePtr HashTable::CreateNewNode(){

	HNodePtr temp = NULL;
	temp = new HashNode();
	if ( temp == NULL){
		return NULL;
	}
	return temp;
}
size_t HashTable::GenerateHashKey(std::string value){

	//cout << "Enter>>" << endl;
	if ( value.empty() ){
		cout << "Error: Invald value, failed to insert value to HashTable!" << endl;
		return -1;
	} 

	unsigned long hashValue = 0;
	unsigned long hashKey = 0;

	for ( int i = 0; i < value.length(); i++){
	//	printf("%c\n", value[i]);
		hashValue += value[i];			//keep adding the ASCII value
	}

	if ( hashValue > 0 ){ hashKey = hashValue % HASH_TABLE_SIZE; }

	//cout << "<<Exit:[" << hashKey <<"]" <<endl;
	return hashKey;
}

void HashTable::PutImpl(std::string key, int value){

	if ( key.empty()){ cout << "Error" << endl; return; }
	unsigned long hashKey = GenerateHashKey(key);


	while ( pHashTable[hashKey] != NULL && hashKey < HASH_TABLE_SIZE){ hashKey += 1; }

	HNodePtr temp = CreateNewNode();
	temp->SetKey(hashKey);
	temp->SetValue(value);
	pHashTable[hashKey] = temp;

}	

int HashTable::GetImpl(std::string key){

	int hashValue = -1;
	unsigned long hashKey = GenerateHashKey(key);
	//while ( pHashTable[hashKey] == NULL && hashKey < HASH_TABLE_SIZE){ hashKey += 1; }

	if ( pHashTable[hashKey] != NULL ){
		hashValue = pHashTable[hashKey]->GetValue();
	} 

	return hashValue;
}


