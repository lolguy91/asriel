recipe = {
    compiler = "/usr/bin/clang",
    include = {"src", "include"},
    lib_dirs = {"lib"},
    src_dirs = {},
    linker = "/usr/bin/ld.lld"
} -- Im too lazy to do the recipe creation function rn

ab.add_src_dir(recipe,"src")

for _, dir in ipairs(recipe.src_dirs) do
    print(dir)
end


function _default(args)
    recipe.build_parallel(ab.num_jobs)
    ab.new_linker("bin/app").run()
end
function run(args)
    _default()
    ab.new_custom_cmd("bin/app").run()
end