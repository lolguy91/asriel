ab.log_err("asd")
ab.log_info("fgh")

recipe = {
    compiler = "/usr/bin/clang",
    include = {"src", "include"},
    lib = {"lib"},
    linker = "/usr/bin/ld.lld"
} -- example for now sorry azzy
ab.add_src_dir(recipe,"src") -- src is default src dir if no other one is defined

function _default(args)
    recipe.build_parallel(ab.num_jobs)
    ab.new_linker("bin/app").run()
end
function run(args)
    _default()
    ab.new_custom_cmd("bin/app").run()
end