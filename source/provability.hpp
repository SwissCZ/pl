#ifndef PROVABILITY_HPP
#define	PROVABILITY_HPP

#include <string>

using namespace std;

//! Modus ponens provability.

/**
 * Modus ponens formula provability validation result.
 */
class Provability
{
private:
    bool provability; ///< Modus ponens formula provability.
public:
    Provability(bool);
    /**
     * Modus ponens formula provability getter.
     * @return Modus ponens formula provability.
     */
    bool getProvability() const;
    /**
     * Composes a formula provability validation message.
     * @return Formula provability validation message.
     */
    virtual string getMessage() const = 0;
};

//! Modus-ponens-provable result.

/**
 * Formula is provable using modus ponens rule.
 */
class ProvableResult : public Provability
{
private:
    int premise; ///< Used premise formula ('A') order.
    int implication; ///< Used implication formula ('A>B') order.
public:
    ProvableResult(int, int);
    virtual string getMessage() const;
};

//! Modus-ponens-inprovable result.

/**
 * Formula is not provable using modus ponens rule.
 */
class InprovableResult : public Provability
{
public:
    InprovableResult();
    virtual string getMessage() const;
};

#endif	/* PROVABILITY_HPP */
