#include <stdio.h>
#include <string.h>
#include <iostream>
//#include <conio.h>

#define INVALID_HASH -1
#define MULTIPLIER		67
#define FIELD_LENGTH	19
#define MOD_PRIME		10009
#define MAX_SIZE		50000

struct ListNode;
typedef struct ListNode Node;
typedef struct ListNode* NodePtr;
typedef struct ListNode** NodeDPtr;

struct DBRecord{
	char name[FIELD_LENGTH];
	char number[FIELD_LENGTH];
	char bday[FIELD_LENGTH];
	char email[FIELD_LENGTH];
	char memo[FIELD_LENGTH];

	DBRecord(){
		for (int i = 0; i < FIELD_LENGTH; i++){
			name[i] = '\0';
			number[i] = '\0';
			bday[i] = '\0';
			email[i] = '\0';
			memo[i] = '\0';
		}
	}
};

struct ListNode{
	//std::string value;
	unsigned int index;
	NodePtr pNext;

	ListNode(){
		index = 0;
		pNext = nullptr;
	}
};

NodePtr NameHash[MOD_PRIME];
NodePtr NumberHash[MOD_PRIME];
NodePtr BDayHash[MOD_PRIME];
NodePtr EmailHash[MOD_PRIME];
NodePtr MemoHash[MOD_PRIME];

DBRecord database[MAX_SIZE];



typedef enum
{
	CMD_INIT,
	CMD_ADD,
	CMD_DELETE,
	CMD_CHANGE,
	CMD_SEARCH
} COMMAND;

typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;



unsigned int dbRecordIndex = 0;
void PrintHash(NodePtr hashArray[], int size);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void InitDB();
 void Add(char* name, char* number, char* birthday, char* email, char* memo);
 int Delete(FIELD field, char* str);
 int Change(FIELD field, char* str, FIELD changefield, char* changestr);
 RESULT Search(FIELD field, char* str, FIELD returnfield);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


void ClearAllHashArray();
static int dummy[100];
static int Score, ScoreIdx;
static char name[20], number[20], birthday[20], email[20], memo[20];

static char lastname[10][5] = { "kim", "lee", "park", "choi", "jung", "kang", "cho", "oh", "jang", "lim" };
static int lastname_length[10] = { 3, 3, 4, 4, 4, 4, 3, 2, 4, 3 };

static int mSeed;
static int mrand(int num)
{
	mSeed = mSeed * 1103515245 + 37209;
	if (mSeed < 0) mSeed *= -1;
	return ((mSeed >> 8) % num);
}

static void make_field(int seed)
{
	int name_length, email_length, memo_length;
	int idx, num;

	mSeed = (unsigned int)seed;

	name_length = 6 + mrand(10);
	email_length = 10 + mrand(10);
	memo_length = 5 + mrand(10);

	num = mrand(10);
	for (idx = 0; idx < lastname_length[num]; idx++) name[idx] = lastname[num][idx];
	for (; idx < name_length; idx++) name[idx] = 'a' + mrand(26);
	name[idx] = 0;

	for (idx = 0; idx < memo_length; idx++) memo[idx] = 'a' + mrand(26);
	memo[idx] = 0;

	for (idx = 0; idx < email_length - 6; idx++) email[idx] = 'a' + mrand(26);
	email[idx++] = '@';
	email[idx++] = 'a' + mrand(26);
	email[idx++] = '.';
	email[idx++] = 'c';
	email[idx++] = 'o';
	email[idx++] = 'm';
	email[idx] = 0;

	idx = 0;
	number[idx++] = '0';
	number[idx++] = '1';
	number[idx++] = '0';
	for (; idx < 11; idx++) number[idx] = '0' + mrand(10);
	number[idx] = 0;

	idx = 0;
	birthday[idx++] = '1';
	birthday[idx++] = '9';
	num = mrand(100);
	birthday[idx++] = '0' + num / 10;
	birthday[idx++] = '0' + num % 10;
	num = 1 + mrand(12);
	birthday[idx++] = '0' + num / 10;
	birthday[idx++] = '0' + num % 10;
	num = 1 + mrand(30);
	birthday[idx++] = '0' + num / 10;
	birthday[idx++] = '0' + num % 10;
	birthday[idx] = 0;
}

