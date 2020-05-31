#pragma once

#include "jsonTypes/tdx_xyzq_history_deal_t.h"
#include "jsonTypes/tdx_xyzq_history_order_t.h"

namespace S4{
namespace TDX{

bool read_history_deal(const std::string& file_name, std::vector<tdx_xyzq_history_deal_t>& deals);

bool read_history_order(const std::string& file_name, std::vector<tdx_xyzq_history_order_t>& orders);


} // namespace TDX
} // namespace S4

