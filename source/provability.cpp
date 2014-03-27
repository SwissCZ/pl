#include "provability.hpp"

#include <sstream>

using namespace std;

Provability::Provability(bool validity) : provability(validity)
{
}

bool Provability::getProvability() const
{
    return provability;
}

ProvableResult::ProvableResult(int premise, int implication)
: Provability(true), premise(premise), implication(implication)
{
}

string ProvableResult::getMessage() const
{
    stringstream stream;
    stream << "Provable using the premise " << premise << " and the implication "
            << implication << ".";
    return stream.str();
}

InprovableResult::InprovableResult() : Provability(false)
{
}

string InprovableResult::getMessage() const
{
    return string() + "Inprovable within the proof.";
}
