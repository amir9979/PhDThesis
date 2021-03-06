#ifndef __JSON_H_ec30169a03d891d55545f6d26609a2cad278e208__
#define __JSON_H_ec30169a03d891d55545f6d26609a2cad278e208__

#include "boost.h"
#include "iostream.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

namespace diagnostic {
class t_json_writable {
public:
    virtual std::ostream & json (std::ostream & out) const = 0;
    inline virtual ~t_json_writable () {}
};


std::ostream & json_write (std::ostream & out,
                           const t_json_writable & w);

std::ostream & json_write (std::ostream & out,
                           const char * i);

std::ostream & json_write (std::ostream & out,
                           const bool & i);

std::ostream & json_write (std::ostream & out,
                           const int & i);

std::ostream & json_write (std::ostream & out,
                           const unsigned int & i);

std::ostream & json_write (std::ostream & out,
                           const long & i);

std::ostream & json_write (std::ostream & out,
                           const double & i);

std::ostream & json_write (std::ostream & out,
                           std::string str);

template <class C>
std::ostream & json_write (std::ostream & out,
                           const std::set<C> & container);

template <class K, class V>
std::ostream & json_write (std::ostream & out,
                           const std::map<K, V> & container);

template <class C>
std::ostream & json_write (std::ostream & out,
                           const std::list<C> & container);

template <class C>
std::ostream & json_write (std::ostream & out,
                           const std::vector<C> & container);

template <class C, class D>
std::ostream & json_write (std::ostream & out,
                           const std::pair<C, D> & p);

template <class T>
std::ostream & json_write (std::ostream & out,
                           const t_const_ptr<T> & c);

template <class C>
std::ostream & json_write_container (std::ostream & out,
                                     const C & container,
                                     std::string lbracket="",
                                     std::string rbracket="") {
    t_group group;


    group.open(out, lbracket, rbracket);
    BOOST_FOREACH(const auto & el, container) {
        group.element(out);
        json_write(out, el);
    }
    group.close(out);

    return out;
}

template <class C>
std::ostream & json_write (std::ostream & out,
                           const std::set<C> & container) {
    return json_write_container(out, container, "[", "]");
}

template <class K, class V>
std::ostream & json_write (std::ostream & out,
                           const std::map<K, V> & container) {
    return json_write_container(out, container, "{", "}");
}

template <class C>
std::ostream & json_write (std::ostream & out,
                           const std::list<C> & container) {
    return json_write_container(out, container, "[", "]");
}

template <class C>
std::ostream & json_write (std::ostream & out,
                           const std::vector<C> & container) {
    return json_write_container(out, container, "[", "]");
}

template <class C, class D>
std::ostream & json_write (std::ostream & out,
                           const std::pair<C, D> & p) {
    json_write(out, p.first);
    out << ':';
    json_write(out, p.second);
    return out;
}

template <class T>
std::ostream & json_write (std::ostream & out,
                           const t_const_ptr<T> & c) {
    if (c)
        json_write(out, *c);
    else
        out << "null";

    return out;
}
}

#endif