#include "main.h"

#include "../configuration/configuration.h"
#include "../diagnostic_report.h"
#include "../json.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;
using boost::property_tree::ptree_bad_path;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using namespace std;
using namespace diagnostic;
using namespace diagnostic::configuration;


void run_diagnostic (const ptree & pt,
                     char ** response) {

    t_const_ptr<t_diagnostic_system> dj = construct_diagnostic_system (pt.get_child("system"));
    cout << *dj << std::endl;


    t_diagnostic_report dr(dj);
    t_trie * D;

    D = new t_trie();
    D->add(t_candidate(1,2,3,45,0));
    D->add(t_candidate(2,3,4,0));
    D->add(t_candidate(8,3,4,0));
    dr.add(0, t_const_ptr<t_trie> (D));


    D = new t_trie();
    D->add(t_candidate(1,9,3,4,0));
    D->add(t_candidate(4,3,5,0));
    D->add(t_candidate(8,7,4,0));
    dr.add(1, t_const_ptr<t_trie> (D));

    t_ptr<t_candidate_ranker::t_ret_type> scores(new t_candidate_ranker::t_ret_type()) ;
    scores->push_back(0.25);
    scores->push_back(0.25);
    scores->push_back(0.5);

    dr.add(0, scores);
    dr.add(1, scores);
    dr.add(2, scores);

    stringstream ss;
    json_write(ss, dr) << std::endl << "-------------" << std::endl;

    *response = strdup(ss.str().c_str());
}


void run (const char * request,
          char ** response) {

    ptree pt;
    stringstream ss (request);

    read_json (ss, pt);

    string request_type = pt.get<string>("type", string());
    cout << request << std::endl;

    if(request_type == "diagnostic")
        return run_diagnostic(pt, response);

}

void cleanup(char * response) {
    free(response);
}