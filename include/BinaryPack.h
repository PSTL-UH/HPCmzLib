#pragma once

#include <cstdint>
#include <string>
#include <string.h>


class BinaryPack {
public:
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
        while ( pos < buf_len ) {
            int linelen, retlen;

            char *tpos = &buf[pos];
            tvec.push_back(tpos);
            retlen = BinaryPack::UnpackInt (buf+pos, linelen);
            pos += linelen;            
        }
        
        return tvec;
    }
    
};
