#pragma once

#include "jsonTypes/glb_conf_t.h"
#include "s4json_util.h"
#include "s4thread.h"

namespace S4{

class glb_conf : std::enable_shared_from_this<glb_conf>
{
public:
    typedef std::shared_ptr<glb_conf> Ptr;

	bool load(const std::string & file_path) {
		std::shared_ptr<nlohmann::json> pJ = readJsonFile(file_path);
		if (pJ && !pJ->empty()) {
			glb_conf_t::from_json(*pJ, _v);
		}
		else {
			ERR("glb_conf load({:}) fail!", file_path);
			return false;
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

	const glb_conf_t& v() const {
		return _v;
	}

	const glb_conf_t::db_t& db() const {
		return _v.db;
	}

	const glb_conf_t::logger_t& logger() const {
		return _v.logger;
	}

	const glb_conf_t::logger_t* pLogger() const {
		return &_v.logger;
	}

	const glb_conf_t::tdx_t& tdx() const {
		return _v.tdx;
	}


private:
    glb_conf_t _v;

    Mutex _mux;

};

    
} // namespace S4
