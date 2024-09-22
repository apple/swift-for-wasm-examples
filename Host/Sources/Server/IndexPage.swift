
struct IndexPage {
    struct Module {
        let name: String
        let path: FilePath
    }

    let modules: [Module]
}