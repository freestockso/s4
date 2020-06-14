
#include "data/s4infMA.h"

#include "common/s4logger.h"

namespace S4 {

CREATE_LOCAL_LOGGER("MA")

static
void calcSMA(const infKQ_t* dayK, ma_t* ma, size_t scope, size_t pos);

//TODO
void calcEMA(const infKQ_t* dayK, ma_t* ma, size_t scope, size_t pos);

maQ_t::maQ_t(const infKQ_t & K, int scope, bool doCalc) :	//
	_pK(&K)
{
	if (scope < 3) {
		LCL_WARN("maQ wanted scope=%d, less than min value=8, set to 3!", scope);
		_scope = 3;
	}
	else {
		_scope = scope;
	}

	if (doCalc)
		calc();
}

void maQ_t::calc()
{
	calc(_scope, static_cast<size_t>(-1));
}

void maQ_t::calc(size_t bgnI, size_t endI)
{
	// if (!_pK->isNewAtBack()) {
	// 	throw std::exception("ERROR: Try to calc CYC about a none-NewAtBack dayK!");
	// }
	assert(_pK->isNewAtBack());

	//scope=600, size=1709 :  2s@debug; 1s@release
	//rptTime tick("calc CYC scope="+IntConvertor::convert(_scope)+", size=" + IntConvertor::convert(_pK->size()));

	//time_t lastTime = (*rbegin())->_time;
	size_t i(bgnI);
/*
	if(bgnI<_scope)
		i = _scope;
*/
	if (i > _pK->size())
		return;
			
	this->reserve(_pK->size() - i);
	size_t scope = _scope;
	for (; i < _pK->size() && i < endI; ++i) {
		if (i >= _scope) scope = _scope;
		else scope = i+1;

		std::shared_ptr<ma_t> pMA = std::make_shared<ma_t>();

		calcSMA(_pK, pMA.get(), scope, i);
		emplace_back(pMA);
	}

}


void calcSMA(const infKQ_t* dayK, ma_t* ma, size_t scope, size_t pos)
{
	assert(pos >= scope);

	price_t o=0, c=0, l=0, h=0;
	int64_t v=0;
	amount_t a=0;

	double factor = (*dayK)[pos]->_factor;
	size_t i = pos - scope + 1;
	for (; i <= pos; ++i) {//从最早向近日
		o += (*dayK)[i]->open_fq(factor);
		c += (*dayK)[i]->close_fq(factor);
		l += (*dayK)[i]->low_fq(factor);
		h += (*dayK)[i]->high_fq(factor);
		v += (*dayK)[i]->volume;
		a += (*dayK)[i]->amount;
	}
	o /= (price_t)scope;
	c /= (price_t)scope;
	h /= (price_t)scope;
	l /= (price_t)scope;
	v /= (int64_t)scope;
	a /= (amount_t)scope;
	ma->set(o, c, l, h, (vol_share_t)v, a);
	ma->_date = (*dayK)[pos]->_date;
	ma->_time = (*dayK)[pos]->_time;
	ma->_MinmuSec = (*dayK)[pos]->_MinmuSec;
}




}