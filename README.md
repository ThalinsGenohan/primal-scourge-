# primal-scourge-tool

Just a thing I decided to make for easy hosting and interaction in my PMD&D campaign, Primal Scourge. For the moment, it is being hardcoded to work with it and its gameplay system, but it will be expanded in the future to allow for other systems as well.

This project is being written in Visual Studio 2017, and uses SFML, TGUI, and Discord Rich Presence. I'm not entirely sure how exactly I should be handling credits and such for these libraries; this is my first actual public project (that I intend to see through to the end), so I apologize for my ineptitude. If anyone would like to inform me on such matters, it would be greatly appreciated.

## INSTALLATION

### 1. Build dependencies

SFML, TGUI, and DiscordRPC are included with this repository as submodules. You must build **and install** (their Static Release versions) using CMake before you can build this project. (If using Windows, change `CMAKE_INSTALL_PREFIX` to something besides `Program Files`, because Windows is weird.) If you don't know how to do that, then you probably want to check out the Releases.
**NOTE: You may need to pull the submodules separately, using the `git submodule update --init --recursive` command in the console for the repo directory.**

### 2. Build the Tool

Once the dependencies are installed, build **and install** this project in CMake.
**__`SFML_DIR` and `TGUI_DIR` must be set to `<INSTALL PATH>/lib/cmake/<SFML/TGUI>`. `DISCORDRPC_ROOT` must be set to the same directory where you installed it.__**

### And that's it.

Have fun ~~because I know I sure did trying to figure out how to work CMake~~.