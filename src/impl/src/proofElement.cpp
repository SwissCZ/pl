#include "proofElement.hpp"

ProofElement::ProofElement(Formula* formula,
                           list<ProofElement*> witnesses)
{
    this->formula = formula;
    this->witnesses = witnesses;
}

ProofElement::~ProofElement()
{
    delete formula;
}

Formula* ProofElement::getFormula() const
{
    return formula;
}

list<ProofElement*> ProofElement::getWitnesses() const
{
    return witnesses;
}

bool ProofElement::getPreserve() const
{
    return preserve;
}

void ProofElement::setPreserve(bool preserve)
{
    this->preserve = preserve;
}
