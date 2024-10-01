<<<<<<< HEAD
ab.log_err("asd")
ab.log_info("fgh")

recipe = ab.use_template(ab.clang_c_template)
ab.add_src_dir(recipe,"src") -- src is default src dir if no other one is defined

function _default(args)
    recipe.build_parallel(ab.num_jobs)
    ab.new_linker("bin/app").run()
end
function run(args)
    _default()
    ab.new_custom_cmd("bin/app").run()
=======
recipe = ab.new_recipe()

recipe:add_src_dir("src")
recipe:set_compiler("clang")
recipe:set_linker("lld")

print("Compler: " .. recipe.compiler)
print("Linker: " .. recipe.linker)

function _default(args)
    recipe:build_func()
end

function run(args)
    _default()
    ab.new_custom_cmd("bin/app").run()
>>>>>>> origin/master
end