import openpyxl
import re
import os

# 文件路径
h_file_path = os.path.dirname(os.path.abspath(__file__))+"/../src/data/decoration/description.h"
xlsx_path = os.path.dirname(os.path.abspath(__file__))+"/src/装饰物品.xlsx"

# 加载Excel文件
wb = openpyxl.load_workbook(xlsx_path)
sheet = wb.active

# 读取Excel数据
var_to_desc_map = {}
for row in sheet.iter_rows(min_row=2):  # 假设第一行为标题，从第二行开始读取
    var_name = row[3].value  # 第四列
    new_content = row[4].value  # 第五列
    if var_name and new_content:
        var_to_desc_map[var_name] = new_content

# 读取.h文件内容
with open(h_file_path, "r", encoding="utf-8") as file:
    h_file_content = file.read()

# 匹配并替换括号内的内容
def replace_description(match):
    var_name = match.group(1)  # 匹配到的变量名
    if var_name in var_to_desc_map:
        new_desc = var_to_desc_map[var_name]
        return f'{var_name}[] = _("{new_desc}")'  # 替换括号内的内容
    return match.group(0)

# 正则表达式匹配变量名及括号内容
pattern = re.compile(
    r'(DecorDesc_[A-Z_0-9]+)\[\]\s*=\s*_\((.*?)\)',  # 匹配变量名和括号内容
    re.DOTALL
)

# 替换内容
new_h_file_content = pattern.sub(replace_description, h_file_content)

# 写回.h文件
with open(h_file_path, "w", encoding="utf-8") as file:
    file.write(new_h_file_content)

print("替换完成！")