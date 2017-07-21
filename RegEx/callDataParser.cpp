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
/*
07-20 18:44:19.363 : ERROR / prepaidtracker ( 8620 : 8620 ) : Target sequence:[CHRG:0.300INR,DURN:003Sec,BAL-LEFT:31.746INR..RC24-1p/sec Local/STD for 28 days]
You last Data usage 971Kb 53bytes.Remaining Balance 2Gb 294Mb 652Kb 144 bytes.Remaining Balance 2Gb 594Mb 652Kb 144bytes in STV333.Call Cost 0.000. Main Bal Rs. 5.365
"Callcost:Rs.0.20 Duration:00:00:08  Bal:Rs.157.31 Govt. mandates to link your Aadhar with mobile number. Visit Retailer",
"CallCost:Rs.0.04 Duration:00:00:02 Bal:Rs.82.29 Now share your 3G/4G pack with loved ones-SMS ADD <10 Digit Mob No> to 121",
"CHRG:0.300INR,DURN:003Sec,BAL-LEFT:31.746INR..RC24-1p/sec Local/STD for 28 days",
"Your last call cost Rs.0.400, call duration 0:0:4, Main A / C balance Rs.194.485 ** For web SELFCARE please visit www.bsnlszprepaid.com **",
"CallCostRs0.8 BallRs16.83 Duration3sec Spl 23: Local Calls at 25p / min for 28 days
"SMS cost:1.50 Bal:Rs.151.91 Cricket, NEWS,Contest,Call 56789.
Get latest songs, dial 578785"
SMS cost:1.50 Bal:Rs.151.91 Cricket, NEWS,Contest,Call 56789.Get latest songs, dial 578785
"You last Data usage 994Kb 830bytes.Remaining Balance 2Gb 593Mb 681Kb 338bytes in STV333.Call Cost 0.000. Main Bal Rs. 1.915
DataUsage:0.16MB;Cost:Rs.0.68;RemBal:Rs.140.27 
Win car,Dial *646*1#
Data Usage Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#
Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#
Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#
Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#
You last call cost Rs.0.380, call duration 0:0:0 Main A/C Balance is 12.90 ***BSNL data recharge option usage balance call cost***
My Data balance is 2GB, main bal is 12.989
Balance.Rs.9.90
Bal Rs 9.9
Balance:Rs:909
Balance is 12.90
You last call cost Rs.0.380, call duration 0:0:0 Main A/C Balance is 12.90 ***BSNL data recharge option usage balance call cost***
You last call cost Rs.0.380, call duration 0:0:0 Main A/C Balance Rs.33.215 ***For BSNL CALLER TUNES DIAL 56700 (TOLL FREE)***

*/


#include "prepaidtracker.h"
#include "MainController.h"
#include "SingletoneManager.h"
#include "LogUtil.h"
#include "CommonUtil.h"
#include "StringUtil.h"

#include <string>
#include <regex>
#include <algorithm>
#include <cctype>
#include <locale>
#include <stdlib.h>
#include <cstdlib>


std::string mLastDialedNumber = "";

std::string sanitizeRegexString(std::string& s){
	//dlog_print(DLOG_ERROR, LOG_TAG, "Before Sanitizing:[%s]", s.c_str());
	std::replace( s.begin(), s.end(), '\n', ' '); // replace all 'x' to 'y'
	//dlog_print(DLOG_ERROR, LOG_TAG, "After Sanitizing:[%s]", s.c_str());
}


class CallData{
private:
	std::string mNumber;
	double mCallDuration;
	long long int createTime;		//epoch time of the call log
	std::string mCostUnit;
	double mCost;
	double mBal;
	std::string mType;
	//CallStatus mCallStatus;
public:
	void SetType(std::string t){
		mType  = t;
	}

	std::string GetType(){
		return mType;
	}
	void SetNumber(const std::string& number){
		mNumber = number;
	}

	void SetCostUnit(const std::string& costUnit){
		mCostUnit = costUnit;
	}

	void SetCallCost(double cost){
		mCost = cost;
	}

	void SetCallDuration(double callDuration){
		mCallDuration = callDuration;
	}

	double GetCallDuration(){
		return mCallDuration;
	}

