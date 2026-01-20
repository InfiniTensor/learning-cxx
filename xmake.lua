add_rules("mode.debug", "mode.release")
set_encodings("utf-8")
set_warnings("all")
set_languages("cxx17")
-- 添加编译toolchains，使用mingw/g++
set_toolchains("mingw")

target("test")
    set_kind("static")
    add_defines(string.format("__XMAKE__=\"%s\"", os.scriptdir():gsub("\\", "/")))
    add_files("learn/test.cpp")

target("learn")
    set_kind("binary")
    add_deps("test")
    add_files("learn/learn.cpp")

target("summary")
    set_kind("binary")
    add_deps("test")
    add_files("learn/summary.cpp")
