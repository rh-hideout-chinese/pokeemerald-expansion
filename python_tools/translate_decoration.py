import openpyxl
import re
import os

# 文件路径
base_dir = os.path.dirname(os.path.abspath(__file__))
h_file_path = os.path.join(base_dir, "../src/data/decoration/header.h")
xlsx_path = os.path.join(base_dir, "src/装饰物品.xlsx")

# 加载Excel文件
wb = openpyxl.load_workbook(xlsx_path)
sheet = wb.active

# 读取Excel数据
replacement_list = []
for row in sheet.iter_rows(min_row=2):  # 假设第一行为标题，从第二行开始读取
    name_value = row[2].value  # 第三列
    if name_value:
        replacement_list.append(name_value)

# 打印替换列表，便于调试
print("replacement_list:", replacement_list)

# 读取.h文件内容
with open(h_file_path, "r", encoding="utf-8") as file:
    h_file_content = file.readlines()

# 替换 .name 行的内容
replacement_index = 0
for i, line in enumerate(h_file_content):
    if '.name = _("' in line and replacement_index < len(replacement_list):
        # 使用正则表达式替换 "..." 中的内容
        h_file_content[i] = re.sub(r'_\(".*?"\)', f'_("{replacement_list[replacement_index]}")', line)
        print(f"替换第 {i + 1} 行: {line.strip()} -> {h_file_content[i].strip()}")
        replacement_index += 1

# 写回 .h 文件
with open(h_file_path, "w", encoding="utf-8") as file:
    file.writelines(h_file_content)

print("替换完成！")