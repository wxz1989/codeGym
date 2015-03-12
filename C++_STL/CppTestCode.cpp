#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <tr1/memory>
#include <tr1/random>
#include <main.h>
#include <Device.h>
#include <map>
using namespace std;
using namespace std::tr1;
void multimapTest();
//string SYNC_DATABASE_FILE_NAME = "SyncData.db";
string SyncContract::SYNC_TABLE_NAME = "delete_info";
#define FILE_PATH 			"/home/rakesh.2206/Results.txt"
string SyncContract::DeleteInfo::_ID = "_id";
string SyncContract::DeleteInfo::_ROW_ID = "row_id";
string SyncContract::DeleteInfo::DATA_TYPE = "data_type";
string SyncContract::DeleteInfo::UUID = "uuid";
string SyncContract::DeleteInfo::DELETE_TIME = "delete_time";
void PrintTestResult (std::string testName);
Test*	Test::pInstance = NULL;
Test::Test() {
}
Test::~Test() {
}
void Test::DeleteInstance(void) {
	delete pInstance;
	pInstance = NULL;
}
Test*
Test::GetInstance() {
	pInstance = new (std::nothrow) Test();
	std::atexit(DeleteInstance);
	return pInstance;
}
void
Test::CreateTable() {
	return;
}
#define IF_FREE_PTR(pointer) \
	do { \
		if(pointer != NULL) { \
			free(pointer);	\
			pointer = NULL;	\
		}	\
	} while (0);
