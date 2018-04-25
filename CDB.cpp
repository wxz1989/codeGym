#include <stdio.h>
#include <string.h>
#include <iostream>
#include <conio.h>

#define INVALID_HASH -1
#define MULTIPLIER		67
#define FIELD_LENGTH	20
#define MOD_PRIME		10009
#define MAX_SIZE		50000

using namespace std;

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
	int index;
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



void PrintRecordFromDatabase(int i){

	cout << " ********* RECORD ********* " << endl;
	cout << "Name:[" << database[i].name << "]" << endl;
	cout << "Number:[" << database[i].number << "]" << endl;
	cout << "Birthday:[" << database[i].bday << "]" << endl;
	cout << "Email:[" << database[i].email << "]" << endl;
	cout << "Memo:[" << database[i].memo << "]" << endl;
	cout << " ************************** " << endl;
}

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
	if (result != check){
		Score -= ScoreIdx;
		cout << "Delete Failed : Expected Count:[" << check << "], Received Count:[" << result << "]" << endl;
	}
}

static void cmd_change()
{
	int field, changefield, check, result;
	char str[20], changestr[20];
	scanf("%d %s %d %s %d", &field, str, &changefield, changestr, &check);

	result = Change((FIELD)field, str, (FIELD)changefield, changestr);
	if (result != check) {
		Score -= ScoreIdx;
		cout << "Change Failed : Expected Count:[" << check << "], Received Count:[" << result << "]" << endl;
	}
}

static void cmd_search()
{
	int field, returnfield, check;
	char str[20], checkstr[20];

	scanf("%d %s %d %s %d", &field, str, &returnfield, checkstr, &check);
	RESULT result = Search((FIELD)field, str, (FIELD)returnfield);

	if (result.count != check || (result.count == 1 && (strcmp(checkstr, result.str) != 0))){
		Score -= ScoreIdx;
		cout << "Search Failed : Expected Count:[" << check << "], Received Count:[" << result.count << "], Expected Value:[" << checkstr << "], Received Value:[" << result.str << "]" << endl;
	}
}

static void run()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int cmd;
		scanf("%d", &cmd);
		//cout << "Iteration:[" << i <<"]" << endl;
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
	//PrintHash(EmailHash, MOD_PRIME);
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

	ClearAllHashArray();
	printf("TotalScore = %d\n", TotalScore);
	_getche();
	return 0;
}



void ResetHashArray(Node* array[], int size = MOD_PRIME);

int myStrLen(char* str){
	int length = 0;
	while (str[length++] != '\0'){}
	return length;
}

bool myStrCmp(char* source, char* dest){

	int sourceLen = myStrLen(source);
	int destLen = myStrLen(dest);

	if (sourceLen != destLen){ return false; }

	for (int i = 0; i < sourceLen; i++){
		if (source[i] != dest[i]) { return false; }
	}
	return true;
}

void myStrCpy(char* dest, char* source, int size){

	if (dest == nullptr || source == nullptr || myStrLen(source) == 0){ return; }
	int sourceLen = myStrLen(source);
	int copyLen = (sourceLen < FIELD_LENGTH ? sourceLen : FIELD_LENGTH);
	for (int i = 0; i < copyLen; i++){ dest[i] = source[i]; }
}

