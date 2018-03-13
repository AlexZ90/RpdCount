#ifndef RPDRECORD_H
#define RPDRECORD_H

#define RPD_CODE 0
#define RPD_INVNUM 1

#define RPD_ZAVKAFVIPUSK 0
#define RPD_ZAVKAFOBESP 1
#define RPD_DEKAN 2
#define RPD_PROREKTOR 3
#define RPD_TITUL 4
#define RPD_TEXT 5
#define RPD_PROF 6
#define RPD_AUTHOR 7

#define FIELDS_SIZE 8

#define RPD_NOTE 10


#include <vector>
#include <string>
#include <iostream>
#include <fstream>


class RpdRecord
{
public:
  RpdRecord();
  int code;
  int invNum;
  std::vector<int> fields;
  std::string note;

  int print();

  friend std::ostream& operator<<(std::ostream &os, const RpdRecord& rr);

};

#endif // RPDRECORD_H
