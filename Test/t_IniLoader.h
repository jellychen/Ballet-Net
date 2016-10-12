#include <Libs/IniLoader/IniConfigLoader.h>
using namespace Libs;

void t_IniLoaderTest_main()
{
    IniConfigLoader loader;
    loader.LoadFile("config.ini");
}
