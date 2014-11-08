#ifndef _xml2cpp_h
#define _xml2cpp_h

struct prop
{
    std::string _propName;
    std::string _propValue;
};

struct nodeBase
{
    std::string _stuctname;
    std::string _membername;
    std::vector<prop *> _pvec;
    std::vector<node *> _nvec;
};

#endif