	double GetCallCost(){
		return mCost;
	}

	std::string GetCallNumber(){
		return mNumber;
	}

	double GetBalance(){
		return mBal;
	}
	void SetBalance(double cost){
		mBal = cost;
	}

	void SetCreateTime(long long int time){
		createTime = time;
	}

	long long int GetCreateTime(void){
		return createTime;
	}
};

typedef CallData* CallDataPtr;


static bool gIsLaunched = false;
#define SUPORTED_OPERATORS 19

using namespace std;
using namespace std::regex_constants;

// trim from start (in place)
static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

void PrintCallData(CallDataPtr cdp ){
	dlog_print(DLOG_ERROR, LOG_TAG, "**********CallData *********");
	dlog_print(DLOG_ERROR, LOG_TAG, "Call Cost :[%s]", cdp->GetType().c_str());
	dlog_print(DLOG_ERROR, LOG_TAG, "Call Cost :[%f]", cdp->GetCallCost());
	dlog_print(DLOG_ERROR, LOG_TAG, "Call Duration :[%f]",cdp->GetCallDuration());
	dlog_print(DLOG_ERROR, LOG_TAG, "Remaining Balance :[%f]",cdp->GetBalance());
}

void PrintMatchInfo(const std::smatch& matchInfo ){


	dlog_print(DLOG_ERROR, LOG_TAG, "**********Match Group*********");
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

int ToSeconds(std::string strDuration){

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
	/*std::regex cost("(?:.?cost.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)|(?:.?chrg.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)", ECMAScript | icase);
	std::regex duration("(?:.?dur.*(?:(?:(?:.)?[0-9]+(?:.)?:(?:.)?[0-9]+(?:.)?)|(?:(?:.)?[0-9]+(?:.)?(?:se(?:c|cond|conds|cs)|mi(?:n|ns|nutes)|h(?:r|rs|our||hr)))))", ECMAScript|icase);
	std::regex balance(".?bal.*(?:Rs)?.*[0-9]+\\.[0-9]{0,5}(?:inr|INR|.{0,1})?", ECMAScript | icase);
	dlog_print(DLOG_DEBUG, LOG_TAG,"Target sequence:[%s]", inputString.c_str());
	std::regex durValRegex("(?:[0-9](?::)?(?::| )*)+");
	std::regex CostAndBalValRegEx("[0-9]+(?:\\.[0-9]+|\\.)");
	std::regex durUnitRegEx("(seconds|secs|sec|s)|(minutes|mins|min|m)|(hours|hour|hrs|hr|h)", ECMAScript|icase);

	std::regex smsType("^(?:(?!(?:.?duration|durn|dur|usage.?)).)*$", ECMAScript | icase );
	std::regex dataType("^(?:(?!(?:.?duration|durn|dur.?)).(.*usage.*))*$", ECMAScript | icase);*/

	std::regex cost("(?:.?cost.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)|(?:.?chrg.?(?:Rs.|Rs|:|\\.)?[0-9]+(?:\\.[0-9]+)?)", ECMAScript | icase);
	std::regex duration("(?:.?dur.*(?:(?:(?:.)?[0-9]+(?:.)?:(?:.)?[0-9]+(?:.)?)|(?:(?:.)?[0-9]+(?:.)?(?:se(?:c|cond|conds|cs)|mi(?:n|ns|nutes)|h(?:r|rs|our||hr)))))", ECMAScript|icase);
	//std::regex balance(".?bal.*(?:Rs)?.*[0-9]+\\.[0-9]{0,5}(?:inr|INR|.{0,1})?", ECMAScript | icase);
	std::regex balance("bal(?:l|ance|-left|-remaining|ance-left|ance-remaining|ance-rem|ance |ance)?(?: |\\.|-|:)?(?:Rs)?(?:\\. |\\.:|\\.|:|  | |-)?[0-9]+\\.[0-9]+", ECMAScript | icase);
	dlog_print(DLOG_ERROR, LOG_TAG,"Target sequence:[%s]", inputString.c_str());
	//sanitizeRegexString(inputString);


	std::regex durValRegex("(?:[0-9](?::)?(?::| )*)+");
	std::regex CostAndBalValRegEx("[0-9]+(?:\\.[0-9]+|\\.)");
	std::regex durUnitRegEx("(seconds|secs|sec|s)|(minutes|mins|min|m)|(hours|hour|hrs|hr|h)", ECMAScript|icase);

	std::regex smsType("^(?:(?!(?:.?duration|durn|dur|usage.?)).)*$", ECMAScript | icase  );
	std::regex dataType("^(?!.*(duration|durn|dur)).*usage.*$", ECMAScript | icase);

	CallDataPtr callDataPtr = NULL;
	callDataPtr = new CallData();
	callDataPtr->SetCreateTime(std::time(NULL));


	if( mLastDialedNumber.empty()){
		std::regex_search ( inputString, m, dataType );
		PrintMatchInfo(m);
		if ( m.size() > 0 ){
			//std::regex balance("bal(?:l|ance|-left|-remaining|ance-left|ance-remaining|ance-rem|ance |ance)?(?: |\\.|-|:)?(?:Rs)?(?:\\. |\\.:|\\.|:|  | |-)?[0-9]+\\.[0-9]+", ECMAScript | icase);
			//std::regex CostAndBalValRegEx("[0-9]+(?:\\.[0-9]+|\\.)");
			dlog_print(DLOG_ERROR, LOG_TAG," DataType Detected and Hence returning :[%s]", inputString.c_str());

			callDataPtr->SetType("data");
			callDataPtr->SetCallCost(0);
			callDataPtr->SetCallDuration(0);
			callDataPtr->SetBalance(0);
			return ;
		}
		std::regex_search ( inputString, m, smsType);
		PrintMatchInfo(m);
		if ( m.size() > 0 ){
			callDataPtr->SetType("sms");
		} else {
			callDataPtr->SetType("call");
		}
	}

	//Call Cost
	std::regex_search ( inputString, m, cost );
	if ( m.size() <=0 ){
		callDataPtr->SetCallCost(0);
	} else {
		for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
			std::string numSearch = *it;

			std::smatch numMatches;
			std::regex_search ( numSearch, numMatches, CostAndBalValRegEx );
			if ( numMatches.size() <=0 ){
				callDataPtr->SetCallCost(0);
			} else {
				for (std::smatch::iterator ite= numMatches.begin(); ite!=numMatches.end(); ++ite) {
					std::string num = *ite;
					double parsedNumber = std::atof(num.c_str());
					callDataPtr->SetCallCost(parsedNumber);
				}
			}
		}
	}

	//Balance
	std::regex_search ( inputString, m, balance );
	if ( m.size() <=0 ){
		callDataPtr->SetBalance(0);
	} else {
		for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
			std::string numSearch = *it;

			std::smatch numMatches;
			std::regex_search ( numSearch, numMatches, CostAndBalValRegEx );
			if ( numMatches.size() <=0 ){
				callDataPtr->SetBalance(0);
			} else {
				for (std::smatch::iterator ite= numMatches.begin(); ite!=numMatches.end(); ++ite) {
					std::string num = *ite;
					double parsedNumber = std::atof(num.c_str());
					callDataPtr->SetBalance(parsedNumber);
					break;
				}
			}
		}
	}

	//Duration Parser
	std::regex_search ( inputString, m, duration );
	dlog_print(DLOG_ERROR, LOG_TAG," Duration MatchSize:[%d]", m.size());
	if ( m.size() == 0 ){
		callDataPtr->SetCallDuration(0);
	} else {
		for (std::smatch::iterator it = m.begin(); it!=m.end(); ++it) {
			std::string numSearch = *it;

			std::smatch numMatches;
			std::regex_search ( numSearch, numMatches, durValRegex );
			if ( numMatches.size() <=0 ){
				callDataPtr->SetCallDuration(0);
			} else {
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
					dlog_print(DLOG_ERROR, LOG_TAG,"******* UnitIndex ********:[%d]", unitIndex);
					int durationInSeconds =0;
					if  ( unitMatch.size() <=0 ){
						durationInSeconds  = ToSeconds(*ite);
					} else {
						if (unitIndex == 1 ){
							durationInSeconds = parsedNumber;
						} else  if ( unitIndex == 2 ){
							durationInSeconds = parsedNumber * 60;

						} else if ( unitIndex == 3 ){
							durationInSeconds = (parsedNumber * (60*60));
						}
					}
					callDataPtr->SetCallDuration(durationInSeconds);
				}
			}
		}
	}
	PrintCallData(callDataPtr);
	delete callDataPtr;
}

