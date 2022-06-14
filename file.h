#ifndef FILE_H
#define FILE_H

#include <string>
#include <error.h>

class file
{
public:
    file();
    void readfile(std::string  pathFileName);
    std::string getFile();
    std::string getError();
private:
    std::string fileText;
    err error;
};

#endif // FILE_H
