#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <stdio.h>
#include "RadixTree.h"
#include "provided.h"
#include <string>
#include <vector>
#include <set>
using namespace std;
class AttributeTranslator
{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    set<string> *m_attvalset;
    RadixTree<vector<AttValPair>*>* m_radixtreeaAttVal;
};
#endif /* AttributeTranslator_h */
