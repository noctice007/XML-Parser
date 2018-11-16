#ifndef XMLPARSER
#define XMLPARSER

#include <sstream>
#include <fstream>
#include <memory>

#include "proccess/string_proccess.hpp"

#include "errors.hpp"

using std::unique_ptr;
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
    unique_ptr<XMLParser>xp;
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

    unique_ptr<XMLParser> get_sub_parent(const string& parent, const string& text)
    {
        string open = "<" + parent + ">";
        string close = "</" + parent + ">";

        string t = sp.get_string_between(open, close);
        check(t=="", "couldn't find '" + parent + "' sub-parent");

        unique_ptr<XMLParser>xp(new XMLParser);
        xp->sp.setText(text);

        xp->Text = text;
        xp->ind = 0;

        xp->v = xp->sp.get_string_between_forward(open, close);
        xp->sp.setText(xp->v[xp->ind]);
        xp->parent = parent;
        return xp;
    }
    unique_ptr<XMLParser> get_sub_parent(const string& parent, const string& attrib,
                              const string& text)
    {
        string open = "<" + parent + " " + attrib + ">";
        string close = "</" + parent + ">";
        string t = sp.get_string_between(open, close);
        check(t=="", "couldn't find '" + parent + "' sub-parent");
        unique_ptr<XMLParser>xp(new XMLParser);
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
    explicit XMLParser(const string& parent, const string& attrib, const string& fileName): sp(""),
        fileName(fileName)
    {
        Text = load(fileName);
        setParent(parent, attrib);
    }

    void setParent(const string& parent);
    void setParent(const string& parent, const string& attrib);

    string getString(const string& tag);
    string getString(const string& tag, const string& attrib);

    int getInt(const string& tag);
    int getInt(const string& tag, const string& attrib);

    long getLong(const string& tag);
    long getLong(const string& tag, const string& attrib);

    bool getBool(const string& tag);
    bool getBool(const string& tag, const string& attrib);

    char getChar(const string& tag);
    char getChar(const string& tag, const string& attrib);

    double getDouble(const string& tag);
    double getDouble(const string& tag, const string& attrib);

    float getFloat(const string& tag);
    float getFloat(const string& tag, const string& attrib);


    bool next();

    bool prev();

    unique_ptr<XMLParser> subParent(const string& parent);
    unique_ptr<XMLParser> subParent(const string& parent, const string& attrib);

    ~XMLParser()
    {
        v.clear();
    }
};
}
#include "xmlparser.cpp"
#endif // XMLPARSER
