//
//  DataTable.hpp
//  vlsi_programs_mac
//
//  Created by Spencer Millican on 1/31/18.
//  Copyright © 2018 Spencer Millican. All rights reserved.
//

#ifndef DataTable_hpp
#define DataTable_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

//This data table class is made for storing and easily printing out a table of data.
//All data points will be represented as a float.
class DataTable{
public:
    //Create an empty data table.
    DataTable();
    
    //Add a column in the data table. Return false if the column already exists.
    bool AddColumn(std::string _c) ;
    
    //Add a row to the data table. Returns an iterator to the row.
    unsigned long AddRow(std::string _r) ;
    
    //Add an entry with a given row, column, and data point to the table. Return false if the data point already exists.
    void Add(std::string _r, std::string _c, float _d) ;
    
    //Print the data table
    void Print();
    //Print the columns of the data table.
    void PrintColumns();
    
private:
    //A list of current columns.
    std::vector<std::string> columns_ ;
    
    //A list of current rows. The index of the entry cordinates to the row number for data.
    std::vector<std::string> rows_ ;
    
    //All current data points. Each vector entry is a row. Each row may contain the data (of it exists).
    std::vector<std::map<std::string, float> > data_ ;
    
};

#endif /* DataTable_hpp */
