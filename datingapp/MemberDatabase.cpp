#include "MemberDatabase.h"
#include <fstream>
using namespace std;
MemberDatabase::MemberDatabase()
{
    m_AttValPair = new vector<string>;
    m_emailprofile = new RadixTree<PersonProfile*>;
    m_attvalparemail = new RadixTree<vector<string>*>;
    m_emailset = new vector<string>;
}

MemberDatabase::~MemberDatabase()
{
    vector<string>::iterator it1;
    for (it1 = m_emailset -> begin(); it1 != m_emailset -> end(); it1++)
    {
        PersonProfile** profile = m_emailprofile -> search(*it1);
        if (profile != nullptr)
            delete *profile;
        
    }
    vector<string>::iterator it2;
    for (it2 = m_AttValPair -> begin(); it2 != m_AttValPair-> end(); it2++)
    {
        vector<string>** emails = m_attvalparemail -> search(*it2);
        if (emails != nullptr)
            delete *emails;
    }
    delete m_emailset;
    delete m_emailprofile;
    delete m_AttValPair;
    delete m_attvalparemail;
}

bool MemberDatabase::LoadDatabase(string filename)
{
    ifstream datafile(filename);
    if (!datafile)
        return false;
    if (datafile.is_open())
    {
        string name, email, attribute, value, line;
        int numofpairs = 0;
        while (datafile.good())
        {
            getline(datafile, name);
            getline(datafile, email);
            if (m_emailprofile -> search(email) != nullptr)
                return false;
            m_emailset -> push_back(email);
            PersonProfile* insertperson = new PersonProfile(name, email);
            datafile >> numofpairs;
            getline(datafile, line);
            for (int i = 0; i != numofpairs; i++)
            {
                getline(datafile, attribute, ',');
                getline(datafile, value);
                insertperson -> AddAttValPair(AttValPair (attribute, value));
                string pairs = attribute + value;
                vector<string>** emailvec = m_attvalparemail -> search(pairs);
                if (emailvec == nullptr)
                {
                    m_attvalparemail -> insert(pairs, new vector<string>);
                    emailvec = m_attvalparemail->search(pairs);
                    m_AttValPair -> push_back(pairs);
                }
                else
                {
                    (*emailvec) -> push_back(email);
                }
            }
            getline(datafile, line);
            m_emailprofile -> insert(email, insertperson);
        }
    }
    return true;
}

vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    string input_pair = input.attribute + input.value;
    vector<string>** matched = m_attvalparemail -> search(input_pair);
    if (matched != nullptr)
        return **matched;
    return vector<string>();
}

const PersonProfile* MemberDatabase::GetMemberByEmail(string email) const
{
    PersonProfile** profile = m_emailprofile -> search(email);
    if (profile != nullptr)
        return *profile;
    return nullptr;
}

