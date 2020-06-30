/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include <experimental/filesystem>
#include "XmlWriter.h"


XmlWriter::XmlWriter(std::string fileName)
{
    if (!( std::experimental::filesystem::exists(fileName))) {
        outFile.open(fileName);
        if (outFile.is_open()) {
            //std::cout << "File created successfully.\n";
            current_indent = 0;
            startDocument = false;
            docWrite = false;
            elementOpen = false;
            stringWritten = false;
            needNewLine=true;
            doIndent = true;
        }
    }
    //else {
    //   std::cerr << "File already exists.\n";
    //}
}

void XmlWriter::WriteStartDocument()
{
    if (!startDocument) {
        startDocument = true;
        docWrite = true;
    }
}


void XmlWriter::WriteEndDocument()
{
    if (startDocument) {
        startDocument   = false;
        docWrite        = false;
    }
}

bool XmlWriter::isOpen() {
    if (outFile.is_open()) {
        return true;
    }
    return false;
}


void XmlWriter::Close()
{
    if (!startDocument) {
        outFile.close();
    }
}

void XmlWriter::WriteStartElement(std::string elementTag)
{
    if (startDocument) {
        outFile << "<!--XML Document-->\n";
        outFile << "<?xml version='1.0' encoding='" << xmlEncode << "'?>";
        startDocument = false;
    }
    if (docWrite) {
        if ( elementOpen ) {
            outFile << ">";
        }
        if ( needNewLine)  {
            outFile << "\n";
        }
        needNewLine = true;
        for (int i = 0; i < current_indent; i++) {
            outFile << " ";
        }
        outFile << "<" << elementTag;
        
        tagStack.push_back(elementTag);
        current_indent += increment_indent;

        elementOpen     = true;
        stringWritten   = false;
    }
}

void XmlWriter::WriteEndElement()
{
    if (docWrite) {
        if (!(tagStack.empty())) {
            current_indent -= increment_indent;
            if ( elementOpen ) {
                outFile << " />";
            }
            else {
                if ( doIndent) {
                    for (int i = 0; i < current_indent; i++) {
                        outFile << " ";
                    }
                }
                outFile << "</" << tagStack.back() << ">";
            }
        }
        outFile << "\n";
        needNewLine=false;
        doIndent = true;
        tagStack.pop_back();
        
        elementOpen     = false;
        stringWritten   = false;
    }
    else {
        std::cerr << "No tags to close.";
    }
    
}

void XmlWriter::WriteAttributeString(std::string outAttribute, std::string outVal)
{
    if (docWrite && elementOpen ) {
        outFile << " " << outAttribute << "=\"" << outVal << "\"";        
    }
}


void XmlWriter::WriteString(std::string outString)
{
    if (docWrite && elementOpen) {
        outFile << ">" << outString;
        stringWritten = true;
        elementOpen = false;
        doIndent = false;
    }
}

