#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"
#include <string>
#include <vector>
using namespace std;

class MemberDatabase
{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(string filename);
    vector<string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(string email) const;
private:
    vector<string> *m_AttValPair;
    RadixTree<PersonProfile*> *m_emailprofile;
    RadixTree<vector<string>*> *m_attvalparemail;
    vector<string> *m_emailset;    
};
#endif /* MemberDatabase_h */
