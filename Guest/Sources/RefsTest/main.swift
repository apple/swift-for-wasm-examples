import externref

@_expose(wasm, "refsTest")
func refsTest() -> Int32 {
    test_builtin_wasm_table_size()
}
