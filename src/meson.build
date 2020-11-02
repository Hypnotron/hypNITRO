deps = [dependency('vulkan'), dependency('sdl2')] 
executable(
        'hypnitro-cli', 
        'interface/cli.cpp', 
        install : true,
        dependencies : deps)
executable(
        'hypnitro-imgui', 
        'interface/gui.cpp', 
        install : true,
        dependencies : deps)

accuracy_test = executable('hypnitro-accuracy-test', 'interface/test.cpp')
test('Accuracy Test', accuracy_test)

