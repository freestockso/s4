import json
import sys
import os

from autogen_json_type import cpp_headers, keep_words

json_cpp_headers = cpp_headers + \
"""
#include "types/s4type.h"
#include "db_sqlite/tableIO.h"

"""

namespace_head = \
"""
namespace S4 {
namespace sqlite {
"""

namespace_tail = \
"""
}//namespace sqlite
}//namespace S4
"""


def determin_value_type_sqlite(value):
    if isinstance(value, str):
        return "TEXT"
    elif isinstance(value, bool):
        return " BOOLEAN"
    elif isinstance(value, int):
        return "INTEGER"
    elif isinstance(value, float):
        return "DOUBLE"

def get_func(value):
    if value == "TEXT":
        return "getString"
    elif value == "BOOLEAN":
        return "getInt"
    elif value == "INTEGER":
        return "getInt"
    elif value == "DOUBLE":
        return "getDouble"

# not support list or dict within dict
def dict_to_cols(json_dict):
    cols = {}

    if '__assign_type_fields__' in json_dict:
        __assign_type_fields__ = json_dict['__assign_type_fields__']
        print("use __assign_type_fields__ = {}".format(__assign_type_fields__))
    else:
        __assign_type_fields__ = {}
        
    for key_name in json_dict:
        if key_name in keep_words:
            continue

        key_value = json_dict[key_name]

        if isinstance(key_value, (str, int, float, bool)):
            key_type = determin_value_type_sqlite(key_value)
            cols[key_name] = key_type
        elif isinstance(key_value, dict):
            print("unsupported type for <dict> {}:{}".format(key_name, key_value))
            exit(-1)
        elif isinstance(key_value, list):
            print("unsupported type for <list> {}:{}".format(key_name, key_value))
            exit(-1)
            # if len(key_value)==0:
            # else:
            #     key_value = key_value[0]
            #     if isinstance(key_value, (str, int, float, bool) or key_name in __assign_type_fields__):
            #     elif isinstance(key_value, dict):
            #     else:
            #         print("unsupported list type for {}:{}".format(key_name, key_value))
            #         exit(-1)
        else:
            print("unsupported type for {}:{}".format(key_name, key_value))
            exit(-1)

    return cols, __assign_type_fields__


PRIMARY_KEY_in_order = [ 'date', 'mktCode', 'datetime', 'code']

def get_K_COL(cols):
    K_COL = \
"""
const std::string K_COL(
    "( "
"""
    primary_key = None
    for name in cols:
        v_type = cols[name]
        K_COL += '        "{}\t{}, "\n'.format(name, v_type)
        if primary_key is None:
            primary_key = name

    for key in PRIMARY_KEY_in_order:
        if key in cols:
            primary_key = key
            break

    K_COL += \
'''
        "PRIMARY KEY({})"
    ")");
'''.format(primary_key)

    return K_COL

def get_K_IN(cols):
    
    K_IN = \
'''
const std::string K_IN(
    "("'''
    l = []
    for name in cols:
        l.append(name)

    K_IN += \
"""
    "{}"
    ") VALUES ({})"
);
""".format(", ".join(l), ','.join(['?']*len(cols)))

    return K_IN


def get_class(data_type_name, io_class_name, K_COL, K_IN, cols, __assign_type_fields__):
    n = 0
    col_list = []
    load = []
    for col in cols:
        col_list.append(col)
        if col in __assign_type_fields__:
            as_type = '({})'.format(__assign_type_fields__[col])
        else:
            as_type = ''
        l = "K_data.{} = {}query.getColumn({}).{}();".format(col, as_type, n, get_func(cols[col]))
        n += 1
        load.append(l)

    load = "\n\t\t".join(load)

    class_str = \
"""
class {1} : public tableIO_t<struct {0}>{{
public:
	{1}(const std::string name):
		m_name(name),
        m_qurey_build("CREATE TABLE if not exists " + m_name + K_COL),
        m_qurey_insert("INSERT OR IGNORE INTO " + m_name + K_IN)
    {{}};
    
	virtual void set_name(const std::string& name) override {{
        m_name = name;
        m_qurey_build = "CREATE TABLE if not exists " + m_name + K_COL;
        m_qurey_insert = "INSERT OR IGNORE INTO " + m_name + K_IN;
    }}

    virtual const std::string & get_query_build(void) const override {{ return m_qurey_build;}};

    virtual const std::string & get_query_insert(void) const override {{ return m_qurey_insert;}};
    
    virtual void bind_query(SQLite::Statement& query, const std::vector<struct {0}>& data, size_t nb) override
    {{
        const struct {0} & K_data = data[nb];
        SQLite::bind(query{4});
    }}

    //warning: not clear data inside, but append DB.data to it
    virtual void load_query(SQLite::Statement& query, std::vector<{0}>& data) override
    {{
        struct {0} K_data;
        {5}
        data.push_back(std::move(K_data));
    }}

private:
	std::string m_name;
    std::string m_qurey_build;
    std::string m_qurey_insert;
private:
{2}

{3}

}};
""".format(data_type_name, io_class_name, K_COL, K_IN, ',\n\t\t\tK_data.'.join(col_list), load)
    return class_str


if __name__ == "__main__":
    print("Current working path={}".format(os.getcwd()))

    if len(sys.argv)==1:
        print("Need at least 1 arg:")
        print("  {} <json file>  [<output file>]".format(sys.argv[0]))
        exit(1)

    src_json = sys.argv[1]
    data_type_name = os.path.basename(src_json)
    data_type_name = data_type_name.split(".")[0]
    io_class_name = data_type_name + "_dbTbl"
    print("Creating Cpp file for type={}, tbl_class={}".format(data_type_name, io_class_name))

    if len(sys.argv)>=3:
        tgt_cpp = sys.argv[2]
        if tgt_cpp.find(".") <0:
            tgt_cpp = tgt_cpp + "/" + io_class_name + ".h"
    else:
        tgt_cpp = src_json.replace(".json", "_dbTbl.h")

    print("reading json file:{}".format(src_json))
    with open(src_json, 'r', encoding='UTF-8') as f:
        text = f.readlines()
    # print(text)
    text = "".join(text)
    json_instance = json.loads(text)

    # print("read json OK:\n{}".format(json.dumps(json_instance, indent=4, separators=(',', ': '))))

    print("read json base type={}".format(type(json_instance)))
    if not isinstance(json_instance, dict):
        print("error:only support base type==dict for now!")
        exit(0)

    cols, __assign_type_fields__ = dict_to_cols(json_instance)
    K_IN = get_K_IN(cols)
    K_COL = get_K_COL(cols)
    class_t = get_class(data_type_name, io_class_name, K_COL, K_IN, cols, __assign_type_fields__)
    print(class_t)


    output_text = json_cpp_headers + namespace_head + class_t + namespace_tail
    
    if tgt_cpp is not None:
        with open(tgt_cpp, 'w+') as fo:
            fo.write(output_text)

