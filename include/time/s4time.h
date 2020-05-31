#pragma once

#include "types/s4type_time.h"
#include <string>


uint64_t nowTime_ms(void);

//HHMMSS
time_minuSec_t nowMinuSec(void);

//return YYYYmmDD; & if minuSec!=nullptr: *minuSec=HHMMSS;
time_date_t utc_to_date(time_utcSec_t t, time_minuSec_t* minuSec = nullptr);

//%Y_%m_%d__%H_%M_%S
std::string utc_to_str(time_utcSec_t utc);

//date:YYYYMMDD  minuSec=HHMMSS
time_utcSec_t date_to_utc(time_date_t date, time_minuSec_t minuSec = 0);

//mdate="2010-11-30"  mtime="11:30:45"
void str_to_tm(char *mdate, char *mtime, struct tm* mtm);

//utcdiff=-8 for Asia/Shanghai; but we set to 0 during whole program
time_utcSec_t tm_to_utc(const struct tm *ltm, int utcdiff=0); 



class rptTime {
public:
	rptTime();
	explicit rptTime(const std::string& target);
	rptTime(const std::string& target, double rptGate);

	~rptTime();

	void estimate(size_t i, size_t i_max, size_t gap=10);
private:
	const std::string m_target;
	timeb tb;
    double _rptGate;
};

