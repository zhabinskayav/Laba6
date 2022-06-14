#include "fas.h"

fas::fas(app my_AP)
{
    AP = std::make_unique<app>(my_AP);
}

void fas::parseAll(const std::string &  pathFileName)
{
    AP->readFile(pathFileName);
    if(!isFileError()){
        AP->parse(AP->getFile());
    }
}

std::string fas::getError()
{
    return AP->getError();
}

std::string fas::getJson()
{
    return AP->getJsonStr();
}

std::string fas::getText()
{
    return AP->getFile();
}

bool fas::isFileError()
{
    if(AP->getError() =="Wrong case" || AP->getError() =="Memory fail"){
        return true;
    }
    return false;
}
