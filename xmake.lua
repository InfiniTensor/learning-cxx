add_rules("mode.debug", "mode.release")
set_encodings("utf-8")
set_warnings("all")
set_languages("cxx17")
-- set_toolchains("msvc")

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

-- 定义一个目标，目标类型为 'binary'，即编译成可执行文件
target("hello_world")
    set_kind("binary")
    add_files("exercises/00_hello_world/main.cpp")  -- 确保路径和文件名正确