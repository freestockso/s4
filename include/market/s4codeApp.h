#pragma once
#define PRB_MK 999999
#define SH_PRB 170000000
#define SZ_PRB 330000000
#define CY_PRB 330300000
#define CY_PRB_MK 10000


#define CODE_INT_STK_INDEX_SH (170000001)
#define CODE_INT_STK_INDEX_SZ (330399001)
#define CODE_INT_STK_INDEX_CY (330399006)

#define CODE_STR_STK_INDEX_SH ("sh000001")
#define CODE_STR_STK_INDEX_SZ ("sz399001")
#define CODE_STR_STK_INDEX_CY ("sz399006")



#include <string>
/***********************************
 * mktCodeInt  : 320000001, 330000997, 170600004;  map_gbbd_t, map_fhps_t; [ TODO: all s3! ]
 * mktCodeStr  : "sh000001", "sz000997", "sh600004"; (interface)
 * pureCodeInt : 1, 997, 600004;  ??
 * pureCodeStr : "000001", "000997", "600004"; basic (tushare/ol)
 * *********************************/


//"600997" : "sh600997", "000001":"sz000001"
std::string pureCodeStr_to_mktCodeStr(const std::string& pureCode);
//"600997" : 170600997, "000001": 330000001
int pureCodeStr_to_mktCodeInt(const std::string& pureCode);
//600997 : "sh600997", 1:"sz000001"
std::string pureCodeInt_to_mktCodeStr(const int pureCode);
//600997 : 170600997, 1: 330000001
int pureCodeInt_to_mktCodeInt(const int pureCode);

//"sh600997" : "600997", "sz000001":"000001"; [ "sh000001":ERROR ]
std::string mktCodeStr_to_pureCodeStr(const std::string& mktCode);
//"sh600997" : 600997, "sz000001":1; [ "sh000001":ERROR ]
int mktCodeStr_to_pureCodeInt(const std::string& mktCode);
//170600997 : "600997", 330000001: "000001"
std::string mktCodeInt_to_pureCodeStr(const int mktCode);
//170600997 : 600997, 330000001: 1
int mktCodeInt_to_pureCodeInt(const int mktCode);

//"sh600997" : 170600997, "sz000001":330000001; [ "sh000001":170000001 ]
int mktCodeStr_to_mktCodeInt(const std::string& mktCode);

//170600997 : "sh600997", 330000001: "sz000001"
std::string mktCodeInt_to_mktCodeStr(int mktCode);

bool isSZmkt(int MktCodeInt);
bool isSHmkt(int MktCodeInt);
bool isCYmkt(int MktCodeInt);
bool isStk(int MktCodeInt);
bool isIdx(int MktCodeInt);

bool isStk(const std::string & MktCodeStr);

bool pureCodeIsStk(int pureCode);