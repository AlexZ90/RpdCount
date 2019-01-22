#ifndef RPDRECORD_H
#define RPDRECORD_H

#define RPD_CODE 0
#define RPD_INVNUM 1

/*List of record fields. Each field is equal 1 if it is necessary to correct it or sign it.*/

#define RPD_ZAVKAFVIPUSK 	0	//Zav. vipusk. kafedri sign
#define RPD_ZAVKAFOBESP 	1	//Zav. obesp. kafedri sign
#define RPD_DEKAN 			2	//Dekan sign
#define RPD_PROREKTOR 		3	//Prorektor sign
#define RPD_TITUL 			4	//titul exists
#define RPD_TEXT 			5	//text exists
#define RPD_PROF 			6	//word 'professional' must be added or deleted for thos document
#define RPD_AUTHOR 			7	//Author sign

#define FIELDS_SIZE 		8	//Number of fields

#define RPD_NOTE 			10	//Note string for document


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