static void cmd_init()
{
	scanf("%d", &ScoreIdx);

	InitDB();
}

static void cmd_add()
{
	int seed;
	scanf("%d", &seed);

	make_field(seed);

	Add(name, number, birthday, email, memo);
}

static void cmd_delete()
{
	int field, check, result;
	char str[20];
	scanf("%d %s %d", &field, str, &check);

	result = Delete((FIELD)field, str);
	if (result != check)
		Score -= ScoreIdx;
}

static void cmd_change()
{
	int field, changefield, check, result;
	char str[20], changestr[20];
	scanf("%d %s %d %s %d", &field, str, &changefield, changestr, &check);

	result = Change((FIELD)field, str, (FIELD)changefield, changestr);
	if (result != check)
		Score -= ScoreIdx;
}

static void cmd_search()
{
	int field, returnfield, check;
	char str[20], checkstr[20];
	scanf("%d %s %d %s %d", &field, str, &returnfield, checkstr, &check);

	RESULT result = Search((FIELD)field, str, (FIELD)returnfield);

	if (result.count != check || (result.count == 1 && (strcmp(checkstr, result.str) != 0)))
		Score -= ScoreIdx;
}

static void run()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:   cmd_init();   break;
		case CMD_ADD:    cmd_add();    break;
		case CMD_DELETE: cmd_delete(); break;
		case CMD_CHANGE: cmd_change(); break;
		case CMD_SEARCH: cmd_search(); break;
		default: break;
		}
	}
}

static void init()
{
	Score = 1000;
	ScoreIdx = 1;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("SampleInput.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	int TotalScore = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		init();

		run();

		if (Score < 0)
			Score = 0;

		TotalScore += Score;
		printf("#%d %d\n", tc, Score);
	}

	PrintHash(NameHash, MOD_PRIME);
	PrintHash(NumberHash, MOD_PRIME);
	PrintHash(BDayHash, MOD_PRIME);
	PrintHash(EmailHash, MOD_PRIME);
	PrintHash(MemoHash, MOD_PRIME);
	ClearAllHashArray();
	printf("TotalScore = %d\n", TotalScore);

	return 0;
}


using namespace std;

void ResetHashArray(Node* array[], int size = MOD_PRIME);

int myStrLen(char* str){
	int length = 0;
	while (str[length++] != '\0'){}
	return length;
}

bool myStrCmp(char* source, char* dest){

	int sourceLen = myStrLen(source);
	int destLen = myStrLen(dest);

	//cout << "source Len :[" << sourceLen <<"], Desti.Length :["<< destLen << "]" << endl;

	if ( sourceLen != destLen ){ return false;}

	int i = 0;
	for ( i = 0; i< sourceLen;i++){
		//cout << source[i] << " " << dest[i] << endl;
		if (source[i] == dest[i])
			continue;
		else {
			return false;
		}
	}
	//cout << "Comp Len :[" << i << "]" << endl;
	return true;
}

void myStrCpy(char* source, char* dest, int size){
	int sl= 0, dl = 0;
	for ( int i = 0; i< size;i++){
		dest[i] = source[i];
	}
}


int InsertRecordToDatabase(char* name, char* number, char* birthday, char* email, char* memo){
	
	if (dbRecordIndex > MAX_SIZE){ return INVALID_HASH; }
	for (int i = 0; i < FIELD_LENGTH; i++){
		database[dbRecordIndex].name[i]= name[i];
		database[dbRecordIndex].number[i] = number[i];
		database[dbRecordIndex].bday[i] = birthday[i];
		database[dbRecordIndex].email[i] = email[i];
		database[dbRecordIndex].memo[i] = memo[i];
	}
	return dbRecordIndex++;
}

void ResetDatabase(){
	for (int i = 0; i < MAX_SIZE; i++){
		for (int j = 0; j < FIELD_LENGTH; j++){
			database[i].name[j] = '\0';
			database[i].number[j] = '\0';
			database[i].bday[j] = '\0';
			database[i].email[j] = '\0';
			database[i].memo[j] = '\0';
		}
	}
}

//This is needed when collision occurs
NodePtr CreateNewNode(){
	NodePtr pNewNode = nullptr;

	pNewNode = new Node();
	pNewNode->index = -1;
	pNewNode->pNext = nullptr;
	return pNewNode;
}
 
