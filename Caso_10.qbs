import qbs

CppApplication {
    consoleApplication: true
    files: [
        "library.h",
        "main.c",
        "matroiddate.h",
        "matroidfloat.h",
        "matroidint.h",
        "matroidstring.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
