#include <iostream>
#include "DAGTask.h"
#include "Taskset.h"
#include "tests.h"
#include "plot_utils.h"

#include <ctime>    

int main(int argc, char **argv){

    if(REPRODUCIBLE) srand (1);
    else srand (time(NULL));

    bool random_creation = false;
    if(argc > 1)
        random_creation = atoi(argv[1]);
        
    std::string taskset_filename = "../demo/taskset_2.yaml";
    if(argc > 2)
        taskset_filename = argv[2];
        

    int n_proc = 4;
    std::vector<int> typed_proc = {4,4};
    Taskset taskset;
    if(random_creation){
        int n_tasks = 2;
        float U_tot = 1;
        GeneratorParams gp;
        gp.configureParams(GenerationType_t::VARYING_N);

        taskset.generate_taskset_Melani(n_tasks, U_tot, n_proc, gp);
    }
    else
        taskset.readTasksetFromYaml(taskset_filename);
    
    std::string dot_command = "";
    for(int i=0; i<taskset.tasks.size();++i){
        std::cout<<taskset.tasks[i]<<std::endl;
        taskset.tasks[i].saveAsDot("test"+std::to_string(i)+".dot");

        //convert dot to png to visualize it
        dot_command = "dot -Tpng test"+std::to_string(i)+".dot > test"+std::to_string(i)+".png";
        system(dot_command.c_str());
    }
    std::cout<<"Taskset utilization: "<<taskset.getUtilization()<<std::endl;
    std::cout<<"Taskset Hyper-Period: "<<taskset.getHyperPeriod()<<std::endl;
    std::cout<<"Taskset max Density: "<<taskset.getMaxDensity()<<std::endl<<std::endl;

    //single DAG tests
    std::cout<<"Single task tests: \n";
    bool constrained_taskset = true;
    bool implicit_taskset = true;
    for(int i=0; i<taskset.tasks.size();++i){
        std::cout<<"\tTask "<<i<<std::endl;
        //constrained
        if(taskset.tasks[i].getDeadline() < taskset.tasks[i].getPeriod()){
            std::cout<< "\t\tBaruah 2012 constrained (GP-FP-EDF): " <<GP_FP_EDF_Baruah2012_C(taskset.tasks[i], n_proc)<<std::endl;
            implicit_taskset = false;
        }

        if(taskset.tasks[i].getDeadline() <= taskset.tasks[i].getPeriod()){
            std::cout<< "\t\tHan 2019 constrained typed(GP-FP): " <<GP_FP_Han2019_C_1(taskset.tasks[i], typed_proc)<<std::endl;
            std::cout<< "\t\tHe 2019 constrained typed(GP-FP): " <<GP_FP_He2019_C(taskset.tasks[i], n_proc)<<std::endl;
        }
        std::cout<< "\t\tBaruah 2012 arbitrary (GP-FP-EDF): "   <<GP_FP_EDF_Baruah2012_A(taskset.tasks[i], n_proc)<<std::endl;
        std::cout<< "\t\tGraham 1969 : "   <<Graham1969(taskset.tasks[i], n_proc)<<std::endl;

        if(taskset.tasks[i].getDeadline() > taskset.tasks[i].getPeriod()){
            constrained_taskset = false;
            implicit_taskset = false;
        }
        
    }

    //taskset tests
    std::cout<<"Taskset tests: \n";


    //arbitrary
    std::cout<< "\tBonifaci 2013 arbitrary (GP-FP-EDF): "   <<GP_FP_EDF_Bonifaci2013_A(taskset, n_proc)<<std::endl;
    std::cout<< "\tBonifaci 2013 arbitrary (GP-FP-DM): "   <<GP_FP_DM_Bonifaci2013_A(taskset, n_proc)<<std::endl;

    //implicit
    if(implicit_taskset){
        std::cout<< "\tLi 2013 implicit (GP-FP-EDF): "   <<GP_FP_EDF_Li2013_I(taskset, n_proc)<<std::endl;
    }

    //constrained
    if(constrained_taskset){
        std::cout<< "\tBonifaci 2013 constrained (GP-FP-DM): "   <<GP_FP_DM_Bonifaci2013_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tQamhieh 2013 constrained (GP-FP-EDF): "   <<GP_FP_EDF_Qamhieh2013_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tBaruah 2014 constrained (GP-FP-EDF): "   <<GP_FP_EDF_Baruah2014_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tMelani 2015 constrained (GP-FP-FTP): "   <<GP_FP_FTP_Melani2015_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tMelani 2015 constrained (GP-FP-EDF): "   <<GP_FP_EDF_Melani2015_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tPathan 2017 constrained (GP-FP-DM): "   <<GP_FP_DM_Pathan2017_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tFonseca 2017 constrained (GP-FP-FTP): "<<GP_FP_FTP_Fonseca2017_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tFonseca 2019 constrained (GP-FP-FTP): "<<GP_FP_FTP_Fonseca2019(taskset, n_proc)<<std::endl;
        std::cout<< "\tHe 2019 constrained (GP-FP-FTP): "<<GP_FP_FTP_He2019_C(taskset, n_proc)<<std::endl;
        std::cout<< "\tSerrano 2016 constrained (GP-LP-FTP): "   <<GP_LP_FTP_Serrano16_C(taskset, n_proc)<<std::endl;
    }

    std::cout<< "\tFonseca 2019 arbitrary (GP-FP-FTP): "<<GP_FP_FTP_Fonseca2019(taskset, n_proc, false)<<std::endl;

}