void ClearHashArray(Node* array[]){
	for (int i = 0; i < MOD_PRIME; i++){
		//cout << "Reset index:[" << i <<"]"<< endl;
		NodePtr pHead = array[i];
		while (pHead != nullptr) {
			NodePtr pTemp = pHead->pNext;
			delete pHead;
			pHead = nullptr;
			pHead = pTemp;
		}
		array[i]  = nullptr;
	}
}

void ResetHashArray(Node* array[], int size ){
	for (int i = 0; i < size; i++){
		array[i] = nullptr;
	}
}

void ClearAllHashArray(){
	ClearHashArray(NameHash);
	ClearHashArray(NumberHash);
	ClearHashArray(BDayHash);
	ClearHashArray(EmailHash);
	ClearHashArray(MemoHash);
}

void PrintHash(NodePtr hashArray[], int size){

	return;
	for ( int i =0 ;i < size;i++) {
		NodePtr pTemp = hashArray[i];
		cout << "Bucket:["<< i << "]: {";
		while ( pTemp != nullptr ){
			cout << pTemp->index << " ,";
			pTemp = pTemp->pNext;
		}
		cout<< "}" << endl;
	}
}

bool InsertIntoHashArray(Node* array[], int orgIndex, unsigned int hashValue, char value[FIELD_LENGTH]){

	if (hashValue < 0 && hashValue > MOD_PRIME){ return false; }
	//Collisson Occured
	if (array[hashValue] != nullptr){
		//cout << "Collision Occured" << endl;
		NodePtr pHead = array[hashValue];
		while (pHead->pNext){
		//	cout << "pHead Value:[" << pHead->index << "]" << endl; 
			pHead = pHead->pNext;
		}

		//cout << "Reached end of the Bucket "<< endl;
		pHead->pNext = CreateNewNode();
		pHead->pNext->index = orgIndex;
	}
	else {
		NodePtr pNewNode =  CreateNewNode();
		pNewNode->index = orgIndex;
		array[hashValue] = pNewNode;
	}
	return true;
}

int Hash(char* source, int length, FIELD fID){

	if ( source == nullptr ){ return INVALID_HASH; }
	if ( length == 0 ){ return INVALID_HASH; }

	char base_A = 'A';
	char base_a = 'a';
	char base_Z = 'Z';
	char base_z = 'z';
	
	int multiplier = MULTIPLIER;
	unsigned int hash = 0;

	if ( fID == NAME || fID == EMAIL || fID == MEMO ) {
		for (int i = 0; i < length; i++){
			if (source[i] >= base_a && source[i] <= base_z){
				hash = (hash*multiplier) + abs(source[i] - base_a);
			}
			else if (source[i] >= base_A && source[i] <= base_Z){
				hash = (hash*multiplier) + abs(source[i] - base_A);
			}
		}
	} else {
		char base_zero =  '0';
		char base_nine =  '9';

		for (int i = 0; i < length; i++){
			if (source[i] >= base_zero && source[i] <= base_nine){
				hash = (hash*multiplier) + abs(source[i] - base_zero);
			}
		}
	}
	hash %= MOD_PRIME;
	//cout << "Hash of [" << source << "], Is:[" << hash << "]" << endl;
	return hash;
}

