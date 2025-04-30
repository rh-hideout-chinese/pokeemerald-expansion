
import os
import re
import pandas as pd
import os

current_folder = os.path.dirname(os.path.abspath(__file__))

def query_pokemon_info(name, df):
    try:
        result = df.loc[name]
        return {
            '汉化文本': result['汉化文本'],
            # 'description': result['description']
        }
    except KeyError:
        return None
    
def replace_move_info(content, df):
    # const u8 gText_ExpandedPlaceholder_Empty[] = _("")
    pattern = r"const u8 gText_(\w+)\[\]\s*=\s*_\(\s*\"([^\"]*)\"\s*\)\s*;"
    matches = list(re.finditer(pattern, content, re.DOTALL))

    for match in matches:
        move = match.group(1)
        original_block = match.group(0)
        print(move, original_block)
        info = query_pokemon_info("gText_"+move, df)
        if not info:
            log(f"❌ 未找到 {'MOVE_'+move}，跳过")
            continue
        try:
            block = original_block
            escaped_text = info["汉化文本"]
            print(info)
            block = re.sub(r'const u8 gText_(\w+)\[\]\s*=\s*_\(".*?"\)\s*;', lambda m: f'const u8 gText_{move}[] = _("{escaped_text}");',block)
        except Exception as e:
            print(f"Error: {e}")
            log(f"❌ {'MOVE_'+move} 没有单独招式效果说明，跳过")
            continue

        content = content.replace(original_block, block)

    return content

def log(message):
    with open(current_folder+"\log.txt", "a", encoding="utf-8") as log_file:
        log_file.write(message + "\n")
    print(message)
if __name__ == "__main__":

    work_file = current_folder +"\..\src\strings.c"
    df = pd.read_excel(current_folder + r'\src\文本.xlsx')

    # 检查并清理重复的“变量名”
    df = df.drop_duplicates(subset='变量名', keep='first')

    # 将“变量名”设置为索引
    df.set_index('变量名', inplace=True)
    with open(work_file, "r", encoding="utf-8") as f:
        content = f.read()

    new_content = replace_move_info(content, df)

    with open(work_file, "w", encoding="utf-8") as f:
        f.write(new_content)