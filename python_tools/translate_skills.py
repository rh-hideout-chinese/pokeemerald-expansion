import os
import re
import pandas as pd
import os

current_folder = os.path.dirname(os.path.abspath(__file__))

def convert_description_to_multiline(description):
    if not isinstance(description, str):
        return None
    # 替换中文字符为英文字符
    split_text = description.split('\\n')

    # 格式化输出为需要的三段，并处理最后一段不加\\n
    formatted_text = [f'"{part}\\\\n"' for part in split_text[:-1]]  # 所有除最后一段外加\\n
    formatted_text.append(f'"{split_text[-1]}"')  # 最后一段不加\\n

    # 拼接成最终的描述
    description = '\n\\t\\t\\t'.join(formatted_text)
    final=r'.description = COMPOUND_STRING(\n\t\t\t' + description+ '),'
    return final 

def query_pokemon_info(name, df):
    try:
        result = df.loc[name]
        return {
            '中文名': result['中文名'],
            '单独招式效果说明': result['单独招式效果说明'],
            # 'description': result['description']
        }
    except KeyError:
        return None

def replace_move_info(content, df):
    pattern = r"\[MOVE_(\w+)\]\s*=\s*\{.*?\n\s*\},?"
    matches = list(re.finditer(pattern, content, re.DOTALL))

    for match in matches:
        move = match.group(1)
        original_block = match.group(0)
        info = query_pokemon_info("[MOVE_"+move+"]", df)
        if not info:
            log(f"❌ 未找到 {'MOVE_'+move}，跳过")
            continue

        block = original_block

        # 替换 .moveName
        block = re.sub(r'\.name\s*=\s*COMPOUND_STRING\(.*?\),', f'.name = COMPOUND_STRING("{info["中文名"]}"),', block)

        # block = re.sub(r'\.categoryName\s*=\s*_\(.*?\),', f'.categoryName = _("{info["categoryName"]}"),', block)
        try:
            block = re.sub(r'\.description\s*=\s*COMPOUND_STRING\((?:.|\n)*?\),\s+#endif', convert_description_to_multiline(info["单独招式效果说明"]), block)
            block = re.sub(r'\.description\s*=\s*COMPOUND_STRING\((?:.|\n)*?\),', convert_description_to_multiline(info["单独招式效果说明"]), block)
        except Exception as e:
            print(f"Error: {e}")
            log(f"❌ {'MOVE_'+move} 没有单独招式效果说明，跳过")
        content = content.replace(original_block, block)

    return content

def log(message):
    with open(current_folder+"\log.txt", "a", encoding="utf-8") as log_file:
        log_file.write(message + "\n")
    print(message)

if __name__ == "__main__":

    work_file = current_folder +"\..\src\data\moves_info.h"
    df = pd.read_excel(current_folder +r'\src\招式.xlsx')
    df.set_index('招式', inplace=True)


    with open(work_file, "r", encoding="utf-8") as f:
        content = f.read()

    new_content = replace_move_info(content, df)

    with open(work_file, "w", encoding="utf-8") as f:
        f.write(new_content)
