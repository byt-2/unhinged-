#include "PersonProfile.h"
PersonProfile::PersonProfile(string name, string email)
{
    m_name = name;
    m_email = email;
    m_numAttValPairs = 0;
}

void PersonProfile::AddAttValPair(const AttValPair &attval)
{
    vector<AttValPair>::iterator it = m_AttValPair.begin();
    if (m_numAttValPairs == 0)
    {
        m_AttValPair.push_back(attval);
        m_numAttValPairs++;
        return;
    }
    while (it != m_AttValPair.end())
    {
        if (*it == attval)
        {
            return;
        }
        it++;
    }
    m_AttValPair.push_back(attval);
    m_numAttValPairs++;
    m_radixtreeaAttVal.insert(attval.attribute,attval.value);
    return;
}

int PersonProfile::GetNumAttValPairs() const
{
    return m_numAttValPairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
   if (attribute_num < 0 || attribute_num >= m_numAttValPairs)
   {
       return false;
   }
    vector<AttValPair>::const_iterator it = m_AttValPair.begin();
    for (int i = 0; i < attribute_num; i++)
    {
        if (it != m_AttValPair.end())
        {
            it++;
        }
    }
    if (it == m_AttValPair.end())
    {
        return false;
    }
    attval = *it;
    return true;
}

