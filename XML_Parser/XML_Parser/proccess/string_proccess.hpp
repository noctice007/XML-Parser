#ifndef STRING_PROCCESS
#define STRING_PROCCESS
#include <string>
#include <vector>
using std::vector;
using std::string;
namespace XML::proccess
{
struct string_proccessor
{
private:
    string text;
public:
    explicit string_proccessor(const string& text): text(text){}
    void setText(const string& text)
    {
        this->text = text;
    }
    string getText() const noexcept
    {
        return text;
    }

    string from_to(size_t f, size_t t)
    {
        if(f > text.length() || t > text.length() || f > t)
        {
            return "";
        }
        return text.substr(f, t-f+1);
    }

    string get_string_between(const string& lhs, const string& rhs)
    {
        string t = text;
        size_t from = t.find(lhs);
        if(from == string::npos)
        {
            return "";
        }
        from += lhs.length();
        size_t to = t.find(rhs, from);
        if(to == string::npos)
        {
            return "";
        }
        to--;
        return from_to(from, to);
    }
    string remove_string_from(const string& lhs)
    {
        size_t from = text.find(lhs)+lhs.length();
        size_t to = text.length()-1;
        return from_to(from, to);
    }
    string remove_string_from_to(const string& lhs, const string& rhs)
    {
        size_t from = text.find(lhs);
        size_t to = text.find(rhs);
        if(from >= to || from == string::npos || to == string::npos)
            return "";
        return text.substr(0, from) + text.substr(to+rhs.length());
    }

    vector<string> get_string_between_forward(const string& lhs, const string& rhs)
    {
        vector<string> v;
        string t = text;
        string temp = get_string_between(lhs, rhs);
        while(temp != "")
        {
            v.push_back(temp);
            text = remove_string_from(rhs);
            temp = get_string_between(lhs, rhs);
        }
        text = t;
        return v;
    }
    string insert(const string& lhs, const size_t pos)
    {
        size_t count = 0;
        string t = text;
        size_t i = pos;
        const size_t size = lhs.length();
        if(pos > text.length())
            return "";
        while(count < size)
        {
            t.insert(t.begin()+i, lhs[count++]);
            i++;
        }
        return t;
    }
};
}
#endif // STRING_PROCCESS

