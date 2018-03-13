#include "RpdRecord.h"

RpdRecord::RpdRecord()
{

  code = 0;
  invNum = 0;
  for (unsigned int i = 0; i < FIELDS_SIZE; i++)
  fields.push_back(0);
  note = "";
}

int RpdRecord::print()
{

    std::cout << "Code: " << code << std::endl;

    std::cout << "InvNum: " << invNum << std::endl;

    if(fields[RPD_ZAVKAFVIPUSK]) std::cout << "ZavKafVipusk (" << RPD_ZAVKAFVIPUSK << "): " << "1" << std::endl;

    if(fields[RPD_ZAVKAFOBESP]) std::cout << "ZavKafObesp (" << RPD_ZAVKAFOBESP << "): " << "1" << std::endl;

    if(fields[RPD_DEKAN]) std::cout  << "Dekan (" << RPD_DEKAN << "): " << "1" << std::endl;;

    if(fields[RPD_PROREKTOR]) std::cout << "Prorektor (" << RPD_PROREKTOR << "): " << "1" << std::endl;
    
    if(fields[RPD_TITUL]) std::cout << "Titul (" << RPD_TITUL << "): " << "1" << std::endl;
    
    if(fields[RPD_TEXT]) std::cout << "Text (" << RPD_TEXT << "): " << "1" << std::endl;
    
    if(fields[RPD_PROF]) std::cout << "Prof (" << RPD_PROF << "): " << "1" << std::endl;

    if(fields[RPD_AUTHOR]) std::cout << "Author (" << RPD_AUTHOR << "): " << "1" << std::endl;
    
    std::cout << "Note: " << note << std::endl;

    return 1;
    
}

std::ostream & operator<<(std::ostream &os, const RpdRecord &cr)
{
    os << cr.code << ";";

    os << cr.invNum << ";";

    if(cr.fields[RPD_ZAVKAFVIPUSK]) os << "1";
    else os << "0";
    os << ";";

    if(cr.fields[RPD_ZAVKAFOBESP]) os << "1";
    else os << "0";
    os << ";";

    if(cr.fields[RPD_DEKAN]) os << "1";
    else os << "0";
    os << ";";

    if(cr.fields[RPD_PROREKTOR]) os << "1";
    else os << "0";
    os << ";";
    
    if(cr.fields[RPD_TITUL]) os << "1";
    else os << "0";
    os << ";";
    
    if(cr.fields[RPD_TEXT]) os << "1";
    else os << "0";
    os << ";";
    
    if(cr.fields[RPD_PROF]) os << "1";
    else os << "0";
    os << ";";

    if(cr.fields[RPD_AUTHOR]) os << "1";
    else os << "0";
    os << ";";
    
    os << cr.note;
    

    return os;
}