char* GetWhereQuery(const char* const pCompeteQuery);
bool 	IsPalindrome(const char*	pInput);
int 	MakePalindrome(const char*	pInput,  int length = 0);
static char* GetTableName(const char* pManifestId);
long int	GetEpochTime(void);
void RandomNumberGenerator(void);
int MakePalindrome(const char*	pInput, int length) {
	int steps = -1;
	return steps;
}
bool IsPalindrome(const char*	pInput) {
	int length = 0;
	if ( pInput == NULL )
		return false;
	while ( pInput[length++] );					//NULL terminated string.
	length--;
	for ( int i = 0; i <= length / 2; i++) {
		if ( pInput[i]  != pInput [(length-1) - i])
			return false;
	}
	return true;
}
int main() {
	multimapTest();
	return 0;
	int length =10;
	string newString = "20";
	char buff[100];
	snprintf(buff, 100, "%d", length);
	newString.assign(buff);
	cout<<newString<<endl;
	return 0 ;
	int**		pDouble  = (int**) calloc(length, sizeof(int*) );
	for (int i = 0; i< length; i++) {
		pDouble[i] = (int*) malloc(sizeof(int));
		*pDouble[i] = i*length;
	}
	for(int index = 0; index < length; index++)
		IF_FREE_PTR(pDouble[index]);
	IF_FREE_PTR(pDouble);
	string datauuid;
	string propertyStr("");
	string strHMac = "MzY3ZDNhNTg2ZjkyNWFkZWQ3NjI0NTE1Y2FlNzM4MjJAAAAAAQQAABIAAABIRUFMVEhfRVZFTlRfVFlQRQAeAAAASEVBTFRIX0VWRU5UX0FERF9PQlNFUlZFUl9SRVMAQwAAAAEEAAAeAAAASEVBTFRIX0VWRU5UX0FERF9PQlNFUlZFUl9SRVMAFQAAAG9ic2VydmVyX2FkZF9zdWNjZXNzAA==";
	propertyStr += "gajjar";
	if ( propertyStr == "rakesh" ) {
		printf("will never come here [%s]", propertyStr.c_str());
	} else if ( propertyStr.compare("gajjar") ) {
		printf("Compare func test [%s]", propertyStr.c_str());
	} else {
		printf("not compared [%s]", propertyStr.c_str());
	}
	printf("\nStr Len of HMAC [%d]", strHMac.length());
	return 0 ;
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	/*
		int T, i = 0, answer = 0;
		std::string input;
		int length = 0;
		cin >> T;
		for ( i = 0 ; i < T ; i++)
		{
			cin>>input;
			if ( input.empty() == false )
			{
				if ( IsPalindrome(input.c_str()) == false )
				{
					if ( length % 2 == 0 )
						MakePalindrome(input.c_str(), length);
					else
						MakePalindrome(input.c_str(), length+1);
				}
			}
			cout<<answer<<endl;
			i = 0;
			input.clear();
			answer = 0;
		}
	*/
	/*int** ar = new int*[10];
	printf("testing %d \n",ar[11]);
	ar[11] = 10;
	printf("testingsecond %d \n",ar[11]);
	 * */
	int i = 10;
	while ( i >0 ) {
		PrintTestResult("Insert");
		PrintTestResult("Read");
		PrintTestResult("Update");
		PrintTestResult("Delete");
		i--;
	}
	string tableName="com.samsung.health.heart_rate";
	string modifiedTableName="com_samsung_health_heart_rate";
	string whereCommand ="i == j ";
	string dbAttachQuery = "ATTACH DATABASE '" + tableName + "' AS '" + modifiedTableName + "';" ;
	printf("\nSubQuery: %s", dbAttachQuery.c_str());
	string subQuery  = "SELECT __id, datauuid, '" + tableName + "', strftime('%s', 'now') FROM " + modifiedTableName + " WHERE " + whereCommand;
	string query = "INSERT INTO SyncData." + SyncContract::SYNC_TABLE_NAME + " ("
	               + SyncContract::DeleteInfo::_ROW_ID + ", "
	               + SyncContract::DeleteInfo::DATA_TYPE + ", "
	               + SyncContract::DeleteInfo::UUID + ", "
	               + SyncContract::DeleteInfo::DELETE_TIME + ") "+ subQuery;
	printf("\nSubQuery: %s", subQuery.c_str());
	printf("\nquery : %s", query.c_str());
	return 0 ;
	GetWhereQuery(NULL);
	query.clear();
	char str[50] = {0};
	DeviceProfileContract		deviceInfo;
	sprintf(str,"%d", 10);
	query = "INSERT INTO "  +
	        deviceInfo.DEVICE_TABLE_NAME + " (" +
	        deviceInfo.__deviceMeta.DEVICE_UUID +  ","  +
	        deviceInfo.__deviceMeta.UUID_SEED  + "," +
	        deviceInfo.__deviceMeta.NAME  + ","  +
	        deviceInfo.__deviceMeta.MANUFACTURER + "," +
	        deviceInfo.__deviceMeta.MODEL+ ","
	        + deviceInfo.__deviceMeta.DEVICE_GROUP +
	        ") VALUES (" + "\"" + "test1" + "\"" + "," + "\"" + "test1" +
	        "\"" + "," + "\"" + "test1" + "\"" + "," + "\"" + "test1"+ "\"" + "," + "\"" +
	        "test1" + "\""+ "," + string(str) + ");";
	//string __id("12345"), tableName("com.samsung.health.heart_rate"), datauuid("1234-abcd-5678");
	tableName.clear();
	datauuid.clear();
	tableName.append("com.samsung.health.heart_rate"), datauuid.append("1234-abcd-5678");
	int __id = 41312038109;
	char rowId[50] = {0};
	string Id;
	sprintf(rowId, "%d", __id);
	Id.append(rowId);
	query = "INSERT INTO deleted_uuid (rowId, datatype, datauuid, deletedtime) VALUES (" + Id +  ",'"+ tableName + "','" + datauuid +  "',strftime('%s', 'now') )";
	//query = "INSERT INTO deleted_uuid (rowId, datatype, datauuid, deletedtime) VALUES ('" + __id +  "','"+ tableName + "','" + datauuid +  "', strftime('%s', 'now') )";
	printf("\nquery : %s", query.c_str());
	//Test*	pInstance = Test::GetInstance();
	//pInstance->CreateTable();
	;
	return 0;
	char** ary = (char**)new int[4];
	for(int i = 0; i < 4; ++i)
		ary[i] = new char[4];
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			ary[i][j] = 'A';
	}
	for(int i =0; i< 2; i++) {
		for(int j =0; j<2; j++) {
			ary[i][j] = 'a';
		}
	}
	char	string_format[100] = {0};
	snprintf (string_format, 10, "-%s-", "1234567");
	cout<<string_format<<endl;
	char*		pTest= "Create Trigger Noti_Before_Delete_Trigger Before Delete on ";
	std::string  triggerQuery;
	triggerQuery.append(pTest);
	triggerQuery.append("tableName");
	triggerQuery.append(" For each row ");
	triggerQuery.append("Begin select datauuid from ");
	triggerQuery.append("tableName");
	triggerQuery.append("; End");
	printf("Trigger Query[%s]\n", triggerQuery.c_str());
	char* 		pConvertedName = GetTableName("com.samsung.health.heart_rate");
	if ( pConvertedName != NULL ) {
		printf("\nConverted Name is : [%s]", pConvertedName);
		//free(pConvertedName);
		IF_FREE_PTR(pConvertedName);
		pConvertedName = NULL;
	}
	long long currentTime = GetEpochTime();
	printf("\nCurrent Time is : [%lld]\n", currentTime);
	RandomNumberGenerator();