void CompareAndCopy(NodePtr record, FIELD sourceField, char* str, FIELD retField, char* ret, int& c){

	if (record == nullptr){ return;  }
	//cout << "Start Source:[" << sourceFieldStr << "] Comp:[" << str << "Ret:[" << ret << "], Count:[" << c << "]" << endl; 
	NodePtr pTemp = record;
	while (pTemp != nullptr){
		if (pTemp->index != -1){
			char sourceFieldStr[FIELD_LENGTH] = { '\0' };

			switch (sourceField){
			case NAME:{ myStrCpy(sourceFieldStr, database[pTemp->index].name, myStrLen(database[pTemp->index].name)); } break;
			case NUMBER:{ myStrCpy(sourceFieldStr, database[pTemp->index].number, myStrLen(database[pTemp->index].number)); } break;
			case BIRTHDAY:{ myStrCpy(sourceFieldStr, database[pTemp->index].bday, myStrLen(database[pTemp->index].bday)); } break;
			case EMAIL:{ myStrCpy(sourceFieldStr, database[pTemp->index].email, myStrLen(database[pTemp->index].email)); } break;
			case MEMO:{ myStrCpy(sourceFieldStr, database[pTemp->index].memo, myStrLen(database[pTemp->index].memo)); } break;
			}

			if (myStrCmp(sourceFieldStr, str) == true){
				if (c < 1){
					if (retField == NAME){  myStrCpy(ret, database[pTemp->index].name, FIELD_LENGTH); }
					else if (retField == NUMBER){ myStrCpy(ret, database[pTemp->index].number, FIELD_LENGTH); }
					else if (retField == BIRTHDAY){ myStrCpy(ret, database[pTemp->index].bday, FIELD_LENGTH); }
					else if (retField == EMAIL){ myStrCpy(ret, database[pTemp->index].email, FIELD_LENGTH); }
					else if (retField == MEMO){ myStrCpy(ret, database[pTemp->index].memo, FIELD_LENGTH); }
				}
				c++;
			}
		}
		pTemp = pTemp->pNext;
	}
	//cout << "Comp:[" << str << "Ret:[" << ret << "], Count:[" << c << "]" << endl;
}


void PrintDatabase(){
	for (unsigned int i = 0; i < dbRecordIndex; i++){ PrintRecordFromDatabase(i); }
}

