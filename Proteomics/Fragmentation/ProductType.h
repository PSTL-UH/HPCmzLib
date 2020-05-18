#pragma once

#include <string>

namespace Proteomics
{
    namespace Fragmentation
    {
        enum class ProductType
        {
            //Ion Type      Neutral Mr
            //a             [N]+[M]-CHO
            //a*	        a-NH3
            //a�	        a-H2O
            //b             [N]+[M]-H
            //b*	        b-NH3
            //b�	        b-H2O
            //c             [N]+[M]+NH2
            //d             a � partial side chain
            //v             y � complete side chain
            //w             z � partial side chain
            //x             [C]+[M]+CO-H
            //y             [C]+[M]+H
            //y*	        y-NH3
            //y�	        y-H2O
            //z             [C]+[M]-NH2

            a,
            aStar,
            aDegree,
            b,
            bStar,
            bDegree,
            //BnoB1ions,
            c,
            x,
            y,
            yStar,
            yDegree,
            zPlusOne, //This is zDot plus H
            zDot,
            M, //this is the molecular ion
            D //this is a diagnostic ion
        };

        static std::string ProductTypeToString(ProductType &t)
        {
            std::string s;

            if ( t == ProductType::a )
                s = "a";
            else if ( t == ProductType::aStar )
                s = "aStar";
            else if ( t == ProductType::aDegree )
                s = "aDegree";
            else if ( t == ProductType::b )
                s = "b";
            else if ( t == ProductType::bStar )
                s = "bStar";
            else if ( t == ProductType::bDegree )
                s = "bDegree";
            else if ( t == ProductType::c )
                s = "c";
            else if ( t == ProductType::x )
                s = "x";
            else if ( t == ProductType::y )
                s = "y";
            else if ( t == ProductType::yStar )
                s = "yStar";
            else if ( t == ProductType::yDegree )
                s = "yDegree";
            else if ( t == ProductType::zPlusOne )
                s = "zPlusOne";
            else if ( t == ProductType::zDot )
                s = "zDot";
            else if ( t == ProductType::M )
                s = "M";
            else if ( t == ProductType::D )
                s = "D";

            return s;
        }
    }
}
