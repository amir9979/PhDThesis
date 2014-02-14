#include "hook_combiner.h"

#include "utils/time.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost;

namespace diagnosis {
namespace benchmark {
void t_hook_combiner::trigger_event (t_collector & collector,
                                     const randomizers::t_system & system) const {
    t_path file = collector.global_path("hooks.csv");
    t_entry entry;


    entry["type"] = "system_init";
    entry["start"] = lexical_cast<std::string> (time_interval());

    BOOST_FOREACH(t_benchmark_hook::t_ptr hook, hook_list) {
        hook->trigger_event(collector, system);
    }

    entry["end"] = lexical_cast<std::string> (time_interval());
    collector.add_entry(file, entry);
}

void t_hook_combiner::trigger_event (t_collector & collector,
                                     const t_status_iteration_init & status) const {
    t_path file = collector.global_path("hooks.csv");
    t_entry entry;


    entry["type"] = "iteration_init";
    entry["start"] = lexical_cast<std::string> (time_interval());

    BOOST_FOREACH(t_benchmark_hook::t_ptr hook, hook_list) {
        hook->trigger_event(collector, status);
    }

    entry["end"] = lexical_cast<std::string> (time_interval());
    collector.add_entry(file, entry);
}

void t_hook_combiner::trigger_event (t_collector & collector,
                                     const t_status_post_gen & status) const {
    t_path file = collector.global_path("hooks.csv");
    t_entry entry;


    entry["type"] = "post_gen";
    entry["start"] = lexical_cast<std::string> (time_interval());
    BOOST_FOREACH(t_benchmark_hook::t_ptr hook, hook_list) {
        hook->trigger_event(collector, status);
    }

    entry["end"] = lexical_cast<std::string> (time_interval());
    collector.add_entry(file, entry);
}

void t_hook_combiner::trigger_event (t_collector & collector,
                                     const t_status_post_rank & status) const {
    t_path file = collector.global_path("hooks.csv");
    t_entry entry;


    entry["type"] = "post_rank";
    entry["start"] = lexical_cast<std::string> (time_interval());
    BOOST_FOREACH(t_benchmark_hook::t_ptr hook, hook_list) {
        hook->trigger_event(collector, status);
    }

    entry["end"] = lexical_cast<std::string> (time_interval());
    collector.add_entry(file, entry);
}

t_hook_combiner & t_hook_combiner::operator << (t_benchmark_hook * hook) {
    hook_list.push_back(t_benchmark_hook::t_ptr(hook));
    return *this;
}

t_hook_combiner & t_hook_combiner::operator << (t_benchmark_hook::t_ptr & hook) {
    hook_list.push_back(hook);
    return *this;
}
}
}