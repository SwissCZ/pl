#ifndef SETTINGS_HPP
#define	SETTINGS_HPP

#include <iostream>

#include "language.hpp"
#include "notation.hpp"
#include "target.hpp"

struct Settings
{
    Language output_language = ASCII;
    Notation input_notation = INFIX;
    Notation output_notation = INFIX;
    Target target = DEFAULT;
    std::istream * input_stream = &std::cin;

    Settings(int argc, char ** argv);
    ~Settings();
};

#endif	/* SETTINGS_HPP */
