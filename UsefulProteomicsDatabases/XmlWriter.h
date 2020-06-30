/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#ifndef XmlWriter_H
#define XmlWriter_H

/* The source code for XMLWriter is inspired by two posts on codereview.stackexchange.com:
   https://codereview.stackexchange.com/questions/67594/xml-writer-in-c-updated?noredirect=1&lq=1
   (including the second review posted there) 
   
   and
   
   https://codereview.stackexchange.com/questions/67334/basic-xml-writer-in-c

  This implmentation uses bits and pieces from all three solutions to match what we need 
  for this code.
*/   
   

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class XmlWriter
{
    
public:
    XmlWriter(std::string fileName);
    void Close();
    bool exists(std::string);
    bool isOpen();
    void WriteStartDocument();
    void WriteEndDocument();
    void WriteStartElement(std::string);
    void WriteEndElement();
    void WriteAttributeString(std::string, std::string);
    void WriteString(std::string);

private:
    std::vector<std::string> tagStack;
    std::ofstream outFile;
    std::string xmlEncode="utf-8";
    int current_indent;
    int increment_indent=2;
    bool startDocument;
    bool docWrite;
    bool elementOpen;
    bool stringWritten;
    bool needNewLine;
    bool doIndent;
    
};

#endif
