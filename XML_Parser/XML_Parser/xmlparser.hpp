#ifndef XMLPARSER
#define XMLPARSER

#include <sstream>
#include "proccess/string_proccess.hpp"
#include "errors.hpp"
#include <fstream>
using std::ifstream;
using std::istringstream;
using namespace XML::proccess;
using XML::Error::error;
namespace XML
{
class XMLParser
{
    string parent;
    vector<string> v;
    string_proccessor sp;
    string Text;
    string fileName;
    XMLParser* xp = nullptr;
    size_t ind;

    void check(const bool exp, const string& err_msg)
    {
        if(exp)
        {
            error(err_msg);
        }
    }
    string load(const string& fileName)
    {
        string temp;
        string text = "";
        ifstream in(fileName);
        check(!in.is_open(), "error: faild to open '" + fileName + "' file");
        while(!in.eof())
        {
            getline(in, temp);
            text += temp;
        }
        in.close();
        return text;
    }
    XMLParser(): sp(""){}
    XMLParser* get_sub_parent(const string& parent, const string& text)
    {
        string open = "<" + parent + ">";
        string close = "</" + parent + ">";
        XMLParser* xp = new XMLParser;
        xp->sp.setText(text);

        xp->Text = text;
        xp->ind = 0;

        xp->v = xp->sp.get_string_between_forward(open, close);
        xp->sp.setText(xp->v[xp->ind]);
        xp->parent = parent;
        return xp;
    }

public:
    explicit XMLParser(const string& parent, const string& fileName): sp(""),
                                                                      fileName(fileName)
    {
        Text = load(fileName);
        setParent(parent);
    }

    void setParent(const string& parent);

    string getString(const string& tag);

    int getInt(const string& tag);

    long getLong(const string& tag);

    bool getBool(const string& tag);

    char getChar(const string& tag);

    double getDouble(const string& tag);

    float getFloat(const string& tag);

    bool next();

    bool prev();

    XMLParser* subParent(const string& parent);

    ~XMLParser()
    {
        v.clear();
        if(xp != nullptr)delete xp;
    }
};
}
#include "xmlparser.cpp"
#endif // XMLPARSER
