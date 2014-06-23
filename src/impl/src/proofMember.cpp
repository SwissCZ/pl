#include "proofMember.hpp"

ProofMember::ProofMember(Formula* formula,
                         list<ProofMember*> witnesses)
: formula(formula), witnesses(witnesses)
{
}

ProofMember::~ProofMember()
{
    delete formula;
}

Formula* ProofMember::getFormula() const
{
    return formula;
}

const list<ProofMember*>& ProofMember::getWitnesses() const
{
    return witnesses;
}

bool ProofMember::getPreserve() const
{
    return preserve;
}

void ProofMember::setPreserve(bool preserve)
{
    this->preserve = preserve;
}
