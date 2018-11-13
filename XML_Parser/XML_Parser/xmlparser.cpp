#ifndef XMLPARSER_CPP
#define XMLPARSER_CPP
#include "xmlparser.hpp"
namespace XML
{
void XMLParser::setParent(const string &parent)
{
    sp.setText(Text);
    string open = "<"+parent+">";
    string close = "</"+parent+">";

    this->parent = open;
    string text = sp.get_string_between(open, close);
    check(text=="", "error: couldn't find '" + parent + "' parent");
    v.clear();
    v = sp.get_string_between_forward(open, close);
    ind = 0;
    sp.setText(v[ind]);
}

string XMLParser::getString(const string &tag)
{
    string open = "<" + tag + ">";
    string close = "</" + tag + ">";
    string str = sp.get_string_between(open, close);
    check(str=="", "error: couldn't find '" + tag + "' tag in '" + parent + "'");
    return str;
}

int XMLParser::getInt(const string& tag)
{
    string t = getString(tag);

    istringstream is(t);
    int num = 0;
    is >> num;
    return num;
}

long XMLParser::getLong(const string& tag)
{
    string t = getString(tag);

    istringstream is(t);
    long num = 0;
    is >> num;
    return num;
}

bool XMLParser::getBool(const string& tag)
{
    string t = getString(tag);

    istringstream is(t);
    bool num = 0;
    is >> num;
    return num;
}

char XMLParser::getChar(const string& tag)
{
    string t = getString(tag);

    istringstream is(t);
    char num = 0;
    is >> num;
    return num;
}

float XMLParser::getFloat(const string& tag)
{
    string t = getString(tag);

    istringstream is(t);
    float num = 0;
    is >> num;
    return num;
}

double XMLParser::getDouble(const string& tag)
{
    string t = getString(tag);

    istringstream is(t);
    double num = 0;
    is >> num;
    return num;
}


bool XMLParser::next()
{
    if(ind == v.size()-1)
    {
        return false;
    }
    sp.setText(v[++ind]);
    return true;
}

bool XMLParser::prev()
{
    if(ind == 0)
    {
        return false;
    }
    sp.setText(v[--ind]);
    return true;
}

XMLParser* XMLParser::subParent(const string& parent)
{
    if(xp != nullptr)
    {
        delete xp;
    }
    xp = get_sub_parent(parent, v[ind]);
    return xp;
}
}
#endif
