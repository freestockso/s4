#include "tdx/tdx_local.h"
#include "common/s4conf.h"

CREATE_LOCAL_LOGGER("test_tdx_local")

using namespace S4;

int main(int argc, char** argv)
{
	glb_conf::pInstance()->load("../json_template/glb_conf_t.json");
	s4logger::pInstance()->init((void*)glb_conf::pInstance()->pLogger());

	TDX::tdxLocal_t tdxLocal(glb_conf::pInstance()->tdx().root);

	vec_dayK_t dayK;

	int bgn = 20160000;
	int end = 20200614;
	tdxLocal.readDayK("000997", dayK, bgn, end);

	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 0;
	end = 20200614;
	tdxLocal.readDayK("000997", dayK, bgn, end);

	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 0;
	end = 20200613;
	tdxLocal.readDayK("000997", dayK, bgn, end);

	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());

	bgn = 20200613;
	end = 20200614;
	tdxLocal.readDayK("000997", dayK, bgn, end);

	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());


	bgn = 20200613;
	end = 99999999;
	tdxLocal.readDayK("000997", dayK, bgn, end);

	LCL_INFO("{:} - {:} : {:} - {:} = {:}", bgn, end, dayK.begin()->date, dayK.rbegin()->date, dayK.size());



}