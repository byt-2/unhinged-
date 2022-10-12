#include "AttributeTranslator.h"
#include <iostream>
#include <fstream>
using namespace std;
AttributeTranslator::AttributeTranslator()
{
    m_attvalset = new set<string>;
    m_radixtreeaAttVal = new RadixTree<vector<AttValPair>*>;
}

AttributeTranslator::~AttributeTranslator()
{
    set<string>::iterator it = m_attvalset -> begin();
    while(it != m_attvalset -> end())
    {
        vector<AttValPair>**compatible_vec = m_radixtreeaAttVal -> search(*it);
        if (compatible_vec != nullptr)
            delete *compatible_vec;
        it++;
    }
    delete m_radixtreeaAttVal;
    delete m_attvalset;
}

bool AttributeTranslator::Load(string filename)
{
    ifstream translate(filename);
    if (!translate)
        return false;
    if (translate.is_open())
    {
        string source_attribute,source_value,compatible_attribute,compatible_value;
        while (translate.good())
            {
                getline(translate,source_attribute, ',');
                getline(translate,source_value, ',');
                getline(translate,compatible_attribute, ',');
                getline(translate,compatible_value);
                string source_file = source_attribute + source_value;
                AttValPair  compatible_attval(compatible_attribute, compatible_value);
                vector<AttValPair>**compatible_vec = m_radixtreeaAttVal -> search(source_file);
                if (compatible_vec == nullptr)
                {
                    m_radixtreeaAttVal -> insert(source_file, new vector<AttValPair>);
                    compatible_vec = m_radixtreeaAttVal->search(source_file);
                    m_attvalset -> insert(source_file);
                }else
                {
                (*compatible_vec) -> push_back(compatible_attval);
                }
            }
    }
    return true;
}

vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    string sourcepairs = source.attribute + source.value;
    vector<AttValPair>** compatible_vec = m_radixtreeaAttVal -> search(sourcepairs);
    if (compatible_vec != nullptr)
        return **compatible_vec;
    return vector<AttValPair>();
}
