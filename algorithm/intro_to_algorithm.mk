# 制作CLRS教材的算法源码makefile
# 制作策略：文件名全部小写
# 示例：stack.h stack.c stack_test.c
# 实现文件分章节建立目录树
# 编程约定：
# Macros		ALL_CAPS
# Typedef		TitleCase(no typedef for pointers ? or TitleCasePtr?)
# Struct 		TitleCase
# Struct Members 	lowerCase
# Enum 			ETitleCase
# Enum Members		ALL_CAPS

# functions		lower_case
# Trivial variables	i, x, n, f, etc
# Local variables 	lowerCase
# Global variables 	g_lowerCase
