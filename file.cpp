#include "file.h"

file::file()
{

}

void file::readfile(std::string pathFileName)
{
    std::string data;
    char buf[pathFileName.length() + 1];
    strcpy(buf, pathFileName.c_str());
    FILE * fp = fopen(buf, "r");
    if(fp == NULL){
        error.setIndexAndBase(0, "Cannot open file");
    }else{
        char c = fgetc(fp);
        while (c != EOF) {
           data.push_back(c);
           c = fgetc(fp);
        }
        fclose(fp);
        fileText = data;
    }
}

std::string file::getFile()
{
    return fileText;
}

std::string file::getError()
{
    return error.formatError();
}

