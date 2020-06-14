#pragma once

#include "s4info.h"
#include "s4infK.h"

namespace S4 {

	////simple ma
	//enum SMA_tgt_t
	//{
	//	CLOSE = 0,
	//	HIGH,
	//	LOW,
	//	AMOUNT,
	//};

	class ma_t : public info_t
	{
	public:
		ma_t() {
            _date = 0;
			_MinmuSec = 0;
			_time = 0;
		};

		int O(void) const { return _o; }
		int C(void) const { return _c; }
		int L(void) const { return _l; }
		int H(void) const { return _h; }
		int V(void) const { return _v; }
		float A(void) const { 
			return _a; 
		}
		float A_kw(void) const {
			return _a / _KW;
		}
		void set(price_t o, price_t c, price_t l, price_t h, price_t v, amount_t a) {
			_o = o;
			_c = c;
			_h = h;
			_l = l;
			_v = v;
			_a = a;
		}
		/*virtual std::string& toString(void) {
			str = IntConvertor::convert(_date) + ": avg=" + IntConvertor::convert(_status.avgPrice);
			return str;
		}*/
	private:
		price_t _o = -1;
		price_t _c = -1;
		price_t _l = -1;
		price_t _h = -1;
		price_t _v = -1;
		amount_t _a = -1;

	};

	class maQ_t : public infQ_t<ma_t>
	{
	public:
		maQ_t(const infKQ_t & K, int scope, bool doCalc = true);


		size_t getScope(void) { return _scope; };

		void calc(void);
		void calc(size_t bgnI, size_t endI);
	private:
		size_t _scope;  //
		const infKQ_t* _pK;
	private:
	};

}