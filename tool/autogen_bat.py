
import os

json_folder = "./json_template"
out_folder = "./include/jsonTypes"

files_of_api = os.listdir(json_folder)
api_list = []
for f in files_of_api:
    if f.find(".json") == len(f) - len(".json") :
        (filepath,tempfilename) = os.path.split(f)
        (filename,extension) = os.path.splitext(tempfilename)
        api_list.append([os.path.join(json_folder, f), os.path.join(out_folder, filename+".h")])

CMD_LINE = "python ./tool/autogen_json_type.py {} {}"
for api,out in api_list:
    k = os.system(CMD_LINE.format(api,out))
    if k==0:
        print("------------------\n{} succeed!\n------------------".format(api))
    else:
        print("------------------\n[ERROR] {} failed!\n------------------".format(api))
        exit(-1)

print("done!")
