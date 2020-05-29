#pragma once

#include "s4json_util.h"
#include "s4thread.h"
#include "jsonTypes/gbl_conf_t.h"

namespace S4{

class glb_conf : std::enable_shared_from_this<glb_conf>
{
public:
    typedef std::shared_ptr<glb_conf> Ptr;

	bool load(std::string & file_path) {
		std::shared_ptr<nlohmann::json> pJ = readJsonFile(file_path);
		if (pJ && !pJ->empty()) {
			gbl_conf_t::from_json(*pJ, _v);
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



private:
    gbl_conf_t _v;

    Mutex _mux;

};

    
} // namespace S4
