void test_builtin_wasm_table_set(int index, __externref_t ref);
__externref_t test_builtin_wasm_table_get(int index);

int test_builtin_wasm_table_size();
int test_builtin_wasm_table_grow(__externref_t ref, int nelem);