int
main ()
{
	FUNC_BEGIN();
	elm_app_base_scale_set(2.6);
	elm_config_preferred_engine_set("opengl_x11");


	/*std::string operatorString[SUPORTED_OPERATORS] = { "Callcost:Rs.0.20 Duration:00:00:08  Bal:Rs.157.31 Govt. mandates to link your Aadhar with mobile number. Visit Retailer",
											"CallCost:Rs.0.04 Duration:00:00:02 Bal:Rs.82.29 Now share your 3G/4G pack with loved ones-SMS ADD <10 Digit Mob No> to 121",
											"CHRG:0.300INR,DURN:003Sec,BAL-LEFT:31.746INR..RC24-1p/sec Local/STD for 28 days",
											"Your last call cost Rs.0.400, call duration 0:0:4, Main A / C balance Rs.194.485 ** For web SELFCARE please visit www.bsnlszprepaid.com **",
											"CallCostRs0.8 BallRs16.83 Duration3sec Spl 23: Local Calls at 25p / min for 28 days",
											"SMS cost:1.50 Bal:Rs.151.91 Cricket, NEWS,Contest, \n Call 56789.Get latest songs, dial 578785",
											"You last Data usage 971Kb 53bytes.Remaining Balance 2Gb 294Mb 652Kb 14 4 bytes"};*/

	std::string operatorString[SUPORTED_OPERATORS] = { "You last Data usage 971Kb 53bytes.Remaining Balance 2Gb 294Mb 652Kb 144 bytes.Remaining Balance 2Gb 594Mb 652Kb 144bytes in STV333.Call Cost 0.000. Main Bal Rs. 5.365",
													"Callcost:Rs.0.20 Duration:00:00:08  Bal:Rs.157.31 Govt. mandates to link your Aadhar with mobile number. Visit Retailer",
													"CallCost:Rs.0.04 Duration:00:00:02 Bal:Rs.82.29 Now share your 3G/4G pack with loved ones-SMS ADD <10 Digit Mob No> to 121",
													"CHRG:0.300INR,DURN:003Sec,BAL-LEFT:31.746INR..RC24-1p/sec Local/STD for 28 days",
													"Your last call cost Rs.0.400, call duration 0:0:4, Main A / C balance Rs.194.485 ** For web SELFCARE please visit www.bsnlszprepaid.com **",
													"CallCostRs0.8 BallRs16.83 Duration3sec Spl 23: Local Calls at 25p / min for 28 days",
													"SMS cost:1.50 Bal:Rs.151.91 Cricket, NEWS,Contest,Call 56789. Get latest songs, dial 578785",
													"SMS cost:1.50 Bal:Rs.151.91 Cricket, NEWS,Contest,Call 56789.Get latest songs, dial 578785",
													"You last Data usage 994Kb 830bytes.Remaining Balance 2Gb 593Mb 681Kb 338bytes in STV333.Call Cost 0.000. Main Bal Rs. 1.915",
													"DataUsage:0.16MB;Cost:Rs.0.68;RemBal:Rs.140.27 Win car,Dial *646*1#",
													"Data Usage Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#",
													"Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#",
													"Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#",
													"Usage:1.71MB; Cost:Rs.7.04; Rem Bal:Rs.133.23 Win car, Dial *646*1#",
													"You last call cost Rs.0.380, call duration 0:0:0 Main A/C Balance is 12.90 ***BSNL data recharge option usage balance call cost***",
													"My Data balance is 2GB, main bal is 12.989",
													"Balance.Rs.9.90",
													"Bal Rs 9.9",
													"Balance:Rs:909",
	};

	for (int i = 0; i < SUPORTED_OPERATORS; i++){
		CallDataParser(operatorString[i] );
	}

	
	return true;
}
