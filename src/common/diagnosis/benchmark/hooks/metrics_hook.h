#ifndef __METRICS_HOOK_H_0b0885703861f344448f13adf9cea1633b73bc5c__
#define __METRICS_HOOK_H_0b0885703861f344448f13adf9cea1633b73bc5c__

#include "diagnosis/benchmark/hooks/benchmark_hook.h"
#include "diagnosis/benchmark/metrics.h"


namespace diagnosis {
namespace benchmark {
class t_metrics_hook : public t_benchmark_hook {
public:
    t_metrics_hook & operator << (t_ptr<t_metric> & metric);
    t_metrics_hook & operator << (t_metric * metric);

    virtual void trigger_event (t_collector & collector,
                                const t_status_post_rank & status) const;

private:
    typedef std::list < t_ptr < t_metric >> t_metrics_list;
    t_metrics_list metrics_list;
};
}
}

#endif