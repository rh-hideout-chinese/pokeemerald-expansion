# 原始字符串
text = "全副武装的样子。\n即使是极巨化宝可梦的\n攻击也能轻易抵挡。"

# 按照\n分割
split_text = text.split('\n')

# 格式化输出为需要的三段，并处理最后一段不加\\n
formatted_text = [f'"{part}\\n"' for part in split_text[:-1]]  # 所有除最后一段外加\\n
formatted_text.append(f'"{split_text[-1]}"')  # 最后一段不加\\n

# 拼接成最终的描述
description = '\n'.join(formatted_text)

# 输出结果
print(description)
