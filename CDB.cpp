#include <stdio.h>
#include <string.h>

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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

extern void InitDB();
extern void Add(char* name, char* number, char* birthday, char* email, char* memo);
extern int Delete(FIELD field, char* str);
extern int Change(FIELD field, char* str, FIELD changefield, char* changestr);
extern RESULT Search(FIELD field, char* str, FIELD returnfield);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
	printf("TotalScore = %d\n", TotalScore);

	return 0;
}

#########################################
#########################################
#########################################
#########################################
#########################################

#include <iostream>
#include <conio.h>

#define INVALID_HASH -1
#define MULTIPLIER		67
#define FIELD_LENGTH	19
#define MOD_PRIME		10009
#define MAX_SIZE		50000

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

struct ListNode;
typedef struct ListNode Node;
typedef struct ListNode* NodePtr;
typedef struct ListNode** NodeDPtr;

/*typedef struct
{
	int count;
	char str[20];
} RESULT;
*/

unsigned int dbRecordIndex = 0;
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
	char value[FIELD_LENGTH];
	//std::string value;
	unsigned int index;
	NodePtr pNext;

	ListNode(){
		//value.clear();
		for (int i = 0; i < FIELD_LENGTH; i++){ value[i] = '\0'; }
		index = 0;
		pNext = nullptr;
	}
};

Node NameHash[MOD_PRIME];
Node NumberHash[MOD_PRIME];
Node BDayHash[MOD_PRIME];
Node EmailHash[MOD_PRIME];
Node MemoHash[MOD_PRIME];

DBRecord database[MAX_SIZE];

using namespace std;

int myStrLen(char* str){
	int length = 0;
	while (str[length++] != '\0'){}
	return length;
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
	for (int j = 0; j < FIELD_LENGTH; j++){ pNewNode->value[j] = '\0'; }

	return pNewNode;
}

void ClearHashArray(Node array[]){
	for (int i = 0; i < dbRecordIndex; i++){
		array[i].index = 0;
		for (int j = 0; j < FIELD_LENGTH; j++){ array[i].value[j] = '\0'; }
		NodePtr pHead = array[i].pNext;
		while (pHead != nullptr) {
			NodePtr pTemp = pHead->pNext;
			delete pHead;
			pHead = nullptr;
			pHead = pTemp;
		}
		array[i].pNext = nullptr;
	}
}

void ResetHashArray(Node array[]){
	for (int i = 0; i < dbRecordIndex; i++){
		array[i].index = 0;
		for (int j = 0; j < FIELD_LENGTH; j++){ array[i].value[j] = '\0'; }
		array[i].pNext = nullptr;
	}
}

bool InsertIntoHashArray(Node array[], int orgIndex, unsigned int hashValue, char value[FIELD_LENGTH]){

	if (hashValue < 0 && hashValue > MOD_PRIME){ return false; }
	//Collisson Occured
	if (array[hashValue].pNext != nullptr){
		NodePtr pHead = array[hashValue].pNext;
		while (pHead != nullptr){
			pHead = pHead->pNext;
		}
		pHead->pNext = CreateNewNode();

		//Copy value from argument to new node
		for (int j = 0; j < FIELD_LENGTH; j++){
			pHead->pNext->value[j] = value[j];
		}
	}
	else {
		array[hashValue].index = orgIndex;
		array[hashValue].pNext = nullptr;
		//std::string value = record.value;
		for (int j = 0; j < FIELD_LENGTH; j++){
			array[hashValue].value[j] = value[j];
		}
	}
	return true;
}

int Hash(char* source, int length){

	if ( source == nullptr ){ return INVALID_HASH; }
	if ( length == 0 ){ return INVALID_HASH; }

	char base_A = 'A';
	char base_a = 'a';
	char base_Z = 'Z';
	char base_z = 'z';
	
	int multiplier = MULTIPLIER;
	unsigned int hash = 0;

	for (int i = 0; i < length; i++){
		if (source[i] >= base_a && source[i] <= base_z){
			hash = (hash*multiplier) + abs(source[i] - base_a);
		}
		else if (source[i] >= base_A && source[i] <= base_Z){
			hash = (hash*multiplier) + abs(source[i] - base_A);
		}
	}
	hash %= MOD_PRIME;
	cout << "Hash of [" << source << "], Is:[" << hash << "]" << endl;
	return hash;
}

void InitDB(){
	dbRecordIndex = 0;
	ResetDatabase();
	ResetHashArray(NameHash);
	ResetHashArray(NumberHash);
	ResetHashArray(BDayHash);
	ResetHashArray(EmailHash);
	ResetHashArray(MemoHash);
	cout << "Init" << endl;
}

void Add(char* name, char* number, char* birthday, char* email, char* memo){

	unsigned int hashValue = Hash(name, myStrLen(name));

	//Add to Database
	InsertRecordToDatabase(name, number, birthday, email, memo);
	//for (int i = 0; i < FIELD_LENGTH; i++) { record.value[i] = name[i]; }
	InsertIntoHashArray(NameHash, dbRecordIndex, hashValue, name);
	cout << "Add" << endl;
}

int Delete(FIELD field, char* str){
	cout << "Delete" << endl;
return 0;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr){
	cout << "Change" << endl;
	return 0;
}

RESULT Search(FIELD field, char* str, FIELD returnfield){
	RESULT ret;
	ret.count = 1;
	return ret;
}
