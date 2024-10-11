
static __externref_t table[0];

// __externref_t test_builtin_wasm_table_get(int index) {
//   return __builtin_wasm_table_get(table, index);
// }
//
// void test_builtin_wasm_table_set(int index, __externref_t ref) {
//   return __builtin_wasm_table_set(table, index, ref);

int test_builtin_wasm_table_size() {
  return __builtin_wasm_table_size(table);
}

// int test_builtin_wasm_table_grow(__externref_t ref, int nelem) {
//   return __builtin_wasm_table_grow(table, ref, nelem);
// }
//
// void test_builtin_wasm_table_fill(int index, __externref_t ref, int nelem) {
//   __builtin_wasm_table_fill(table, index, ref, nelem);
// }
//
// static __externref_t other_table[0];
//
// void test_table_copy(int dst_idx, int src_idx, int nelem) {
//   __builtin_wasm_table_copy(table, other_table, dst_idx, src_idx, nelem);
// }
//
// __attribute__((export_name("entrypoint")))
// void entrypoint(__externref_t ref) {
//   __builtin_wasm_table_set(table, 0, ref);
// }
//
