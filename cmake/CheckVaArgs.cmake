cmake_minimum_required(VERSION 3.0)

include(CheckCSourceCompiles)

function(check_va_args_macro)
set(NONE_CODE
"#include <stdio.h>
#define print(fmt,...) fprintf(stdout, fmt, __VA_ARGS__)

int main () {
	print(\"Hi\");
	print(\"Hi %s\", \"bud\");
	print(\"Pi %d.%d%d%d%d\", 3, 1, 4, 1, 6);
	return 0;
}"
)

set(OPT_CODE
"#include <stdio.h>
#define print(fmt,...) fprintf(stdout, fmt __VA_OPT__(,) __VA_ARGS__)

int main () {
	print(\"Hi\");
	print(\"Hi %s\", \"bud\");
	print(\"Pi %d.%d%d%d%d\", 3, 1, 4, 1, 6);
	return 0;
}"
)

set(CAT_CODE
"#include <stdio.h>
#define print(fmt,...) fprintf(stdout, fmt, ##__VA_ARGS__)

int main () {
	print(\"Hi\");
	print(\"Hi %s\", \"bud\");
	print(\"Pi %d.%d%d%d%d\", 3, 1, 4, 1, 6);
	return 0;
}"
)

check_c_source_compiles(NONE_CODE NONE_WORKS)
check_c_source_compiles(OPT_CODE OPT_WORKS)
check_c_source_compiles(CAT_CODE CAT_WORKS)

set(VA_ARGS_NONE "${NONE_WORKS}" PARENT_SCOPE)
set(VA_ARGS_OPT "${OPT_WORKS}" PARENT_SCOPE)
set(VA_ARGS_CAT "${CAT_WORKS}" PARENT_SCOPE)

endfunction(check_va_args_macro)