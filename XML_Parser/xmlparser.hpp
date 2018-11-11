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
    string text;
    string parent;
    vector<string> v;
    string_proccessor sp;
    string Text;
    string fileName;
    bool support_attributes;
    size_t ind;
    XMLParser* xp;
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
    XMLParser* get_new_sub_parent(const string& parent, const string& text)
    {
        XMLParser* xp = new XMLParser;
        string open = "<" + parent + ">";
        string close = "</" + parent + ">";

        xp->sp.setText(text);

        xp->Text = text;
        xp->ind = 0;

        xp->text = sp.get_string_between(open, close);
        try
        {
            xp->check(text=="", "error: couldn't find '" + parent + "' sub-parent");
        }catch(...){
            error("error: couldn't find '" + parent + "' sub-parent"); delete xp;
        }
        xp->v = xp->sp.get_string_between_forward(open, close);
        xp->sp.setText(xp->v[xp->ind]);
        xp->parent = parent;
        return xp;
    }

public:
    explicit XMLParser(const string& parent, const string& fileName, bool support_attrib = false): sp(""),
                                                                                                    fileName(fileName),
                                                                                                   support_attributes(support_attrib)
    {
        xp = nullptr;
        string open;
        if(support_attributes)
            open = "<"+parent;
        else
            open = "<"+parent+">";
        string close = "</"+parent+">";

        string text = load(fileName);
        sp.setText(text);
        this->parent = parent;

        Text = text;

        ind = 0;
        this->text = sp.get_string_between(open, close);
        check(text=="", "error: couldn't find '" + parent + "' parent");
        v = sp.get_string_between_forward(open, close);
        sp.setText(v[ind]);
    }

    void setParent(const string& parent, bool support_attrib = false)
    {
        support_attributes = support_attrib;
        sp.setText(Text);
        string open;
        if(support_attributes)
            open = "<"+parent;
        else
            open = "<"+parent+">";
        this->parent = open;
        string close = "</"+parent+">";
        istringstream is(close);
        is >> close;
        text = sp.get_string_between(open, close);
        check(text=="", "error: couldn't find '" + parent + "' parent");
        v.clear();
        v = sp.get_string_between_forward(open, close);
        ind = 0;
        sp.setText(v[ind]);
    }

    string getString(const string& tag)
    {
        string open = "<" + tag + ">";
        string close = "</" + tag + ">";
        string str = sp.get_string_between(open, close);
        check(str=="", "error: couldn't find '" + tag + "' tag in '" + parent + "'");
        return str;
    }

    int getInt(const string& tag)
    {
        string t = getString(tag);

        istringstream is(t);
        int num = 0;
        is >> num;
        return num;
    }

    long getLong(const string& tag)
    {
        string t = getString(tag);

        istringstream is(t);
        long num = 0;
        is >> num;
        return num;
    }

    bool getBool(const string& tag)
    {
        string t = getString(tag);

        istringstream is(t);
        bool num = 0;
        is >> num;
        return num;
    }

    char getChar(const string& tag)
    {
        string t = getString(tag);

        istringstream is(t);
        char num = 0;
        is >> num;
        return num;
    }

    double getDouble(const string& tag)
    {
        string t = getString(tag);

        istringstream is(t);
        double num = 0;
        is >> num;
        return num;
    }

    float getFloat(const string& tag)
    {
        string t = getString(tag);

        istringstream is(t);
        float num = 0;
        is >> num;
        return num;
    }
    bool next()
    {
        if(ind == v.size()-1)
        {
            return false;
        }
        sp.setText(v[++ind]);
        return true;
    }
    bool prev()
    {
        if(ind == 0)
        {
            return false;
        }
        sp.setText(v[--ind]);
        return true;
    }
    ~XMLParser()
    {
        v.clear();
        if(xp != nullptr)delete xp;
    }
    void setSubParent(const string& parent)
    {
        if(xp != nullptr)
            delete xp;
        string open = "<"+parent+">";
        string close = "</"+parent+">";
        string temp = sp.get_string_between(open, close);
        check(temp=="", "error: couldn't find '" + parent + "' sub-parent in " + this->parent);
        xp = get_new_sub_parent(parent, v[ind]);
    }
    XMLParser* subParent()
    {
        return xp;
    }
};
}

#endif // XMLPARSER

