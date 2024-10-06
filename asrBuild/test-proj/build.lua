recipe = ab.new_recipe()

recipe:add_src_dir("src")
recipe:set_compiler("clang")
recipe:set_linker("lld")
recipe:set_extension(".c")

function _default(args)
    recipe:build_func()
end

function run(args)
    _default()
    ab.new_custom_cmd("bin/app").run()
end