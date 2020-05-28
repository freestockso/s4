#pragma once

#include "s4json_util.h"
#include "jsonTypes/glb_conf_t.h"

namespace S4{

class glb_conf{
public:
    static bool load(std::string & file_path);

private:
    static glb_conf_t _v;

}

    
} // namespace S4
