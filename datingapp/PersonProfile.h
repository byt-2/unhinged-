#ifndef PersonProfile_h
#define PersonProfile_h

#include <stdio.h>
#include <iostream>
#include <string>
#include "provided.h"
#include "RadixTree.h"
#include <vector>
using namespace std;
class PersonProfile
{
public:
PersonProfile(string name, string email);
string GetName() const;
string GetEmail() const;
void AddAttValPair(const AttValPair& attval);
int GetNumAttValPairs() const;
bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    string m_name;
    string m_email;
    int m_numAttValPairs;
    vector<AttValPair> m_AttValPair;
    RadixTree<string> m_radixtreeaAttVal;
};
inline
string PersonProfile::GetName() const
{
    return m_name;
}

inline
string PersonProfile::GetEmail() const
{
    return m_email;
}


#endif /* PersonProfile_h */
