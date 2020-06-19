#pragma once

#include <string>
#include <stdexcept>

namespace S4{

/// Base QuickFIX exception type.
struct Exception : public std::logic_error
{
	Exception(const std::string& t, const std::string& d)
		: std::logic_error(d.size() ? t + ": " + d : t),
		type(t), detail(d)
	{}
	~Exception() throw() {}

	std::string type;
	std::string detail;
};


/// Unable to convert field into its native format
struct FieldConvertError : public Exception
{
	FieldConvertError(const std::string& what = "")
		: Exception("Could not convert field", what) {}
};
/// 
struct ConfigError : public Exception
{
	ConfigError(const std::string& what = "")
		: Exception("Configure failed", what) {}
};
/// 
struct CodeNameConvertError : public Exception
{
	CodeNameConvertError(const std::string& what = "")
		: Exception("CodeName ERROR:", what) {}
};
/// 
struct InfoError : public Exception
{
	InfoError(const std::string& what = "")
		: Exception("Info ERROR:", what) {}
};
/// 
struct TimerError : public Exception
{
	TimerError(const std::string& what = "")
		: Exception("Timer ERROR:", what) {}
};
/// 
struct ThreadDataIfError : public Exception
{
	ThreadDataIfError(const std::string& what = "")
		: Exception("Thread data IF ERROR:", what) {}
};
/// 
struct StrategyError : public Exception
{
	StrategyError(const std::string& what = "")
		: Exception("Strategy ERROR:", what) {}
};
/// 
struct OrderError : public Exception
{
	OrderError(const std::string& what = "")
		: Exception("Order ERROR:", what) {}
};
/// 
struct QtDataIfError : public Exception
{
	QtDataIfError(const std::string& what = "")
		: Exception("QT dataIF ERROR:", what) {}
};
/// 
struct SqliteDBError : public Exception
{
	SqliteDBError(const std::string& what = "")
		: Exception("Sqlite DB ERROR:", what) {}
};
/// 
struct MoneyPoolError : public Exception
{
	MoneyPoolError(const std::string& what = "")
		: Exception("MoneyPool ERROR:", what) {}
};
/// 
struct EvaError : public Exception
{
	EvaError(const std::string& what = "")
		: Exception("EVALUATE ERROR:", what) {}
};
/// 
struct CycError : public Exception
{
	CycError(const std::string& what = "")
		: Exception("CYC ERROR:", what) {}
};
/// 
struct AppError : public Exception
{
	AppError(const std::string& what = "")
		: Exception("s3app ERROR:", what) {}
};
/// 
struct TdxOlError : public Exception
{
	TdxOlError(const std::string& what = "")
		: Exception("TDX-OL ERROR:", what) {}
};
/// 
struct OTF_Error : public Exception
{
	OTF_Error(const std::string& what = "")
		: Exception("OTF ERROR:", what) {}
};

/// 
struct SNAP_Error : public Exception
{
	SNAP_Error(const std::string& what = "")
		: Exception("SNAP ERROR:", what) {}
};
/// 
struct BANRANK_Error : public Exception
{
	BANRANK_Error(const std::string& what = "")
		: Exception("BanRank ERROR:", what) {}
};
/// 
struct pyTrader_Error : public Exception
{
	pyTrader_Error(const std::string& what = "")
		: Exception("pyTrader ERROR:", what) {}
};

///
struct stg_Error : public Exception
{
	stg_Error(const std::string& what = "")
		: Exception("stg ERROR:", what) {}
};

///
struct type_Error : public Exception
{
	type_Error(const std::string& what = "")
		: Exception("type ERROR:", what) {}
};

/// 
struct consoleError : public Exception
{
	consoleError(const std::string& what = "")
		: Exception("console ERROR:", what) {}
};

///
struct network_Error : public Exception
{
	network_Error(const std::string& what = "")
		: Exception("network ERROR:", what) {}
};


}//S4