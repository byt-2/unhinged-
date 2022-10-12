#include "MatchMaker.h"
#include <map>
#include <set>
using namespace std;
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    m_mdb = &mdb;
    m_at = &at;
}

bool comp(const EmailCount& ec1, const EmailCount& ec2)
{
    if (ec1.count > ec2.count)
        return true;
    if (ec2.count > ec1.count)
        return false;
    return ec2.email > ec1.email;
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const
{
    const PersonProfile* profile = m_mdb -> GetMemberByEmail(email);
    vector<AttValPair> match;
    for (int i = 0; i < profile->GetNumAttValPairs(); i++)
    {
        AttValPair attvalpair;
        profile -> GetAttVal(i, attvalpair);
        vector<AttValPair> compatiblevec = m_at -> FindCompatibleAttValPairs(attvalpair);
        vector<AttValPair>::iterator it1 = compatiblevec.begin();
        while (it1 != compatiblevec.end())
        {
            match.push_back(*it1);
            it1++;
        }
    }
    map<string, int> emailset;
    vector<AttValPair>::iterator it2 = match.begin();
    while(it2 != match.end())
    {
        vector<string> emailsmatched = m_mdb -> FindMatchingMembers(*it2);
        vector<string>::iterator it3 = emailsmatched.begin();
        while (it3 != emailsmatched.end())
        {
            if (*it3 != profile -> GetEmail())
                emailset[*it3]++;
            it3++;
        }
        it2++;
    }
    vector<EmailCount> matched;
    map<string, int>::iterator it4 = emailset.begin();
    while (it4 != emailset.end())
    {
        if (it4->second >= threshold)
            matched.push_back(EmailCount(it4 -> first, it4 -> second));
        it4++;
    }
    sort(matched.begin(), matched.end(), comp);
    return matched;
}
