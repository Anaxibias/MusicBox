#include "callback_functions.h"

int null_callback(void* unused, int num_columns, char** row_data, char** column_name) {
	return 0;
}