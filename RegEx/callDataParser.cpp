// regex_search example
#include <iostream>
#include <string>
#include <regex>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <stdlib.h>

#define SUPORTED_OPERATORS 5

using namespace std;
using namespace std::regex_constants;

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}


enum ParsingCategory{
	CALL_COST=0,
	CALL_DURATION,
	REM_BALANCE,
	INVALID
};

int GetSeconds(std::string strDuration){

	cout << strDuration.c_str() << endl;
	std::smatch m;
	std::regex durSeconds("[0-9]+");

	std::regex_search ( strDuration, m, durSeconds);
	for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
		std::cout << *it ;
	}
	return 0;
}

void CallDataParser(std::string inputString, ParsingCategory parseCategory){
	std::smatch m;
	std::regex cost("(?:.?cost.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)|(?:.?chrg.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)", ECMAScript | icase);
	std::regex duration("(?:.?dur.*(?:(?:(?:.)?[0-9]+(?:.)?:(?:.)?[0-9]+(?:.)?)|(?:(?:.)?[0-9]+(?:.)?(?:se(?:c|cond|conds|cs)|mi(?:ns|nutes)|h(?:our||hr)))))", ECMAScript|icase);
	std::regex balance(".?bal.*(?:Rs)?.*[0-9]+\\.[0-9]{0,5}(?:inr|INR|.{0,1})?", ECMAScript | icase);
	std::cout << "Target sequence: " << inputString << std::endl;
	std::regex durValRegex("(?:[0-9](?::)?(?::| )*)+");
	std::regex CostAndBalValRegEx("[0-9]+(?:\\.[0-9]+|\\.)");
	std::regex durUnitRegEx("sec|min|hours|hr", ECMAScript|icase);

	int matchCount = 0;
	cout << "Match begins" << endl;

	switch(parseCategory){
		case CALL_COST:{
		case REM_BALANCE:{
				std::regex_search ( inputString, m, (parseCategory==CALL_COST ?  cost : balance));
				std::cout << "Matches: [ ";
				for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
					std::cout << *it << "]";

					std::string numSearch = *it;

					std::smatch numMatches;
					cout << "Digits:[";
					std::regex_search ( numSearch, numMatches, CostAndBalValRegEx );
					for (std::smatch::iterator ite= numMatches.begin(); ite!=numMatches.end(); ++ite) {
						std::cout << *ite <<"]";
					}
				}
			}
		}
		break;
		case CALL_DURATION:{
			std::regex_search ( inputString, m, duration );
			std::cout << "Matches:[" ; 
		  	for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
				std::cout << *it << "]" ;

				std::string numSearch = *it;

				std::smatch numMatches;
				cout << "Digit:[";
				std::regex_search ( numSearch, numMatches, durValRegex );
				for (std::smatch::iterator ite= numMatches.begin(); ite!=numMatches.end(); ++ite) {
					std::cout << *ite << "]";
					
					GetSeconds(*ite);

					std::string unitSearch = *ite;

					std::smatch unitMatch;
					cout << "Unit:[ ";
					std::regex_search ( numSearch, unitMatch, durUnitRegEx );
					for (std::smatch::iterator iteU= unitMatch.begin(); iteU!=unitMatch.end(); ++iteU) {
						std::cout << *iteU << "]";
					}
		  		}
		  	}
		}
		break;
		default:{

		}
	}
  	cout << "]" << endl;
}

void TestParse(std::string inputString, const std::regex& e){
	std::smatch m;
	//std::regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"
	std::regex cost("(.?chrg).*([0-9])|(.?call.*cost).*([0-9])|(.?dur.*).*([0-9])|(.?bal.*).*([0-9])", ECMAScript | icase);
	std::regex duration("(.?dur.*(?:(?:[0-9]+:[0-9]+)|(?:[0-9]+(?:.)?(?:se(?:c|cond|conds|cs)|mi(?:ns|nutes)|h(?:our||hr)))))", ECMAScript | icase);
	std::regex balance(".?bal.*(?:Rs)?.*[0-9]+\\.[0-9]{0,5}(?:inr|INR|.{0,1})?", ECMAScript | icase);
	std::cout << "Target sequence: " << inputString << std::endl;

	int matchCount = 0;
	cout << "Match begins" << endl;
	std::string roiString;
	while (std::regex_search(inputString, m, balance)) {
		for (auto x : m){
			if (x.length() > 0){
				cout << "**********Meta Data:[" << matchCount << "] *********" << endl;
				cout << "Pos: " << m.position() << endl;
				cout << "Size: " << m.size() << endl;
				cout << "Str: " << m.str() << endl;
				cout << "Suffix: " << m.suffix() << endl;
				cout << "Len: " << m.length() << endl;
				cout << "*****************************" << endl;
				if (matchCount == 0){
					roiString = x;
					matchCount++;
					break;
				}
			}
		}
		std::cout << std::endl;;
		inputString = m.suffix().str();
	}
	cout << "Match ends" << endl;
}

int main (int argc, char* argv[])
{
	
	std::string operatorString[SUPORTED_OPERATORS] = { "Callcost:Rs.0.20 Duration:00:00:08  Bal:Rs.157.31 Govt. mandates to link your Aadhar with mobile number. Visit Retailer",
									"CallCost:Rs.0.04 Duration:00:00:02 Bal:Rs.82.29 Now share your 3G/4G pack with loved ones-SMS ADD <10 Digit Mob No> to 121",
									"CHRG:0.300INR,DURN:003Sec,BAL-LEFT:31.746INR..RC24-1p/sec Local/STD for 28 days",
									"Your last call cost Rs.0.400, call duration 0:0:4, Main A / C balance Rs.194.485 ** For web SELFCARE please visit www.bsnlszprepaid.com **",
									"CallCostRs0.8 BallRs16.83 Duration3sec Spl 23: Local Calls at 25p / min for 28 days"
									};
	for (int i = 0; i < SUPORTED_OPERATORS; i++){
		//TestParse(operatorString[i], e);
		int argument = atoi(argv[1]);
		if ( argument <=0 || argument > 2){ argument = 0; }

		CallDataParser(operatorString[i], (ParsingCategory) argument);
	}
	
	return 0;
}