int Hash(char* source, int length, FIELD fID){

	if (source == nullptr){ return INVALID_HASH; }
	if (length == 0){ return INVALID_HASH; }

	char base_A = 'A';
	char base_a = 'a';
	char base_Z = 'Z';
	char base_z = 'z';

	int multiplier = MULTIPLIER;
	unsigned int hash = 0;

	if (fID == NAME || fID == EMAIL || fID == MEMO) {
		for (int i = 0; i < length; i++){
			if (source[i] >= base_a && source[i] <= base_z){
				hash = (hash*multiplier) + abs(source[i] - base_a);
			}
			else if (source[i] >= base_A && source[i] <= base_Z){
				hash = (hash*multiplier) + abs(source[i] - base_A);
			}
		}
	}
	else {
		char base_zero = '0';
		char base_nine = '9';

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

int CleanSlate(int dbIndex, char* str, FIELD field){

	int count = 0;
	int nameCount = 0;
	int numberCount = 0;
	int bDayCount = 0;
	int emailCount = 0;
	int memoCount = 0;

	NodePtr record = nullptr;
	NodePtr pTemp = nullptr;

	if (dbIndex < 0 || dbIndex > MOD_PRIME) { cout << "Invalid Record Index" << endl;  return count; }

	//PrintRecordFromDatabase(dbIndex);
	unsigned int hash = Hash(database[dbIndex].name, myStrLen(database[dbIndex].name), NAME);
	record = NameHash[hash];
	if (record == nullptr){ cout << "name Record is null" << endl; return count; }

	pTemp = record;
	while (pTemp != nullptr){
		if (pTemp->index != -1){
			if (myStrCmp(database[dbIndex].name, database[pTemp->index].name) == true) {
				//cout << "FoundIndex:[" << database[dbIndex].memo << "], Iterated Index:[" << database[pTemp->index].memo << "], Count:[" << name<< "]" << endl;
				pTemp->index = -1;
				nameCount++;
				break;
			}
		}
		pTemp = pTemp->pNext;
	}

	hash = Hash(database[dbIndex].number, myStrLen(database[dbIndex].number), NUMBER);
	record = NumberHash[hash];
	if (record == nullptr){ cout << "Number Record is null" << endl; return count; }
	pTemp = record;

	while (pTemp != nullptr){
		if (pTemp->index != -1){
			if (myStrCmp(database[dbIndex].number, database[pTemp->index].number) == true){
				//	cout << "FoundIndex:[" << database[dbIndex].number << "], Iterated Index:[" << database[pTemp->index].number << "], Count:[" << numberCount << "]" << endl;
				pTemp->index = -1;
				numberCount++;
				break;
			}
		}
		pTemp = pTemp->pNext;
	}

	hash = Hash(database[dbIndex].bday, myStrLen(database[dbIndex].bday), BIRTHDAY);
	record = BDayHash[hash];
	if (record == nullptr){ cout << "bday Record is null" << endl; return count; }

	pTemp = record;
	while (pTemp != nullptr){
		if (pTemp->index != -1){
			if (myStrCmp(database[dbIndex].bday, database[pTemp->index].bday) == true){
				//cout << "FoundIndex:[" << database[dbIndex].bday << "], Iterated Index:[" << database[pTemp->index].bday << "], Count:[" << bDayCount << "]" << endl;
				pTemp->index = -1;
				bDayCount++;
				break;
			}
		}
		pTemp = pTemp->pNext;
	}

	hash = Hash(database[dbIndex].email, myStrLen(database[dbIndex].email), EMAIL);
	record = EmailHash[hash];
	if (record == nullptr){ cout << "email Record is null" << endl; return count; }

	pTemp = record;
	while (pTemp != nullptr){
		if (pTemp->index != -1){
			if (myStrCmp(database[dbIndex].email, database[pTemp->index].email) == true){
				//cout << "FoundIndex:[" << database[dbIndex].email << "], Iterated Index:[" << database[pTemp->index].email << "], Count:[" << emailCount << "]" << endl;
				pTemp->index = -1;
				emailCount++;
				break;
			}
		}
		pTemp = pTemp->pNext;
	}

	hash = Hash(database[dbIndex].memo, myStrLen(database[dbIndex].memo), MEMO);
	record = MemoHash[hash];
	if (record == nullptr){ cout << "memo Record is null" << endl; return count; }

	pTemp = record;
	while (pTemp != nullptr){
		if (pTemp->index != -1){
			if (myStrCmp(database[dbIndex].memo, database[pTemp->index].memo) == true){
				//cout << "FoundIndex:[" << database[dbIndex].memo << "], Iterated Index:[" << database[pTemp->index].memo << "], Count:[" << memoCount << "]" << endl;
				pTemp->index = -1;
				memoCount++;
				break;
			}
		}
		pTemp = pTemp->pNext;
	}

	//cout << nameCount << " " << numberCount << " " << bDayCount << " " << emailCount << " " << memoCount << endl;
	if (nameCount >= 0 || numberCount >= 0 || bDayCount >= 0 || emailCount >= 0 || memoCount >= 0){ count = 1; }
	return count;
}

int InsertRecordToDatabase(char* name, char* number, char* birthday, char* email, char* memo){

	if (dbRecordIndex > MAX_SIZE){ return INVALID_HASH; }

	for (int i = 0; i < myStrLen(name); i++){ database[dbRecordIndex].name[i] = name[i]; };
	for (int i = 0; i < myStrLen(number); i++){ database[dbRecordIndex].number[i] = number[i]; };
	for (int i = 0; i < myStrLen(birthday); i++){ database[dbRecordIndex].bday[i] = birthday[i]; };
	for (int i = 0; i < myStrLen(email); i++){ database[dbRecordIndex].email[i] = email[i]; };
	for (int i = 0; i < myStrLen(memo); i++){ database[dbRecordIndex].memo[i] = memo[i]; };

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
		array[i] = nullptr;
	}
}

void ResetHashArray(Node* array[], int size){

	for (int i = 0; i < size; i++){ array[i] = nullptr; }
}

void ClearAllHashArray(){
	ClearHashArray(NameHash);
	ClearHashArray(NumberHash);
	ClearHashArray(BDayHash);
	ClearHashArray(EmailHash);
	ClearHashArray(MemoHash);
}

void PrintHash(NodePtr hashArray[], int size){
	for (int i = 0; i < size; i++) {
		NodePtr pTemp = hashArray[i];
		cout << "Bucket:[" << i << "]: {";
		while (pTemp != nullptr){
			cout << pTemp->index << " ,";
			pTemp = pTemp->pNext;
		}
		cout << "}" << endl;
	}
}

bool InsertIntoHashArray(Node* array[], int orgIndex, unsigned int hashValue, char value[FIELD_LENGTH]){

	NodePtr pHead = nullptr;
	NodePtr pNewNode = nullptr;

	if (hashValue < 0 && hashValue > MOD_PRIME){ return false; }

	if (array[hashValue] != nullptr){
		pHead = array[hashValue];
		while (pHead->pNext){ pHead = pHead->pNext; }

		pHead->pNext = CreateNewNode();
		pHead->pNext->index = orgIndex;
	}
	else {
		pNewNode = CreateNewNode();

		pNewNode->index = orgIndex;
		array[hashValue] = pNewNode;
	}
	return true;
}



//Fill in result in the retValue if Count == 1 else leave that field and return no of records found.
int HashLookup(FIELD field, char* str, FIELD retField, RESULT& res){
	unsigned int hashValue = -1;

	int count = 0;
	NodePtr record = nullptr;
	hashValue = Hash(str, myStrLen(str), field);

	switch (field){
	case NAME:{
				  record = NameHash[hashValue];
				  if (record == nullptr){ return count; }
				  /*NodePtr pTemp = record;

				  while (pTemp != nullptr){
					  if (pTemp->index != -1){
						  if (myStrCmp(database[pTemp->index].name, str) == true){
							  if (count < 1){
								  if (retField == NAME){
									  myStrCpy(res.str, database[pTemp->index].name, FIELD_LENGTH);
								  }
								  else if (retField == NUMBER){
									  myStrCpy(res.str, database[pTemp->index].number, FIELD_LENGTH);
								  }
								  else if (retField == BIRTHDAY){
									  myStrCpy(res.str, database[pTemp->index].bday, FIELD_LENGTH);
								  }
								  else if (retField == EMAIL){
									  myStrCpy(res.str, database[pTemp->index].email, FIELD_LENGTH);
								  }
								  else if (retField == MEMO){
									  myStrCpy(res.str, database[pTemp->index].memo, FIELD_LENGTH);
								  }
							  }
							  count++;
						  }
					  }
					  pTemp = pTemp->pNext;
				  }*/
				  CompareAndCopy(record, field , str, retField, res.str, count);
	}
		break;
	case NUMBER:{
					record = NumberHash[hashValue];
					if (record == nullptr){ return count; }
					CompareAndCopy(record, field, str, retField, res.str, count);
	}
		break;
	case BIRTHDAY:{
					  record = BDayHash[hashValue];
					  if (record == nullptr){ return count; }
					  CompareAndCopy(record, field, str, retField, res.str, count);
	}
		break;
	case EMAIL:{
				   record = EmailHash[hashValue];
				   if (record == nullptr){ return count; }
				   CompareAndCopy(record, field, str, retField, res.str, count);
	}
		break;
	case MEMO:{
				  record = MemoHash[hashValue];
				  if (record == nullptr){ return count; }
				  CompareAndCopy(record, field, str, retField, res.str, count);
	}
		break;
	}
	res.count = count;
	return count;
}

int DeleteLookUp(FIELD field, char* str){
	unsigned int hashValue = -1;
	int count = 0;
	NodePtr record = nullptr;
	hashValue = Hash(str, myStrLen(str), field);

	switch (field){
	case NAME:{
				  record = NameHash[hashValue];
				  //Compare with the main node
				  if (record == nullptr){ return count; }

				  //Node with Collission found, now iterate and find your matching node
				  NodePtr pTemp = record;
				  while (pTemp != nullptr){
					  if (pTemp->index != -1) {
						  if (myStrCmp(database[pTemp->index].name, str) == true){
							  if (CleanSlate(pTemp->index, str, field) > 0){ count++; }
						  }
					  }
					  pTemp = pTemp->pNext;
				  }
	}
		break;
	case NUMBER:{
					record = NumberHash[hashValue];
					//Compare with the main node
					if (record == nullptr){ return count; }
					//if (record->index == -1) { return count; }
					NodePtr pTemp = record;
					while (pTemp != nullptr){
						if (pTemp->index != -1) {
							if (myStrCmp(database[pTemp->index].number, str) == true){
								if (CleanSlate(pTemp->index, str, field) > 0){ count++; }
							}
						}
						pTemp = pTemp->pNext;
					}
	}
		break;
	case BIRTHDAY:{
					  record = BDayHash[hashValue];
					  //Compare with the main node
					  if (record == nullptr){ return count; }
					  NodePtr pTemp = record;
					  while (pTemp != nullptr){
						  if (pTemp->index != -1) {
							  if (myStrCmp(database[pTemp->index].bday, str) == true){
								  if (CleanSlate(pTemp->index, str, field) > 0){ count++; }
							  }
						  }
						  pTemp = pTemp->pNext;
					  }
	}
		break;
	case EMAIL:{
				   record = EmailHash[hashValue];
				   //Compare with the main node
				   if (record == nullptr){ return count; }
				   NodePtr pTemp = record;
				   while (pTemp != nullptr){
					   if (pTemp->index != -1) {
						   if (myStrCmp(database[pTemp->index].email, str) == true){
							   if (CleanSlate(pTemp->index, str, field) > 0){ count++; }
						   }
					   }
					   pTemp = pTemp->pNext;
				   }
	}
		break;
	case MEMO:{
				  record = MemoHash[hashValue];
				  //Compare with the main node
				  if (record == nullptr){ return count; }
				  NodePtr pTemp = record;
				  while (pTemp != nullptr){
					  if (pTemp->index != -1) {
						  if (myStrCmp(database[pTemp->index].memo, str) == true){
							  if (CleanSlate(pTemp->index, str, field) > 0){ count++; }
						  }
					  }
					  pTemp = pTemp->pNext;
				  }
	}
		break;
	}
	return count;
}

int ChangeLookUp(FIELD field, char* str, FIELD fieldToChange, char* val){
	unsigned int hashValue = -1;
	int count = 0;
	NodePtr record = nullptr;
	hashValue = Hash(str, myStrLen(str), field);

	switch (field){
	case NAME:{
				  record = NameHash[hashValue];
				  //Compare with the main node
				  if (record == nullptr){ return count; }
				  // PrintRecordFromDatabase(record->index);
				  NodePtr pTemp = record;
				  while (pTemp != nullptr){
					  if (pTemp->index != -1){
						  if (myStrCmp(database[pTemp->index].name, str) == true){
							  count++;
							  switch (fieldToChange){
							  case NAME:{
											for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].name[i] = '\0'; }
											for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].name[i] = val[i]; }

											unsigned int newValue = Hash(val, myStrLen(val), NAME);
											InsertIntoHashArray(NameHash, pTemp->index, newValue, val);
							  }
								  break;
							  case NUMBER:{
											  for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].number[i] = '\0'; }
											  for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].number[i] = val[i]; }

											  unsigned int newValue = Hash(val, myStrLen(val), NUMBER);
											  InsertIntoHashArray(NumberHash, pTemp->index, newValue, val);
							  }
								  break;
							  case BIRTHDAY:{
												for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].bday[i] = '\0'; }
												for (int i = 0; i < myStrLen(val); i++) {
													database[pTemp->index].bday[i] = val[i];
												}
												unsigned int newValue = Hash(val, myStrLen(val), BIRTHDAY);
												InsertIntoHashArray(BDayHash, pTemp->index, newValue, val);
							  }
								  break;
							  case EMAIL:{
											 for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].email[i] = '\0'; }
											 for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].email[i] = val[i]; }

											 unsigned int newValue = Hash(val, myStrLen(val), EMAIL);
											 InsertIntoHashArray(EmailHash, pTemp->index, newValue, val);
							  }
								  break;
							  case MEMO:{
											for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].memo[i] = '\0'; }
											for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].memo[i] = val[i]; }

											unsigned int newValue = Hash(val, myStrLen(val), MEMO);
											InsertIntoHashArray(MemoHash, pTemp->index, newValue, val);
							  }
								  break;
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
					if (record == nullptr){ return count; }
					//PrintRecordFromDatabase(record->index);
					NodePtr pTemp = record;
					while (pTemp != nullptr){
						if (pTemp->index != -1){
							if (myStrCmp(database[pTemp->index].number, str) == true){
								count++;
								switch (fieldToChange){
								case NAME:{
											  for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].name[i] = '\0'; }
											  for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].name[i] = val[i]; }

											  unsigned int newValue = Hash(val, myStrLen(val), NAME);
											  InsertIntoHashArray(NameHash, pTemp->index, newValue, val);
								}
									break;
								case NUMBER:{
												for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].number[i] = '\0'; }
												for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].number[i] = val[i]; }
												unsigned int newValue = Hash(val, myStrLen(val), NUMBER);
												InsertIntoHashArray(NumberHash, pTemp->index, newValue, val);
								}
									break;
								case BIRTHDAY:{
												  for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].bday[i] = '\0'; }
												  for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].bday[i] = val[i]; }
												  unsigned int newValue = Hash(val, myStrLen(val), BIRTHDAY);
												  InsertIntoHashArray(BDayHash, pTemp->index, newValue, val);
								}
									break;
								case EMAIL:{
											   for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].email[i] = '\0'; }
											   for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].email[i] = val[i]; }
											   unsigned int newValue = Hash(val, myStrLen(val), EMAIL);
											   InsertIntoHashArray(EmailHash, pTemp->index, newValue, val);
								}
									break;
								case MEMO:{
											  for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].memo[i] = '\0'; }
											  for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].memo[i] = val[i]; }

											  unsigned int newValue = Hash(val, myStrLen(val), MEMO);
											  InsertIntoHashArray(MemoHash, pTemp->index, newValue, val);
								}
									break;
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
					  if (record == nullptr){ return count; }
					  // PrintRecordFromDatabase(record->index);
					  NodePtr pTemp = record;
					  while (pTemp != nullptr){

						  if (pTemp->index != -1){

							  if (myStrCmp(database[pTemp->index].bday, str) == true){
								  count++;
								  switch (fieldToChange){
								  case NAME:{
												for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].name[i] = '\0'; }
												for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].name[i] = val[i]; }

												unsigned int newValue = Hash(val, myStrLen(val), NAME);
												InsertIntoHashArray(NameHash, pTemp->index, newValue, val);
								  }
									  break;
								  case NUMBER:{
												  for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].number[i] = '\0'; }
												  for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].number[i] = val[i]; }
												  unsigned int newValue = Hash(val, myStrLen(val), NUMBER);
												  InsertIntoHashArray(NumberHash, pTemp->index, newValue, val);
								  }
									  break;
								  case BIRTHDAY:{
													for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].bday[i] = '\0'; }
													for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].bday[i] = val[i]; }
													unsigned int newValue = Hash(val, myStrLen(val), BIRTHDAY);
													InsertIntoHashArray(BDayHash, pTemp->index, newValue, val);
								  }
									  break;
								  case EMAIL:{
												 for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].email[i] = '\0'; }
												 for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].email[i] = val[i]; }

												 unsigned int newValue = Hash(val, myStrLen(val), EMAIL);
												 InsertIntoHashArray(EmailHash, pTemp->index, newValue, val);
								  }
									  break;
								  case MEMO:{
												for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].memo[i] = '\0'; }
												for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].memo[i] = val[i]; }

												unsigned int newValue = Hash(val, myStrLen(val), MEMO);
												InsertIntoHashArray(MemoHash, pTemp->index, newValue, val);
								  }
									  break;
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
				   if (record == nullptr){ return count; }
				   //  PrintRecordFromDatabase(record->index);
				   NodePtr pTemp = record;
				   while (pTemp != nullptr){
					   if (pTemp->index != -1){
						   if (myStrCmp(database[pTemp->index].email, str) == true){
							   count++;
							   switch (fieldToChange){
							   case NAME:{
											 for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].name[i] = '\0'; }
											 for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].name[i] = val[i]; }

											 unsigned int newValue = Hash(val, myStrLen(val), NAME);
											 InsertIntoHashArray(NameHash, pTemp->index, newValue, val);
							   }
								   break;
							   case NUMBER:{
											   for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].number[i] = '\0'; }
											   for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].number[i] = val[i]; }

											   unsigned int newValue = Hash(val, myStrLen(val), NUMBER);
											   InsertIntoHashArray(NumberHash, pTemp->index, newValue, val);
							   }
								   break;
							   case BIRTHDAY:{
												 for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].bday[i] = '\0'; }
												 for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].bday[i] = val[i]; }

												 unsigned int newValue = Hash(val, myStrLen(val), BIRTHDAY);
												 InsertIntoHashArray(BDayHash, pTemp->index, newValue, val);
							   }
								   break;
							   case EMAIL:{
											  for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].email[i] = '\0'; }
											  for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].email[i] = val[i]; }

											  unsigned int newValue = Hash(val, myStrLen(val), EMAIL);
											  InsertIntoHashArray(EmailHash, pTemp->index, newValue, val);
							   }
								   break;
							   case MEMO:{
											 for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].memo[i] = '\0'; }
											 for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].memo[i] = val[i]; }

											 unsigned int newValue = Hash(val, myStrLen(val), MEMO);
											 InsertIntoHashArray(MemoHash, pTemp->index, newValue, val);
							   }
								   break;
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
				  if (record == nullptr){ return count; }
				  // PrintRecordFromDatabase(record->index);
				  NodePtr pTemp = record;
				  while (pTemp != nullptr){
					  if (pTemp->index != -1){
						  if (myStrCmp(database[pTemp->index].memo, str) == true){
							  count++;
							  switch (fieldToChange){
							  case NAME:{
											for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].name[i] = '\0'; }
											for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].name[i] = val[i]; }
											unsigned int newValue = Hash(val, myStrLen(val), NAME);
											InsertIntoHashArray(NameHash, pTemp->index, newValue, val);
							  }
								  break;
							  case NUMBER:{
											  for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].number[i] = '\0'; }
											  for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].number[i] = val[i]; }

											  unsigned int newValue = Hash(val, myStrLen(val), NUMBER);
											  InsertIntoHashArray(NumberHash, pTemp->index, newValue, val);
							  }
								  break;
							  case BIRTHDAY:{
												for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].bday[i] = '\0'; }
												for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].bday[i] = val[i]; }

												unsigned int newValue = Hash(val, myStrLen(val), BIRTHDAY);
												InsertIntoHashArray(BDayHash, pTemp->index, newValue, val);
							  }
								  break;
							  case EMAIL:{
											 for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].email[i] = '\0'; }
											 for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].email[i] = val[i]; }

											 unsigned int newValue = Hash(val, myStrLen(val), EMAIL);
											 InsertIntoHashArray(EmailHash, pTemp->index, newValue, val);
							  }
								  break;
							  case MEMO:{
											for (int i = 0; i < FIELD_LENGTH; i++) { database[pTemp->index].memo[i] = '\0'; }
											for (int i = 0; i < myStrLen(val); i++) { database[pTemp->index].memo[i] = val[i]; }

											unsigned int newValue = Hash(val, myStrLen(val), MEMO);
											InsertIntoHashArray(MemoHash, pTemp->index, newValue, val);
							  }
								  break;
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
}

void Add(char* name, char* number, char* birthday, char* email, char* memo){

	//cout << "Add:[" << name << " " << number << " " << birthday << " " << email << " " << memo << "]" << endl;
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
}

int Delete(FIELD field, char* str){
	int count = 0;
	count = DeleteLookUp(field, str);
	return count;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr){
	int count = 0;
	count = ChangeLookUp(field, str, changefield, changestr);
	return count;
}

RESULT Search(FIELD field, char* str, FIELD returnfield){
	RESULT ret;
	ret.count = 0;
	for (int i = 0; i < FIELD_LENGTH; i++){ ret.str[i] = '\0'; }
	HashLookup(field, str, returnfield, ret);
	return ret;
}
