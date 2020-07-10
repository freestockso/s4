#pragma once

#include "jsonTypes/glb_conf_ctx_t.h"
#include "common/s4json_util.h"
#include "common/s4thread.h"
#include "common/s4calendar.h"

namespace S4{

class glb_conf : std::enable_shared_from_this<glb_conf>
{
public:
    typedef std::shared_ptr<glb_conf> Ptr;

	bool load(const std::string & file_path) {
		std::shared_ptr<nlohmann::json> pJ = readJsonFile(file_path);
		if (pJ && !pJ->empty()) {
			glb_conf_ctx_t::from_json(*pJ, _v);
		}
		else {
			ERR("glb_conf load({:}) fail!", file_path);
			return false;
		}

		if (_v.tdx.root.size()){
			_tdxCalendar = std::make_shared<tdxCalendar_t>(_v.tdx.root);
		}

		return true;
	}

	static Ptr pInstance(){
		static glb_conf::Ptr _g_pConf;
		if (!_g_pConf) {
			_g_pConf = std::make_shared<glb_conf>();
			INFO("glb_conf::pInstance() init done.");
		}
		
        return _g_pConf;
    }

	inline const glb_conf_ctx_t& v() const {
		return _v;
	}

	inline const glb_conf_ctx_t::network_t& nw() const {
		return _v.network;
	}

	inline const glb_conf_ctx_t::db_t& db() const {
		return _v.db;
	}

	inline const glb_conf_ctx_t::logger_t& logger() const {
		return _v.logger;
	}

	inline const glb_conf_ctx_t::logger_t* pLogger() const {
		return &_v.logger;
	}

	inline const glb_conf_ctx_t::tdx_t& tdx() const {
		return _v.tdx;
	}

	std::shared_ptr<tdxCalendar_t> calendar(){
		return _tdxCalendar;
	}


private:
    glb_conf_ctx_t _v;

    Mutex _mux;

	std::shared_ptr<tdxCalendar_t> _tdxCalendar;

};

    
} // namespace S4
