import externref

@expose(wasm, "refsTest")
func refsTest() -> Int {
    task_builtin_wasm_table_size()
}

