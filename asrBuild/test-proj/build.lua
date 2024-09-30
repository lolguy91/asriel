recipe = ab.new_recipe()

function _default(args)
    recipe:build_func()
end

function run(args)
    _default()
    ab.new_custom_cmd("bin/app").run()
end