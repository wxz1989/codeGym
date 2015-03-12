#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <map>

using namespace std;


void multimapTest();

void main()
{

	multimapTest();
	getchar();
	return;


	string query;
	string tableName("com.samsung.health.heart_rate"), datauuid("1234-abcd-5678");
	__int64 __id = 41312038109;
	
	char rowId[50] = {0};
	string Id;
	sprintf_s(rowId, "%d", __id);
	Id.append(rowId);
	
	string timeStats = "strftime('%s', 'now')";
	string insetStatement = "INSERT INTO deleted_uuid (rowId, datatype, datauuid, deletedtime) VALUES (";
	//query =  insetStatement + Id +  ",'"+ tableName + "','" + datauuid +  "','"  +  timeStats  + "'" ;
	printf("\nquery : %s", insetStatement.c_str());

	getchar();
	return;
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



	// Equal Range Test
	std::cout << "mymm contains:\n";
	for (char ch='x'; ch<='z'; ch++)
		{
		std::pair <std::multimap<char,int>::iterator, std::multimap<char,int>::iterator> ret;
		ret = mymm.equal_range(ch);
		std::cout << ch << " Range=>[";
		for (std::multimap<char,int>::iterator it=ret.first; it!=ret.second; ++it)
			std::cout << ' ' << it->second;
		std::cout <<"]"<< '\n';
		}
	return ;
}
