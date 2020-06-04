/*
* DON'T TOUCH!
* This file is generated by python script AUTOMATICALLY!
*
* Generated base on: ./json_template\db_history_t.json
* Type name: db_history_t
* Tester:    int db_history_t_tester();
*
* Json keep-word: 
    "__default_value_fields__": [], # Take value in .json file as the default value of cpp variable
    "__optional_fields__": [], # Not require to present to .json file, but always in cpp struct
    "__assign_type_fields__": {"field":"cpp-type"}, # Assign specal cpp-type of field, but not infer automatically as default
    "__assign_set_lists__": [], # Take list in .json file as std::set<>, but not std::vector<> as default
    "__comment__xxx":"", # Add comment line
* Script author: ChenZaihui<chinsaiki@outlook.com>
*/
#pragma once
#include <assert.h>
#include "common/s4json_util.h"
#include "common/s4logger.h"
#include "types/s4type.h"

#include <set>
#include <list>
#include <vector>

namespace S4 {

/* type */
struct db_history_t {
	int rowid;	//	0
//strategy name
	std::string stgName;	//	tdx_xyzq
//id through open-close
	int id;	//	0
	int tdxOrderId;	//	0
	std::string insCode;	//	sz000001
//no name, 平安银行 is not good for sqliteDB
	int time;	//	123
	std::string datetime;	//	2018_04_26__00_00_00
//current option of id: open / change_take / change_stop / close / change_close / abort
	std::string optType;	//	open
//long as stock only for now
	std::string position;	//	long
//current status of id: new / opened / closed / aborted
	std::string status;	//	new
	int open;	//	-1
	int take;	//	-1
	int stop;	//	-1
	int close;	//	-1
//not in use for now
	int open_deal;	//	-1
	int openVol;	//	-1
	int openVol_deal;	//	-1
	int openAmt_deal;	//	0
	int close_deal;	//	-1
	int closeVol;	//	-1
	int closeVol_deal;	//	-1
	int closeAmt_deal;	//	0
	int commission;	//	0
	int stamp_duty;	//	0
	int transfer_fee;	//	0
	int other_fees;	//	0
	std::string remarks;	//	起始配号:226168906

