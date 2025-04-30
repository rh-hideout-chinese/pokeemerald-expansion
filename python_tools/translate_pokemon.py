import os
import re
import pandas as pd
import os

current_folder = os.path.dirname(os.path.abspath(__file__))

def convert_description_to_multiline(description):
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
            'speciesName': result['speciesName'],
            'categoryName': result['categoryName'],
            'description': result['description']
        }
    except KeyError:
        return None

def replace_species_info(content, df):
    pattern = r"\[SPECIES_(\w+)\]\s*=\s*\{.*?\n\s*\},?"
    matches = list(re.finditer(pattern, content, re.DOTALL))

    for match in matches:
        species = match.group(1)
        original_block = match.group(0)
        info = query_pokemon_info("SPECIES_"+species, df)
        if not info:
            log(f"❌ 未找到 {'SPECIES_'+species}，跳过")
            continue

        block = original_block

        # 替换 .speciesName
        block = re.sub(r'\.speciesName\s*=\s*_\(.*?\),', f'.speciesName = _("{info["speciesName"]}"),', block)

        # 替换 .categoryName
        block = re.sub(r'\.categoryName\s*=\s*_\(.*?\),', f'.categoryName = _("{info["categoryName"]}"),', block)

        # 替换 .description
        block = re.sub(r'\.description\s*=\s*COMPOUND_STRING\((?:.|\n)*?\),', convert_description_to_multiline(info["description"]), block)

        content = content.replace(original_block, block)

    return content

def log(message):
    with open(current_folder+"\log.txt", "a", encoding="utf-8") as log_file:
        log_file.write(message + "\n")
    print(message)

if __name__ == "__main__":

    work_folder = current_folder +"\..\src\data\pokemon\species_info"
    df = pd.read_excel(current_folder +r'\src\图鉴.xlsx')
    df.set_index('name', inplace=True)

    for filename in os.listdir(work_folder):
        if re.match(r'^gen_\d+_families\.h$', filename):
            file_path = os.path.join(work_folder, filename)
            log(f"✅ 处理文件：{file_path}")
            with open(file_path, "r", encoding="utf-8") as f:
                content = f.read()

            new_content = replace_species_info(content, df)

            with open(file_path, "w", encoding="utf-8") as f:
                f.write(new_content)
