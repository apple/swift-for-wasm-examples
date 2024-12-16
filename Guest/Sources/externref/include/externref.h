#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct ExternRefIndex ExternRefIndex;

void test_builtin_wasm_table_set(ExternRefIndex index, __externref_t ref);
__externref_t test_builtin_wasm_table_get(ExternRefIndex index);

int test_builtin_wasm_table_size(void);
int test_builtin_wasm_table_grow(__externref_t ref, int nelem);

int foo(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
