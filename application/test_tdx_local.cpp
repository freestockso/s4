#include "tdx/tdx_local.h"
#include "common/s4conf.h"
#include <filesystem>

CREATE_LOCAL_LOGGER("test_tdx_local")

using namespace S4;
using namespace std::filesystem;

int main(int argc, char** argv)
{
	glb_conf::pInstance()->load("../json_template/glb_conf_ctx_t.json");
	s4logger::pInstance()->init((void*)glb_conf::pInstance()->pLogger());

	path tdx_root(glb_conf::pInstance()->tdx().root);
	if (!std::filesystem::exists(tdx_root) || !is_directory(tdx_root)) {
		LCL_FATAL("no such folder: {:}", tdx_root.string());
	}
	TDX::tdxLocal_t tdxLocal(tdx_root.string());

	vec_dayK_t dayK;

	int bgn = 20160000;
	int end = 20200614;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 0;
	end = 20200614;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 0;
	end = 20200613;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 20111010;
	end = 20200612;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 20200613;
	end = 20200614;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (dayK.size()) {
		LCL_FATAL("read {:} where is empty scope!");
	}
	else {
		LCL_INFO("{:} - {:} : = {:}", bgn, end, dayK.size());
	}


	bgn = 20200612;
	end = 99999999;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 0;
	end = 20110101;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (dayK.size()) {
		LCL_FATAL("read {:} where is empty scope!");
	}
	else {
		LCL_INFO("{:} - {:} : = {:}", bgn, end, dayK.size());
	}

	bgn = 0;
	end = 20111010;
	tdxLocal.readDayK("sz000997", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());
	LCL_INFO("---------------------------------")

	bgn = 0;
	end = 20200612;
	tdxLocal.readDayK("sh688004", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 20200612;
	end = 20200612;
	tdxLocal.readDayK("sh688004", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 0;
	end = 20200611;
	tdxLocal.readDayK("sh688004", dayK, bgn, end);

	if (dayK.size()) {
		LCL_FATAL("read {:} where is empty scope!");
	}
	else {
		LCL_INFO("{:} - {:} : = {:}", bgn, end, dayK.size());
	}

	bgn = 20200611;
	end = 20200611;
	tdxLocal.readDayK("sh688004", dayK, bgn, end);

	if (dayK.size()) {
		LCL_FATAL("read {:} where is empty scope!");
	}
	else {
		LCL_INFO("{:} - {:} : = {:}", bgn, end, dayK.size());
	}

	bgn = 20200612;
	end = 99999999;
	tdxLocal.readDayK("sh688004", dayK, bgn, end);

	if (!dayK.size()) {
		LCL_FATAL("nothing read from tdx-local!");
	}
	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	LCL_INFO("--------------------------------- done --------------------------------")

}