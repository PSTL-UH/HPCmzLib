/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "Tolerance.h"
#include "PpmTolerance.h"
#include "AbsoluteTolerance.h"
#include "DoubleRange.h"
#include <regex>
#include <algorithm>

static bool iequals(const std::string& a, const std::string& b) {
        return std::equal(a.begin(), a.end(),
                          b.begin(), b.end(),
                          [](char a, char b) {
                              return tolower(a) == tolower(b);
                          });
}


namespace MzLibUtil {

    
    Tolerance::Tolerance(double value) {
        privateValue = std::abs(value);
    }

    double Tolerance::getValue() const {
        return privateValue;
    }

    Tolerance *Tolerance::ParseToleranceString(const std::string &s) {
#ifdef ORIG
        Match *m = StringRegex->Match(s);
        if (m->Groups[3]->Value->Equals(L"PPM", StringComparison::OrdinalIgnoreCase)) {
#endif
        std::regex StringRegex(R"((\+-|-\+|±)?\s*([\d.]+)\s*(PPM|Absolute))", std::regex_constants::icase);
        std::smatch m;
        std::regex_search(s, m, StringRegex);
        if ( iequals (m[3],"PPM") ) {
            return new PpmTolerance(std::stod(m[2]));
        }
        else {
            return new AbsoluteTolerance(std::stod(m[2]));
       }
    }
}
