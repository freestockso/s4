#include "common/s4logger.h"
#include "db_sqlite/tableIO_dayK.h"
//#include "../logger/s3logger.h"
// time_t time;     datetime
// float open;      double
// float high;      double
// float low;       double
// float close;     double
// float amount;    double   
// uint32_t volume; integer
// datetime         text

#include <SQLiteCpp/ExecuteMany.h>


namespace S4 {
namespace sqlite {


static const std::string K_COL(
    "( "
        "date INTEGER, "
        "open INTEGER, "
        "high INTEGER, "
        "low INTEGER, "
        "close INTEGER, "
        "amount DOUBLE, "
        "volume INTEGER, "
        //"preCls INTEGER, "
        "PRIMARY KEY(date)"
    ")");
static const std::string K_IN(
    "("
        "date, "
        "open, "
        "high, "
        "low, "
        "close, "
        "amount, "
        "volume "
		//"preCls"
    ") VALUES (?,?,?,?,?,?,?)"
);

dbTbl_dayK_t::dbTbl_dayK_t(const std::string name):
		m_name(name+"_day"),
        m_qurey_build("CREATE TABLE if not exists " + m_name + K_COL),
        m_qurey_insert("INSERT OR IGNORE INTO " + m_name + K_IN)
    {};

void  dbTbl_dayK_t::set_name(const std::string& name) {
	m_name = name + "_day";
	m_qurey_build = "CREATE TABLE if not exists " + m_name + K_COL;
	m_qurey_insert = "INSERT OR IGNORE INTO " + m_name + K_IN;
}

void dbTbl_dayK_t::bind_query(SQLite::Statement& query, const std::vector<struct dayK_t>& data, size_t nb)
{
    //if(m_Kque==NULL){
    //    SQLite::bind(query, 0, 0, 0, 0, 0, 0, 0);

    //    INFO("dbTbl_dayK_t::bind_query now source to make DB data, set all 0!");
    //    return;
    //}
    const struct dayK_t & K_data = data[nb];
    // query.bind(1, 2);
    SQLite::bind(query, K_data.date, K_data.open, K_data.high, K_data.low, K_data.close, K_data.amount, K_data.volume);
	//query.bind(1, K_data.time);
	//query.bind(2, K_data.open);
	//query.bind(3, K_data.high);
	//query.bind(4, K_data.low);
	//query.bind(5, K_data.close);
	//query.bind(6, K_data.amount);
	//query.bind(7, K_data.volume);
	//query.bind(8, UTC_to_str(&K_data.time));


}

void dbTbl_dayK_t::load_query(SQLite::Statement& query, std::vector<dayK_t>& data)
{
    //if(m_Kque==NULL){
    //    INFO("dbTbl_dayK_t::load_query now target to load DB data!");
    //    return;
    //}

    struct dayK_t K_data;
    K_data.date   = query.getColumn(0).getInt();
    K_data.open   = query.getColumn(1).getInt();
    K_data.high   = query.getColumn(2).getInt();
	K_data.low    = query.getColumn(3).getInt();
    K_data.close  = query.getColumn(4).getInt();
    K_data.amount = (float)query.getColumn(5).getDouble();
    K_data.volume = query.getColumn(6).getInt();

    data.push_back(std::move(K_data));

}

}
}