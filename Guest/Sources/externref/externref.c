#include "externref.h"

struct ExternRefIndex {
  int index;
};

static __externref_t table[0];

__externref_t test_builtin_wasm_table_get(ExternRefIndex index) {
  return __builtin_wasm_table_get(table, index.index);
}

void test_builtin_wasm_table_set(ExternRefIndex index, __externref_t ref) {
  return __builtin_wasm_table_set(table, index.index, ref);
}

int test_builtin_wasm_table_size(void) {
  return __builtin_wasm_table_size(table);
}

int test_builtin_wasm_table_grow(__externref_t ref, int nelem) {
  return __builtin_wasm_table_grow(table, ref, nelem);
}

void test_builtin_wasm_table_fill(int index, __externref_t ref, int nelem) {
  __builtin_wasm_table_fill(table, index, ref, nelem);
}

__attribute__((export_name("entrypoint")))
void entrypoint(__externref_t ref) {
  __builtin_wasm_table_set(table, 0, ref);
}

int foo(void) {
  return 42;
}
