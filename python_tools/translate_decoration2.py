#!/usr/bin/python
import openpyxl
import re
import os

# --- 1. 路径设置 ---
base_dir = os.path.dirname(os.path.abspath(__file__))
h_file_path = os.path.join(os.path.dirname(base_dir), "src", "data", "decoration", "header.h")
xlsx_path = os.path.join(base_dir, "src", "装饰物品.xlsx")

# --- 2. 加载 Excel 数据 ---
var_to_desc_map = {}
try:
    wb = openpyxl.load_workbook(xlsx_path)
    sheet = wb.active
    for row in sheet.iter_rows(min_row=2):
        var_name = row[0].value   # 第四列：ID (如 DECOR_SMALL_DESK)
        new_content = row[4].value # 第五列：翻译内容
        if var_name:
            # 这里的 .strip() 很关键，防止 Excel 单元格里带不可见空格
            var_to_desc_map[str(var_name).strip()] = str(new_content).replace('\n', '\\n')
    print(f"Excel 读取成功，共加载 {len(var_to_desc_map)} 条映射。")
except Exception as e:
    print(f"读取 Excel 出错: {e}")
    exit()

# --- 3. 读取 .h 文件 ---
with open(h_file_path, "r", encoding="utf-8") as file:
    h_file_content = file.read()

# --- 4. 核心正则表达式 ---
# 解释：
# \[([A-Z_0-9]+)\] : 匹配 [ID]
# .*?\.description\s*=\s*COMPOUND_STRING\s*\( : 匹配到描述开始
# (.*?) : 捕获组 2，即括号里的所有内容（跨行）
# \), : 匹配描述结束
pattern = re.compile(
    r'(\[\s*([A-Z_0-9]+)\s*\]\s*=\s*\{.*?\.\s*description\s*=\s*COMPOUND_STRING\s*\()(.*?)(\)\s*,)',
    re.DOTALL
)

def replace_description(match):
    prefix = match.group(1)      # [ID] = { ... .description = COMPOUND_STRING(
    var_name = match.group(2)    # ID 名
    old_inner = match.group(3)   # 括号里的旧文本
    suffix = match.group(4)      # ),
    
    if var_name in var_to_desc_map:
        new_desc = var_to_desc_map[var_name]
        # 格式化输出：增加换行和缩进，使代码美观
        replacement = f'\n            "{new_desc}"'
        print(f"成功替换: {var_name}")
        return f"{prefix}{replacement}{suffix}"
    
    return match.group(0)

# 执行替换
new_h_file_content = pattern.sub(replace_description, h_file_content)

# --- 5. 保存结果 ---
if new_h_file_content != h_file_content:
    with open(h_file_path, "w", encoding="utf-8") as file:
        file.write(new_h_file_content)
    print("\n>>> 替换任务顺利完成！")
else:
    print("\n[错误] 未能匹配到任何内容。请检查：")
    print("1. .h 文件中的 ID 是否在 Excel 第四列中完全匹配？")
    print("2. Excel 里的 ID 是否带了方括号？(脚本预期不带方括号，如 DECOR_SMALL_DESK)")