//	char**	pNewArray = NULL;
//	//pNewArray = new char*[3];
//	pNewArray = (char**)new int[3];
//	for ( int i = 0; i< 3 ; i++ )
//	{
//		pNewArray[i] = new char[4];
//
//		for(int j=0; j<4; j++)
//		{
//			pNewArray[i][j] = (char)i+j;
//		}
//
//	}
	return 0;
}
void RandomNumberGenerator(void) {
	std::tr1::mt19937 eng;
	eng.seed(time(NULL));
	std::cout<<"Uniform distri"<<endl;
	std::tr1::uniform_int<int> unif(1, 15);
	for (int i = 0; i < 5; ++i) {
		int ans = unif(eng);
		std::cout<<"Random[" <<ans<<"] ["<<(float)ans/RAND_MAX<<"]"<<std::endl;
	}
	std::cout<<"Normal distri"<<endl;
	std::tr1::normal_distribution<double> dist;
	for (int i = 0; i < 10; ++i)
		std::cout << "Normal Distri["<< dist(eng) <<"]"<< std::endl;
}
static char* GetTableName(const char* pManifestId) {
	printf("\nGetTableName::Enter");
	int length = 0;
	char* 	pDest = NULL;
	if ( pManifestId == NULL )
		return NULL;
	length = strlen(pManifestId);
	if( length == 0 )
		return NULL;
	printf("\nGetTableName::String length [%d]", length );
	pDest = (char*) malloc((sizeof(char) * length+1));
	memset(pDest, 0 , (sizeof(char) * length+1));
	strcpy(pDest, pManifestId);
	printf("\nGetTableName::Original Source String[%s]", pDest);
	for ( int i = 0; i < length ; i++) {
		if ( pDest[i] =='.' ) {
			pDest[i] = '_';
		}
	}
	printf("\nGetTableName::Exit [%s]", pDest);
	return pDest;
}
long int
GetEpochTime() {
	printf("\nGetEpochTime::Enter");
	time_t timer;
	struct tm startTime;
	double seconds;
	long int myTime  =0;
	startTime.tm_hour = 0;
	startTime.tm_min = 0;
	startTime.tm_sec = 0;
	startTime.tm_year = 70;
	startTime.tm_mon = 0;
	startTime.tm_mday = 1;
	time(&timer);  /* get current time; same as: timer = time(NULL)  */
	seconds = difftime(timer,mktime(&startTime));
	printf ("\n[%lld] [%.f] seconds since January 1, 2000 in the current timezone", timer, seconds);
	printf("\nGetEpochTime::Exit [%.f]", seconds);
	myTime = static_cast<long int> (time(NULL));
	printf("\MyEpoch Time with time(NULL): [%lld]", myTime*1000);
	return (long int)seconds;
}
char* GetWhereQuery(const char* const pCompeteQuery) {
	int length = 0;
	std::string str ("DELETE FROM CURRENT_TABLE_NAME where WHERE_QUERY");
	length = str.length();
	std::string str2 ("where");
	// different member versions of find in the same order as above:
	std::size_t found = str.find(str2);
	if (found!=std::string::npos)
		std::cout << "'where' found at: " << found << '\n';
	// let's replace the first needle:
	std::string str3 = str.substr (found+ str2.length() ,length - found );   // "generalities"
	printf("\nWhere Query::Exit [%s]", str3.c_str());
	return NULL;
}
void PrintTestResult (std::string testName) {
	FILE* fp_w = NULL;
	std::string success =":SUCCESS";
	std::string failure =":FAIL";
	fp_w = fopen(FILE_PATH, "a");
	if ( fp_w != NULL ) {
		fwrite(testName.c_str(), sizeof(char), testName.length(), fp_w);
		fwrite(success.c_str(), sizeof(char), success.length(), fp_w);
		fwrite("\r", sizeof(char), 2, fp_w);
		fclose(fp_w);
	}
}
void multimapTest() {
	
	std::multimap<char,int> mymm;
	mymm.insert (std::make_pair('x',10));
	mymm.insert (std::make_pair('y',20));
	mymm.insert (std::make_pair('z',30));
	mymm.insert (std::make_pair('z',40));
	
	// test inserttion to multimap
	mymm.insert (std::make_pair('z',555));
	mymm.insert (std::make_pair('z',606));
	mymm.insert (std::make_pair('z',407));
	mymm.insert (std::make_pair('z',707));
	
	// Other data between inserttion to multimap
	mymm.insert (std::make_pair('U',10));
	mymm.insert (std::make_pair('W',20));
	mymm.insert (std::make_pair('S',30));
	mymm.insert (std::make_pair('T',40));
	
	mymm.insert (std::make_pair('Z',10));
	mymm.insert (std::make_pair('Z',20));
	mymm.insert (std::make_pair('Z',30));
	mymm.insert (std::make_pair('Z',40));
	
	//More duplicate sets
	mymm.insert (std::make_pair('z',-1));
	mymm.insert (std::make_pair('z',-10));
	mymm.insert (std::make_pair('z',-60));
	mymm.insert (std::make_pair('z',-70));
	
	std::multimap<char,int>::iterator it = mymm.find('z');
	for (; it != mymm.end() ; it++) {
		std::cout<<"Multimap X: ["<<it->second<<"]"<<endl;
	}
	// print content:
	std::cout << "elements in mymm:" << '\n';
	std::cout << "y => " << mymm.find('y')->second << '\n';
	std::cout << "z => " << mymm.find('x')->second << '\n';
	return ;
}

