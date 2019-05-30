//
//  DataTable.cpp
//  vlsi_programs_mac
//
//  Created by Spencer Millican on 1/31/18.
//  Copyright © 2018 Spencer Millican. All rights reserved.
//

#include "DataTable.hpp"

#include <algorithm> //Find

DataTable::DataTable(){
    
}

bool DataTable::AddColumn(std::string _c) {
    std::vector<std::string>::iterator it = std::find(columns_.begin() , columns_.end(), _c) ;
    if ( it != columns_.end() ) { //Column already exists.
        return false ;
    }
    columns_.push_back( _c ) ;
    return true ;
}

//Add a row to the data table. Return false if the row already exists.
unsigned long DataTable::AddRow(std::string _r) {
    std::vector<std::string>::iterator it = std::find(rows_.begin() , rows_.end() , _r ) ;
    if (it != rows_.end() ) { //Row already exists.
        return it - rows_.begin() ;
    }
    rows_.push_back( _r ) ;
    data_.push_back( std::map<std::string , float>() ) ;
    return rows_.size() - 1 ;
}

//Add an entry with a given row, column, and data point to the table. Return false if the data point already exists.
void DataTable::Add(std::string _r, std::string _c, float _d){
    this->AddColumn( _c );
    unsigned long index = this->AddRow( _r );
    data_.at(index)[_c] = _d ;
}

//Print the data table
void DataTable::Print(){
    this->PrintColumns() ;
    for ( unsigned long i = 0; i < rows_.size() ; i++ ) {
        printf( "%s\t" , rows_.at(i).c_str() ) ;
        for ( unsigned long c = 0 ; c < columns_.size() ;  c++ ) {
            std::string columnName = columns_.at(c) ;
            std::map<std::string , float >::iterator it = data_.at(i).find(columnName);
            if (it != data_.at(i).end()) {
                printf("%f\t", data_.at(i).find(columnName)->second) ;
            } else {
                printf( "N/A\t" ) ;
            }
        }
        printf( "\n" ) ;
    }
}
void DataTable::PrintColumns(){
    printf("Entry\t") ;
    for ( std::string column : columns_ ) {
        printf("%s\t", column.c_str() ) ;
    }
    printf("\n");
}
