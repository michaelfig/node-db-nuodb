{
        "targets": [
                {
                        "target_name": "nuodb_bindings",
                        "sources": [
                                "lib/node-db/binding.cc", 
                                "lib/node-db/connection.cc",
                                "lib/node-db/events.cc", 
                                "lib/node-db/exception.cc",
                                "lib/node-db/query.cc", 
                                "lib/node-db/result.cc", 
                                "src/node_db_nuodb_bindings.cc", 
                                "src/node_db_nuodb.cc",
                                "src/node_db_nuodb_connection.cc", 
                                "src/node_db_nuodb_query.cc",
                                "src/node_db_nuodb_result.cc"
                        ],
                        "cflags!": [ 
                                "-fno-exceptions" 
                        ],
                        "cflags_cc!": [ 
                                "-fno-exceptions" 
                        ],
                        "conditions": [
                                ["OS=='linux'", {
                                        "cflags": [
                                                "-Wall",
                                                "-w"
                                        ],
                                        "link_settings": {
                                                "libraries": [
                                                           "-Wl,-rpath,/opt/nuodb/lib64",
                                                           "-L/opt/nuodb/lib64",
                                                           "-lNuoRemote"
                                                ],
                                                "include_dirs": [
                                                           "/opt/nuodb/lib64"
                                                ]
                                        },
                                        "include_dirs": [
                                                "lib",
                                                "/usr/local/include/node",
                                                "/opt/nuodb",
                                                "/opt/nuodb/lib64",
                                                "/opt/nuodb/include"
                                        ]
                                }],
                                ["OS=='mac'", {
                                        "xcode_settings": {
                                                "LD_RUNPATH_SEARCH_PATHS": [
                                                        "/opt/nuodb/lib64"
                                                ],
                                                "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                                                "WARNING_CFLAGS!": [
                                                        "-Wall",
                                                        "-W",
                                                ]
                                        },
                                        "link_settings": {
                                                "libraries": [
                                                           "-L/opt/nuodb/lib64",
                                                           "-lNuoRemote"
                                                ],
                                                "include_dirs": [
                                                           "/opt/nuodb/lib64"
                                                ]
                                        },
                                        "include_dirs": [
                                                "lib",
                                                "/usr/local/include/node",
                                                "/opt/nuodb",
                                                "/opt/nuodb/lib64",
                                                "/opt/nuodb/include"
                                        ]
                                }],
                                ["OS=='solaris'", {
                                        "cflags": [
                                                "-Wall",
                                                "-W"
                                        ],
                                        "link_settings": {
                                                "libraries": [
                                                           "-Wl,-rpath,/opt/nuodb/lib64",
                                                           "-L/opt/nuodb/lib64",
                                                           "-lNuoRemote"
                                                ],
                                                "include_dirs": [
                                                           "/opt/nuodb/lib64"
                                                ]
                                        },
                                        "include_dirs": [
                                                "lib",
                                                "/usr/local/include/node",
                                                "/opt/nuodb",
                                                "/opt/nuodb/lib64",
                                                "/opt/nuodb/include"
                                        ]
                                }]
                        ]
                }
        ]
}