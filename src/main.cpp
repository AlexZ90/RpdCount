#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include "commonFunctions.h" 
#include "RpdRecord.h"

using namespace std;

int readDatabase (std::fstream &fs, std::unordered_map<int,RpdRecord> &records);
int writeDatabase (std::fstream &fs, std::unordered_map<int,RpdRecord> &records);

int main(int argc, char *argv[])
{

    std::fstream fs;
    std::string databaseFilePath = "rpdCount_database.txt";
    std::string line;
    int startNum = 0;
    std::unordered_map<int,RpdRecord> records;

    if (argc > 1)
    {
        databaseFilePath = argv[1];
    }
    else
    {
        std::cout <<  "using: rpdCount rpdCount_database.txt" << std::endl;
        exit -1;
    }

    fs.open (databaseFilePath, std::fstream::in | std::fstream::out);

    if (!fs.is_open())
    {
        std::cout << "Error while opening file: " << databaseFilePath << std::endl;
        return -1;
    }

    while ( std::getline(fs,line))
    {
      if (line.find("[start_num]") != std::string::npos)
      {
        std::getline(fs,line);
        startNum = std::atoi(line.c_str());
        std::cout << "startNum = " << startNum << std::endl;
        break;
      }
    }

    while (std::getline(fs,line))
    {
      if (line.find("[records]") != std::string::npos)
      {
        std::cout << "records found" << std::endl;
        break;
      }
    }

    records.clear();
    readDatabase(fs,records);

    for (std::unordered_map<int, RpdRecord>::iterator it = records.begin(); it != records.end(); ++it)
    {
        std::cout << (*it).second << std::endl;
    }

    fs.close();

    std::string str;

    bool exists = false;

    while (1)
    {
        
        RpdRecord rr;
        std::cout << endl;
        std::cout << "Enter the code: ";
        getline(std::cin,str);

        if (str == "q")
            break;
        else if (str.length() == 0)
        {
            std::cout << "Enter the code" << std::endl;
            continue;
        }

        rr.code = std::stoi(str);

        std::unordered_map<int,RpdRecord>::iterator got = records.find (rr.code);

        if ( got != records.end() )
        {
            rr = got->second;
            exists = true;
            std::cout << endl;
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Exists:" << std::endl;
            std::cout << std::endl;
            rr.print();
            std::cout << endl;
        }
        else
        {
            rr.invNum = startNum++;
        }

        if (str == "q")
        {   
            std::cout << "exit without saving" << std::endl;
            startNum--;
            break;
        }
        else if (str == "wq")
        {   
            records[rr.code] = rr;
            std::cout << "exit with saving" << std::endl;
            break;
        }


        std::cout << std::endl;
        std::cout << "ZavKafVipusk (" << RPD_ZAVKAFVIPUSK << ")" <<   std::endl;
        std::cout << "ZavKafObesp (" << RPD_ZAVKAFOBESP << ")" <<   std::endl;
        std::cout << "Dekan (" << RPD_DEKAN << ")" <<   std::endl;;
        std::cout << "Prorektor (" << RPD_PROREKTOR << ")" <<   std::endl;
        std::cout << "Titul (" << RPD_TITUL << ")" <<   std::endl;
        std::cout << "Text (" << RPD_TEXT << ")" <<   std::endl;
        std::cout << "Prof (" << RPD_PROF << ")" <<   std::endl;
        std::cout << "Author (" << RPD_AUTHOR << ")" <<   std::endl;
        std::cout << "Enter fields: ";
        getline(std::cin,str);

        if (str == "q")
        {   
            std::cout << "exit without saving" << std::endl;
            startNum--;
            break;
        }
        else if (str == "wq")
        {   
            records[rr.code] = rr;
            std::cout << "exit with saving" << std::endl;
            break;
        }

        std::vector<int> new_fields;

        for (unsigned int i = 0; i < str.length(); i++)
        {
            int num = str[i] - '0';
            if (num < FIELDS_SIZE)
            {
                rr.fields[num] = ~(rr.fields[num]) & 1;
            }
            else 
            {
                std::cout << "Error in booleans" << std::endl;
                break;
            }
        }

        std::cout << "Enter note: ";
        getline(std::cin,str);

        if (str == "q")
        {   
            std::cout << "exit without saving" << std::endl;
            startNum--;
            break;
        }
        else if (str == "wq")
        {   
            records[rr.code] = rr;
            std::cout << "exit with saving" << std::endl;
            break;
        }

        rr.note = rr.note + str;
        records[rr.code] = rr;

        std::cout << rr << std::endl;
    }


    fs.open (databaseFilePath, std::fstream::in | std::fstream::out | std::fstream::trunc);

    if (!fs.is_open())
    {
        std::cout << "Error while opening file: " << databaseFilePath << std::endl;
        return -1;
    }

    fs << "[start_num]" << std::endl;
    fs << startNum << std::endl << std::endl;

    fs << "[records]" << std::endl;
    writeDatabase(fs,records);

    fs.close();

    return 0;
}

int readDatabase (std::fstream &fs, std::unordered_map<int,RpdRecord> &records)
{
    std::string line;
    std::vector <std::string> splitResult;
    RpdRecord rr;

    while ( std::getline(fs,line))
    {
        if (line.size() == 0)
            continue;

        RpdRecord rr;
        common::split(line,";",splitResult);
        // for (unsigned int i = 0; i < splitResult.size(); i++)
        //     std::cout << splitResult[i] << " ";
        // std::cout << std::endl;
        rr.code = std::atoi(splitResult[RPD_CODE].c_str());
        rr.invNum = std::atoi(splitResult[RPD_INVNUM].c_str());
        
        for (unsigned int i = 0; i < FIELDS_SIZE; i++)
            rr.fields[i] = std::stoi(splitResult[i+2]); //2 - code + inv_num

        if (splitResult.size() == (RPD_NOTE + 1)) //note presents
        {
            rr.note = splitResult[RPD_NOTE];
        }
        else
            rr.note = "";

        records[rr.code] = rr;
    }

    return 1;
}

int writeDatabase (std::fstream &fs, std::unordered_map<int,RpdRecord> &records)
{

    for (std::unordered_map<int, RpdRecord>::iterator it = records.begin(); it != records.end(); ++it)
    {
        fs << (*it).second << std::endl;
    }

    return 1;
}