//Fill in result in the retValue if Count == 1 else leave that field and return no of records found.
int HashLookup(FIELD field, char* str, FIELD retField, char* retValue){
	unsigned int hashValue = -1;

	int count= 0;
	NodePtr record = nullptr;
	hashValue = Hash(str, myStrLen(str), field);

	//record =  NameHash[hashValue];
	//cout << "Hash is:[" << record->index << "]" << endl;
	//cout << "Database :[" << database[record->index].name << "]" << endl;
	switch(field){
		case NAME:{
			record = NameHash[hashValue];
			//Compare with the main node
			if ( record == nullptr ){ return INVALID_HASH;}
			//Node with Collission found, now iterate and find your matching node
			NodePtr pTemp = record;
			while ( pTemp !=nullptr){
				
				//cout << "Matching:[" << database[pTemp->index].name <<"], [" << str <<"]" << endl;
				if ( myStrCmp(database[pTemp->index].name, str) == true){
					//cout << "Match Found:[" << database[pTemp->index].name <<"], [" << str <<"]" << endl;
					count++;

					if( count  <=1 ){
						if ( retField == NAME ){
							myStrCpy(retValue, database[pTemp->index].name, FIELD_LENGTH);
						} else if ( retField == NUMBER ){
							myStrCpy(retValue, database[pTemp->index].number, FIELD_LENGTH);
						} else if ( retField == BIRTHDAY ){
							myStrCpy(retValue, database[pTemp->index].bday, FIELD_LENGTH);
						} else if ( retField == EMAIL ){
							myStrCpy(retValue, database[pTemp->index].email, FIELD_LENGTH);
						} else if ( retField == MEMO ){
							myStrCpy(retValue, database[pTemp->index].memo, FIELD_LENGTH);
						}
					}
				} 
				pTemp = pTemp->pNext;
			}			
		}
		break;
		case NUMBER:{
			record = NumberHash[hashValue];
			//Compare with the main node
			if ( record == nullptr ){ return INVALID_HASH;}
			//Node with Collission found, now iterate and find your matching node
			NodePtr pTemp = record;
			while ( pTemp !=nullptr){
				
				//cout << "Matching:[" << database[pTemp->index].number <<"], [" << str <<"]" << endl;
				if ( myStrCmp(database[pTemp->index].number, str) == true){
					//cout << "Match Found:[" << database[pTemp->index].number <<"], [" << str <<"]" << endl;
					count++;

					if( count  <=1 ){
						if ( retField == NAME ){
							myStrCpy(retValue, database[pTemp->index].name, FIELD_LENGTH);
						} else if ( retField == NUMBER ){
							myStrCpy(retValue, database[pTemp->index].number, FIELD_LENGTH);
						} else if ( retField == BIRTHDAY ){
							myStrCpy(retValue, database[pTemp->index].bday, FIELD_LENGTH);
						} else if ( retField == EMAIL ){
							myStrCpy(retValue, database[pTemp->index].email, FIELD_LENGTH);
						} else if ( retField == MEMO ){
							myStrCpy(retValue, database[pTemp->index].memo, FIELD_LENGTH);
						}
					}
				} 
				pTemp = pTemp->pNext;
			}			
		}
		break;
		case BIRTHDAY:{
			record = BDayHash[hashValue];
			//Compare with the main node
			if ( record == nullptr ){ return INVALID_HASH;}
			//Node with Collission found, now iterate and find your matching node
			NodePtr pTemp = record;
			while ( pTemp !=nullptr){
				
				//cout << "Matching:[" << database[pTemp->index].bday <<"], [" << str <<"]" << endl;
				if ( myStrCmp(database[pTemp->index].bday, str) == true){
					//cout << "Match Found:[" << database[pTemp->index].bday <<"], [" << str <<"]" << endl;
					count++;

					if( count  <=1 ){
						if ( retField == NAME ){
							myStrCpy(retValue, database[pTemp->index].name, FIELD_LENGTH);
						} else if ( retField == NUMBER ){
							myStrCpy(retValue, database[pTemp->index].number, FIELD_LENGTH);
						} else if ( retField == BIRTHDAY ){
							myStrCpy(retValue, database[pTemp->index].bday, FIELD_LENGTH);
						} else if ( retField == EMAIL ){
							myStrCpy(retValue, database[pTemp->index].email, FIELD_LENGTH);
						} else if ( retField == MEMO ){
							myStrCpy(retValue, database[pTemp->index].memo, FIELD_LENGTH);
						}
					}
				} 
				pTemp = pTemp->pNext;
			}			
		}
		break;
		case EMAIL:{
			record = EmailHash[hashValue];
			//Compare with the main node
			if ( record == nullptr ){ return INVALID_HASH;}
			//Node with Collission found, now iterate and find your matching node
			NodePtr pTemp = record;
			while ( pTemp !=nullptr){
				
				//cout << "Matching:[" << database[pTemp->index].email <<"], [" << str <<"]" << endl;
				if ( myStrCmp(database[pTemp->index].email, str) == true){
					//cout << "Match Found:[" << database[pTemp->index].email <<"], [" << str <<"]" << endl;
					count++;

					if( count  <=1 ){
						if ( retField == NAME ){
							myStrCpy(retValue, database[pTemp->index].name, FIELD_LENGTH);
						} else if ( retField == NUMBER ){
							myStrCpy(retValue, database[pTemp->index].number, FIELD_LENGTH);
						} else if ( retField == BIRTHDAY ){
							myStrCpy(retValue, database[pTemp->index].bday, FIELD_LENGTH);
						} else if ( retField == EMAIL ){
							myStrCpy(retValue, database[pTemp->index].email, FIELD_LENGTH);
						} else if ( retField == MEMO ){
							myStrCpy(retValue, database[pTemp->index].memo, FIELD_LENGTH);
						}
					}
				} 
				pTemp = pTemp->pNext;
			}			
		}
		break;
		case MEMO:{
			record = MemoHash[hashValue];
			//Compare with the main node
			if ( record == nullptr ){ return INVALID_HASH;}
			//Node with Collission found, now iterate and find your matching node
			NodePtr pTemp = record;
			while ( pTemp !=nullptr){
				//cout << "Matching:[" << database[pTemp->index].memo <<"], [" << str <<"]" << endl;
				if ( myStrCmp(database[pTemp->index].memo, str) == true){
					
					//cout << "Match Found:[" << database[pTemp->index].memo <<"], [" << str <<"]" << endl;
					count++;

					if( count  <=1 ){
						if ( retField == NAME ){
							myStrCpy(retValue, database[pTemp->index].name, FIELD_LENGTH);
						} else if ( retField == NUMBER ){
							myStrCpy(retValue, database[pTemp->index].number, FIELD_LENGTH);
						} else if ( retField == BIRTHDAY ){
							myStrCpy(retValue, database[pTemp->index].bday, FIELD_LENGTH);
						} else if ( retField == EMAIL ){
							myStrCpy(retValue, database[pTemp->index].email, FIELD_LENGTH);
						} else if ( retField == MEMO ){
							myStrCpy(retValue, database[pTemp->index].memo, FIELD_LENGTH);
						}
					}
				} 
				pTemp = pTemp->pNext;
			}			
		}
		break;
	}
	return count;
}


