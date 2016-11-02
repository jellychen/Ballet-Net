#include "ZsWorkboard.h"
using namespace Zeus;

const std::string _g_manifestFile    = "Manifest.xml";
const std::string _g_workProcessFile = "WorkProcess.id";

ZsWorkboard::ZsWorkboard(const char* path)
{
    if (!path)
    {
        throw std::runtime_error("ZsWorkboard Construct Failed");
    }

    workboard_ = path;
    if (false == BalDirUtil::IsPathExist(workboard_.c_str()))
    {
        if (false == BalDirUtil::CreateDir(workboard_.c_str()))
        {
            throw std::runtime_error("ZsWorkboard CreateDir Failed");
        }
    }
    opts_.LoadOptions((workboard_ + _g_manifestFile).c_str());
}

ZsWorkboard::~ZsWorkboard()
{

}

bool ZsWorkboard::IsProcessExist(int* pid)
{
    if (pid) *pid = 0;
    FILE* file = ::fopen((workboard_ + _g_workProcessFile).c_str(), "r+");
    if (nullptr_() == file) return false;

    int id = 0; bool readSuccess = false;
    if (1 == ::fscanf(file, "%d\n", &id))
    {
        readSuccess = true;
        if (pid) *pid = id;
    }
    ::fclose(file);
    return readSuccess && (0 == ::kill(id, 0));
}

bool ZsWorkboard::WriteProcessIdIntoFile()
{
    FILE* file = ::fopen((workboard_ + _g_workProcessFile).c_str(), "w+");
    if (nullptr_() == file) return false;
    int pid = ::getpid(); ::fseek(file, 0L, SEEK_SET);
    fprintf(file, "%d\n", pid); ::fflush(file);
    ::fclose(file);
    return true;
}
