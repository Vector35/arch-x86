# arch-x86
This is the x86 plugin that ships with Binary Ninja.

## Building

Building the architecture plugin requires `cmake` 3.13 or above. You will also need the
[Binary Ninja API source](https://github.com/Vector35/binaryninja-api).

First, set the `BN_API_PATH` environment variable to the path containing the
Binary Ninja API source tree.

Run `cmake`. This can be done either from a separate build directory or from the source
directory. Once that is complete, run `make` in the build directory to compile the plugin.

The plugin can be found in the root of the build directory as `libarch_x86.so`,
`libarch_x86.dylib` or `arch_x86.dll` depending on your platform.

To install the plugin, first launch Binary Ninja and uncheck the "x86 architecture plugin"
option in the "Core Plugins" section. This will cause Binary Ninja to stop loading the
bundled plugin so that its replacement can be loaded. Once this is complete, you can copy
the plugin into the user plugins directory (you can locate this by using the "Open Plugin Folder"
option in the Binary Ninja UI).

**Do not replace the architecture plugin in the Binary Ninja install directory. This will
be overwritten every time there is a Binary Ninja update. Use the above process to ensure that
updates do not automatically uninstall your custom build.**

## XED

XED is at commit e72b2c89cbf949af2ee0d26a571ca6a71e13835d

To update XED, first update the submodules and run `make -f Makefile.xed`...do this on each platform and put the lib's in `/lib` named appropriately.