void InitDB(){
	dbRecordIndex = 0;
	ResetDatabase();
	ResetHashArray(NameHash);
	ResetHashArray(NumberHash);
	ResetHashArray(BDayHash);
	ResetHashArray(EmailHash);
	ResetHashArray(MemoHash);
	//cout << "Init" << endl;
}

void Add(char* name, char* number, char* birthday, char* email, char* memo){

	//cout << "Add:[" << name << " " << number << " " << birthday << " "<< email << " "<< memo << "]" << endl;
	unsigned int nameHash = Hash(name, myStrLen(name), NAME);
	unsigned int numberHash = Hash(number, myStrLen(number), NUMBER);
	unsigned int bDayHash = Hash(birthday, myStrLen(birthday), BIRTHDAY);
	unsigned int emailHash = Hash(email, myStrLen(email), EMAIL);
	unsigned int memoHash = Hash(memo, myStrLen(memo), MEMO);
	//Add to Database
	int index = InsertRecordToDatabase(name, number, birthday, email, memo);
	//for (int i = 0; i < FIELD_LENGTH; i++) { record.value[i] = name[i]; }

	InsertIntoHashArray(NameHash, index, nameHash, name);
	InsertIntoHashArray(NumberHash, index, numberHash, number);
	InsertIntoHashArray(BDayHash, index, bDayHash, birthday);
	InsertIntoHashArray(EmailHash, index, emailHash, email);
	InsertIntoHashArray(MemoHash, index, memoHash, memo);

	//PrintHash(NameHash,dbRecordIndex);
	//PrintHash(NumberHash,dbRecordIndex);
	//PrintHash(BDayHash,dbRecordIndex);
	//PrintHash(EmailHash,dbRecordIndex);
	//PrintHash(MemoHash,dbRecordIndex);
	//cout << "Add" << endl;
}

int Delete(FIELD field, char* str){
	//cout << "Delete" << endl;
return 0;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr){
	//cout << "Change" << endl;
	return 0;
}

RESULT Search(FIELD field, char* str, FIELD returnfield){
	RESULT ret;
	
	int count = 0;
	count = HashLookup(field, str, returnfield, ret.str);
	if ( count == 0 ){
		cout << "Searching:[" << str << "] NOT FOUND" << endl;
	}
	return ret;
}
