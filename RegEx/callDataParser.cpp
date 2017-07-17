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

void PrintCallData(CallData cdp ){
	dlog_print(DLOG_ERROR, LOG_TAG, "**********CallData *********");
	dlog_print(DLOG_ERROR, LOG_TAG, "Call Cost :[%f]", cdp.mCost);
	dlog_print(DLOG_ERROR, LOG_TAG, "Call Duration :[%f]",cdp.mCallDuration);
	dlog_print(DLOG_ERROR, LOG_TAG, "Remaining Balance :[%f]",cdp.mBal);
}

void PrintMatchInfo(const std::smatch& matchInfo, int matchCount ){
	dlog_print(DLOG_ERROR, LOG_TAG, "**********Match Group:[%d]*********", matchCount/4 );
	dlog_print(DLOG_ERROR, LOG_TAG, "Position:[%d]", matchInfo.position());
	dlog_print(DLOG_ERROR, LOG_TAG, "Size:[%d]",matchInfo.size());
	dlog_print(DLOG_ERROR, LOG_TAG, "Str:[%s]",matchInfo.str().c_str());
	dlog_print(DLOG_ERROR, LOG_TAG, "Suffix:[%s]",matchInfo.suffix());
	dlog_print(DLOG_ERROR, LOG_TAG,"Len:[%d]",matchInfo.length());
}

enum ParsingCategory{
	CALL_COST=0,
	CALL_DURATION,
	REM_BALANCE,
	INVALID
};

int GetSeconds(std::string strDuration){

	std::smatch m;
	std::regex durSecondsRegEx("([0-9]+)(?:(?::)?([0-9]+)(?::)?([0-9]+))?");

	int durationValue=0;
	int value  =0;
	std::regex_search ( strDuration, m, durSecondsRegEx);
	for (int matchIndex = m.size(); matchIndex>=1; matchIndex--) {
		std::string seconds = m[matchIndex];
		ltrim(seconds);

		value = std::atoi(seconds.c_str());

		if( matchIndex == 3 && seconds.length()>0 ){
			durationValue += value;
		} else if( matchIndex == 2 && seconds.length()>0){
			durationValue += (value*60);
		} else if( matchIndex == 1 && seconds.length()>0){
			durationValue += ((value*60)*60);
		}
	}

	return durationValue;
}

void CallDataParser(std::string inputString){
	std::smatch m;
	std::regex cost("(?:.?cost.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)|(?:.?chrg.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)", ECMAScript | icase);
	std::regex duration("(?:.?dur.*(?:(?:(?:.)?[0-9]+(?:.)?:(?:.)?[0-9]+(?:.)?)|(?:(?:.)?[0-9]+(?:.)?(?:se(?:c|cond|conds|cs)|mi(?:n|ns|nutes)|h(?:r|rs|our||hr)))))", ECMAScript|icase);
	std::regex balance(".?bal.*(?:Rs)?.*[0-9]+\\.[0-9]{0,5}(?:inr|INR|.{0,1})?", ECMAScript | icase);
	dlog_print(DLOG_DEBUG, LOG_TAG,"Target sequence:[%s]", inputString.c_str());
	std::regex durValRegex("(?:[0-9](?::)?(?::| )*)+");
	std::regex CostAndBalValRegEx("[0-9]+(?:\\.[0-9]+|\\.)");
	std::regex durUnitRegEx("(seconds|secs|sec|s)|(minutes|mins|min|m)|(hours|hour|hrs|hr|h)", ECMAScript|icase);

	CallData callDataPtr;

	//Call Cost
	std::regex_search ( inputString, m, cost );
	//dlog_print(DLOG_DEBUG, LOG_TAG,"Matches:");
	for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
		std::string numSearch = *it;

		std::smatch numMatches;
		std::regex_search ( numSearch, numMatches, CostAndBalValRegEx );
		for (std::smatch::iterator ite= numMatches.begin(); ite!=numMatches.end(); ++ite) {
			std::string num = *ite;
			double parsedNumber = std::atof(num.c_str());
			callDataPtr.mCost = parsedNumber;
		}
	}

	//Call Cost
	std::regex_search ( inputString, m, balance );
	//dlog_print(DLOG_DEBUG, LOG_TAG,"Matches:");
	for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
		std::string numSearch = *it;

		std::smatch numMatches;
		std::regex_search ( numSearch, numMatches, CostAndBalValRegEx );
		for (std::smatch::iterator ite= numMatches.begin(); ite!=numMatches.end(); ++ite) {
			std::string num = *ite;
			double parsedNumber = std::atof(num.c_str());
			callDataPtr.mBal = parsedNumber;
		}
	}
	std::regex_search ( inputString, m, duration );
	//dlog_print(DLOG_DEBUG, LOG_TAG,"Matches: ");
	for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
		std::string numSearch = *it;

		std::smatch numMatches;
		std::regex_search ( numSearch, numMatches, durValRegex );
		for (std::smatch::iterator ite= numMatches.begin(); ite!=numMatches.end(); ++ite) {
			std::string unitSearch = *ite;

			double parsedNumber = std::atof(unitSearch.c_str());

			std::smatch unitMatch;
			std::regex_search ( numSearch, unitMatch, durUnitRegEx );

			std::string num;
			int unitIndex = -1;
			for (int matchIndex = 1 ; matchIndex<unitMatch.size(); matchIndex++) {
				std::string temp =unitMatch[matchIndex];
				if( temp.length() >0 ){
					unitIndex = matchIndex;
					num = temp;
				}
			}
			int durationInSeconds =0;
			if  ( unitMatch.size() <=0 ){
				durationInSeconds  = GetSeconds(*ite);
			} else {
				if( unitIndex == 1 ){
					durationInSeconds = parsedNumber;
				} else if ( unitIndex == 2 ){
					durationInSeconds = parsedNumber * 60;

				} else if ( unitIndex == 3 ){
					durationInSeconds = (parsedNumber * (60*60));
				}
			}
			callDataPtr.mCallDuration  = durationInSeconds;
		}
	}
	PrintCallData(callDataPtr);
}

int main (int argc, char* argv[])
{
	
	std::string operatorString[SUPORTED_OPERATORS] = { "Callcost:Rs.0.20 Duration:00:00:08  Bal:Rs.157.31 Govt. mandates to link your Aadhar with mobile number. Visit Retailer",
											"CallCost:Rs.0.04 Duration:00:00:02 Bal:Rs.82.29 Now share your 3G/4G pack with loved ones-SMS ADD <10 Digit Mob No> to 121",
											"CHRG:0.300INR,DURN:003Sec,BAL-LEFT:31.746INR..RC24-1p/sec Local/STD for 28 days",
											"Your last call cost Rs.0.400, call duration 0:0:4, Main A / C balance Rs.194.485 ** For web SELFCARE please visit www.bsnlszprepaid.com **",
											"CallCostRs0.8 BallRs16.83 Duration3sec Spl 23: Local Calls at 25p / min for 28 days",
											"SMS cost:1.50 Bal:Rs.151.91 Cricket, NEWS,Contest,Call 56789.Get latest songs, dial 578785",
											};
	for (int i = 0; i < SUPORTED_OPERATORS; i++){
		CallDataParser(operatorString[i] );
	}
	
	return 0;
}
