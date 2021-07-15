#pragma once

#include <cstdint>
#include <string>
#include <string.h>
#include <iostream>

class BinaryPack {
private:
    static const int16_t BinaryPackHeader=0xABCD;
    
public:
    static const int LineStartOffset = sizeof(int16_t)+sizeof(int);

    static size_t PackFloat ( char *buf, const float &val)
    {
        memcpy ( buf, &val, sizeof(float));
        return sizeof(float);
    }
    static size_t UnpackFloat ( char* buf, float &val)
    {
        memcpy (&val, buf, sizeof(float));
        return sizeof(float);
    }
    
    static size_t PackDouble ( char *buf, const double &val)
    {
        memcpy ( buf, &val, sizeof(double));
        return sizeof(double);
    }
    static size_t UnpackDouble ( char *buf, double &val)
    {
        memcpy ( &val, buf, sizeof(double));
        return sizeof(double);
    }

    static size_t PackInt ( char *buf, const int &val)
    {
        memcpy ( buf, &val, sizeof(int));
        return sizeof(int);
    }
    static size_t UnpackInt ( char *buf, int &val)
    {
        memcpy ( &val, buf, sizeof(int));
        return sizeof(int);
    }

    static size_t PackBool ( char *buf, const bool &val)
    {
        memcpy ( buf, &val, sizeof(bool));
        return sizeof(bool);
    }
    static size_t UnpackBool ( char *buf, bool &val)
    {
        memcpy ( &val, buf, sizeof(bool));
        return sizeof(bool);
    }
    
    static size_t PackString ( char *buf, const std::string &val)
    {
        // Copy lenght of string into buffer first ( 2byte int)
        // string contains end of string character.
        int16_t len = val.length()+1;
        memcpy ( buf, &len, sizeof(int16_t) );
        memcpy ( buf+sizeof(int16_t), val.c_str(), len);
        return sizeof(int16_t)+len;
    }

    static size_t UnpackString ( char *buf, std::string &val)
    {
        int16_t len;
        memcpy ( &len, buf, sizeof(int16_t) );

        char tmpbuf[len];
        memcpy ( tmpbuf, buf+sizeof(int16_t), len);
        val = std::string(tmpbuf);
        return sizeof(int16_t)+len;
    }
    
    static std::vector<char *> SplitLines(char *buf, size_t buf_len )
    {
        std::vector<char *> tvec;
        size_t pos=0;
        int16_t header;
        while ( pos < buf_len ) {
            int linelen, retlen;

            char *tpos = &buf[pos];
            tvec.push_back(tpos);
            memcpy(&header, buf+pos, sizeof(int16_t));
            if ( header != BinaryPackHeader ) {
                std::cout <<"Memory corruption detected in BinaryPack::SplitLines\n";
                tvec.clear();
                return tvec;
            }
            retlen = BinaryPack::UnpackInt (buf+pos+sizeof(int16_t), linelen);
            pos += linelen;            
        }
        
        return tvec;
    }

    static void SetLineLength( char *buf, const int &len)
    {
        // Copy first a 2byte header to the beginning  of the line.
        // Allows to identify memory corruption easier.
        memcpy(buf, &BinaryPackHeader, sizeof(int16_t));
        memcpy(buf+sizeof(int16_t), &len, sizeof(int));
    }

    static int GetLineLength( char *buf, int &linelen)
    {
        int retlen;
        int16_t header;
        int pos=0;
        memcpy(&header, buf+pos, sizeof(int16_t));
        if ( header != BinaryPackHeader ) {
            std::cout <<"Memory corruption detected in BinaryPack::GetLineLength\n";
            return -1;
        }
        pos += sizeof(int16_t);
        retlen = BinaryPack::UnpackInt (buf+pos, linelen);
        
        return pos+retlen;
    }
    
};