	/* from json */
	static bool from_json(const json& json_var, db_history_t& db_history_t_var){
		try{
			try{
				db_history_t_var.rowid = json_var.at("rowid").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "rowid", e.what());
				throw e;
			}
			try{
				db_history_t_var.stgName = json_var.at("stgName").get<std::string>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "stgName", e.what());
				throw e;
			}
			try{
				db_history_t_var.id = json_var.at("id").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "id", e.what());
				throw e;
			}
			try{
				db_history_t_var.tdxOrderId = json_var.at("tdxOrderId").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "tdxOrderId", e.what());
				throw e;
			}
			try{
				db_history_t_var.insCode = json_var.at("insCode").get<std::string>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "insCode", e.what());
				throw e;
			}
			try{
				db_history_t_var.time = json_var.at("time").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "time", e.what());
				throw e;
			}
			try{
				db_history_t_var.datetime = json_var.at("datetime").get<std::string>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "datetime", e.what());
				throw e;
			}
			try{
				db_history_t_var.optType = json_var.at("optType").get<std::string>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "optType", e.what());
				throw e;
			}
			try{
				db_history_t_var.position = json_var.at("position").get<std::string>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "position", e.what());
				throw e;
			}
			try{
				db_history_t_var.status = json_var.at("status").get<std::string>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "status", e.what());
				throw e;
			}
			try{
				db_history_t_var.open = json_var.at("open").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "open", e.what());
				throw e;
			}
			try{
				db_history_t_var.take = json_var.at("take").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "take", e.what());
				throw e;
			}
			try{
				db_history_t_var.stop = json_var.at("stop").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "stop", e.what());
				throw e;
			}
			try{
				db_history_t_var.close = json_var.at("close").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "close", e.what());
				throw e;
			}
			try{
				db_history_t_var.open_deal = json_var.at("open_deal").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "open_deal", e.what());
				throw e;
			}
			try{
				db_history_t_var.openVol = json_var.at("openVol").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "openVol", e.what());
				throw e;
			}
			try{
				db_history_t_var.openVol_deal = json_var.at("openVol_deal").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "openVol_deal", e.what());
				throw e;
			}
			try{
				db_history_t_var.openAmt_deal = json_var.at("openAmt_deal").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "openAmt_deal", e.what());
				throw e;
			}
			try{
				db_history_t_var.close_deal = json_var.at("close_deal").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "close_deal", e.what());
				throw e;
			}
			try{
				db_history_t_var.closeVol = json_var.at("closeVol").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "closeVol", e.what());
				throw e;
			}
			try{
				db_history_t_var.closeVol_deal = json_var.at("closeVol_deal").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "closeVol_deal", e.what());
				throw e;
			}
			try{
				db_history_t_var.closeAmt_deal = json_var.at("closeAmt_deal").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "closeAmt_deal", e.what());
				throw e;
			}
			try{
				db_history_t_var.commission = json_var.at("commission").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "commission", e.what());
				throw e;
			}
			try{
				db_history_t_var.stamp_duty = json_var.at("stamp_duty").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "stamp_duty", e.what());
				throw e;
			}
			try{
				db_history_t_var.transfer_fee = json_var.at("transfer_fee").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "transfer_fee", e.what());
				throw e;
			}
			try{
				db_history_t_var.other_fees = json_var.at("other_fees").get<int>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "other_fees", e.what());
				throw e;
			}
			try{
				db_history_t_var.remarks = json_var.at("remarks").get<std::string>();
			}catch(const std::exception& e){
				ERR("{:} not found in json! e={:}", "remarks", e.what());
				throw e;
			}
		}catch (const std::exception& e){
			ERR("parse json {:} \nfail:{:}", json_var.dump(4), e.what());
			return false;
		}
		return true;
	}
	/* to json */
	static bool to_json(json& json_var, const db_history_t& db_history_t_var){
		try{
			json_var["rowid"] = db_history_t_var.rowid;
			json_var["stgName"] = db_history_t_var.stgName;
			json_var["id"] = db_history_t_var.id;
			json_var["tdxOrderId"] = db_history_t_var.tdxOrderId;
			json_var["insCode"] = db_history_t_var.insCode;
			json_var["time"] = db_history_t_var.time;
			json_var["datetime"] = db_history_t_var.datetime;
			json_var["optType"] = db_history_t_var.optType;
			json_var["position"] = db_history_t_var.position;
			json_var["status"] = db_history_t_var.status;
			json_var["open"] = db_history_t_var.open;
			json_var["take"] = db_history_t_var.take;
			json_var["stop"] = db_history_t_var.stop;
			json_var["close"] = db_history_t_var.close;
			json_var["open_deal"] = db_history_t_var.open_deal;
			json_var["openVol"] = db_history_t_var.openVol;
			json_var["openVol_deal"] = db_history_t_var.openVol_deal;
			json_var["openAmt_deal"] = db_history_t_var.openAmt_deal;
			json_var["close_deal"] = db_history_t_var.close_deal;
			json_var["closeVol"] = db_history_t_var.closeVol;
			json_var["closeVol_deal"] = db_history_t_var.closeVol_deal;
			json_var["closeAmt_deal"] = db_history_t_var.closeAmt_deal;
			json_var["commission"] = db_history_t_var.commission;
			json_var["stamp_duty"] = db_history_t_var.stamp_duty;
			json_var["transfer_fee"] = db_history_t_var.transfer_fee;
			json_var["other_fees"] = db_history_t_var.other_fees;
			json_var["remarks"] = db_history_t_var.remarks;
		}catch (const std::exception& e){
		ERR("to json {:} \nfail:{:}", json_var.dump(4), e.what());
			return false;
		}
		return true;
	}
};// struct db_history_t
} // namespace S4


    /* Tester */
    inline int db_history_t_tester() {

        //std::ifstream i("G:/E/work/999_s/s4/./json_template/db_history_t.json");
        std::string i("{    \"rowid\":0,    \"__comment__0\":\"strategy name\",    \"stgName\": \"tdx_xyzq\",    \"__comment__1\":\"id through open-close\",    \"id\":0,    \"tdxOrderId\": 0,    \"insCode\":\"sz000001\",    \"__comment__2\":\"no name, 平安银行 is not good for sqliteDB\",    \"time\": 123,    \"datetime\": \"2018_04_26__00_00_00\",    \"__comment__3\":\"current option of id: open / change_take / change_stop / close / change_close / abort\",    \"optType\":\"open\",    \"__comment__4\":\"long as stock only for now\",    \"position\": \"long\",    \"__comment__5\":\"current status of id: new / opened / closed / aborted\",    \"status\":\"new\",    \"open\":-1,    \"take\":-1,    \"stop\":-1,    \"close\":-1,    \"__comment__6\":\"not in use for now\",    \"open_deal\":-1,    \"openVol\":-1,    \"openVol_deal\":-1,    \"openAmt_deal\":0,    \"close_deal\":-1,    \"closeVol\":-1,    \"closeVol_deal\":-1,    \"closeAmt_deal\":0,    \"commission\":0,    \"stamp_duty\":0,    \"transfer_fee\":0,    \"other_fees\":0,    \"remarks\":\"起始配号:226168906\"}");
        S4::json json_var;
        //i >> json_var; //from file
        json_var = S4::json::parse(i);  //from string

        S4::db_history_t db_history_t_var;

        if(!S4::db_history_t::from_json(json_var, db_history_t_var)){
            INFO("S4::db_history_t::from_json fail!");
            return -1;
        }

        S4::json j_out;
        if(!S4::db_history_t::to_json(j_out, db_history_t_var)){
            INFO("S4::db_history_t::to_json fail!");
            return -1;
        }

        INFO("{:}", j_out.dump(4));

        return 0;
    }

    