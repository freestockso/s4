#pragma once

#include <time.h>
#include <stdint.h>
#include <sys/timeb.h>
#include <vector>
#include <string>
#include <map>
#include <list>

#include "s4type_precision.h"
#include "s4type_time.h"
#include "market/s4codeApp.h"	//types of code

// #include "s3type_future.h"

/************************************************************************/
/* WARNING: Vol in DayK/minuK/GBBQ is in Gu(1 share), Vol in Snap is in Shou(1 hand) = 100 Gu!*/
/************************************************************************/
typedef std::vector<struct minuK_t> vec_minuK_t;
struct minuK_t
{
	time_utcSec_t time;	//utcSec
	price_t open;
	price_t high;
	price_t low;
	price_t close;
	amount_t amount;	//yuan
	vol_share_t volume;	//gu (1 share)
};

typedef std::vector<struct dayK_t> vec_dayK_t;
struct dayK_t
{
	time_date_t date;			//YYYYMMDD
	price_t open;
	price_t high;
	price_t low;
	price_t close;
	amount_t amount;		//yuan
	vol_share_t volume;		//gu (1 share)
	price_t preClose;		//nothing inside, but need here for tdx-file-reading
};

struct stk_tdx_quote_t
{
	int mktCode;
	uint16_t active1;			//active1增加1，表示这期间发生过成交。如果没有成交，每次快照给出的时间戳、五档价格和委托量都是可能变动的，但active1不变。如果active1增加1，那么总量，总金额一定会变。
	int price;
	int last_close;
	int open;
	int high;
	int low;
	int reversed_bytes0;
	timeb timeS;
	int reversed_bytes1;		//-价格*100
	int vol;					//总量 手
	int cur_vol;				//现量 手 index?
	amount_t amount;
	int s_vol;
	int b_vol;
	int reversed_bytes2;		//市场
	int reversed_bytes3;
	int bid1;
	int ask1;
	int bid_vol1;
	int ask_vol1;
	int bid2;
	int ask2;
	int bid_vol2;
	int ask_vol2;
	int bid3;
	int ask3;
	int bid_vol3;
	int ask_vol3;
	int bid4;
	int ask4;
	int bid_vol4;
	int ask_vol4;
	int bid5;
	int ask5;
	int bid_vol5;
	int ask_vol5;
	uint16_t reversed_bytes4;
	int reversed_bytes5;
	int reversed_bytes6;
	int reversed_bytes7;
	int reversed_bytes8;
	uint16_t reversed_bytes9;	//涨速
	uint16_t active2;			//活跃度
	time_t lcl_time;

	std::string toString(void) const;
};

typedef std::vector<struct gbbd_t> vec_gbbd_t;
typedef std::vector<struct fhps_t> vec_fhps_t;
struct gbbd_t
{
	//unsigned char isSz;
	uint32_t strDate;
	//unsigned char category; //信息类型:1的为除权除息, 大于1的为股本变动
	float qianliutong;		//前总流通(万股) -> gu
	float qianzong;			//前总股本
	float houliutong;		//后总流通
	float houzong;			//后总股本
};
struct fhps_t
{
	//unsigned char isSz;
	uint32_t strDate;
	//unsigned char category; //信息类型:1的为除权除息, 大于1的为股本变动
	float hongli;		//每10股派几元 -> 1股
	float peigujia;		//配股价		
	float songgu;		//每10股送几股 -> 1股
	float peigu;		//每10股配几股 -> 1股
};


//typedef std::map<int, vec_gbbd_t> map_gbbd_t;
//typedef std::map<int, vec_fhps_t> map_fhps_t;
class map_gbbd_t : public std::map<int, vec_gbbd_t>
{
public:
	const vec_gbbd_t* getStk(const std::string&) const;
	const vec_gbbd_t* getStk(int) const;

};

class map_fhps_t : public std::map<int, vec_fhps_t>
{
public:
	const vec_fhps_t* getStk(const std::string&) const;
	const vec_fhps_t* getStk(int) const;

};


enum runMode_t
{
	rOTF = 0,
	rREG,
	rCap,
};

enum timeMode_t
{
	tDAY = 0,
	tMINU,
	tSnap,
	//tTick,

	tUNKNOWN,
};

enum orderType_t {
	UNKNOW = 0,
	LIMITED_BUY,
	LIMITED_SELL,
	MARKET_BUY,
	MARKET_SELL,
	BUY,
	SELL,
	ANY,
	CANCEL_BUY,
	CANCEL_SELL,
	//MARKET_CLOSE,
	//LIMITED_CLOSE,
};

std::string orderTypeStr(orderType_t t);
orderType_t str2orderType(const std::string & str);

bool isOrderTypeEqual(orderType_t t0, orderType_t t1);

//*:                         AUTO
//BUY:  dbp / RZ_BUY(first n) |   NORMAL_STOCK
//SELL: dbp / RQ_SELL(TODO)   |   NORMAL_STOCK
//CANCEL: RZRQ                |   NORMAL_STOCK
enum tradeType_t
{
	AUTO = 0,
	NORMAL_STOCK,
	DBP,
	RZRQ,
	RZ_BUY,
	RQ_SELL,

};
std::string tradeTypeStr(tradeType_t t);


enum marketType_t
{
	STOCK_AUTO = 0,
	STOCK_RZ,
	STOCK_DBP,
	STOCK_STK
};
std::string marketTypeStr(marketType_t t);
marketType_t str2marketType(const std::string & str);


//humanOrder
struct horder_t
{
	int mktCode;
	int vol;
	int openPrice;
	marketType_t marketType;
	orderType_t orderType;
	std::string source;
	std::string toString(void) const;
};



