import qbs

CppApplication {
    consoleApplication: true
    files: [
        "library.h",
        "list.h",
        "main.c",
        "matroid.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
