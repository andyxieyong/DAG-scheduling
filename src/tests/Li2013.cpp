#include "tests.h"

// "Outstanding Paper Award: Analysis of Global EDF for Parallel Tasks" Li et al. (ECRTS 2013) 

/* Corollary 6 in the paper*/
bool G_EDF_Li2013_I(const Taskset& taskset, const int m){
for(const auto& task:taskset.tasks){
        if(!(task.getDeadline() == task.getPeriod()))
            FatalError("This test requires implicit deadline tasks");

        if(task.getLenght() > 1. / ( 4. - 2. / m) * (float) task.getPeriod())
            return false;
    }

    if(taskset.getUtilization() <= m / (4. - 2. / m ))
        return true;
    return false;
}
