#include "papi_utils.h"
#include <vector>


#define N 128
#define BLOCK_SIZE 4
typedef std::vector<std::vector<double>> TwoDVec;

inline void tileCode(TwoDVec& C, TwoDVec& A, TwoDVec& B){
    for (int ii = 0; ii < N; ii += BLOCK_SIZE) {
        for (int jj = 0; jj < N; jj += BLOCK_SIZE) {
            for (int kk = 0; kk < N; kk += BLOCK_SIZE) {
                for (int i = ii; i < ii + BLOCK_SIZE; i ++) {
                    for (int j = jj; j < jj + BLOCK_SIZE; j ++) {
                        for (int k = kk; k < kk + BLOCK_SIZE; k ++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

inline void naiveCode(TwoDVec& C, TwoDVec& A, TwoDVec& B){
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            for (int k = 0; k < N; k ++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void resetArrays(TwoDVec& C, TwoDVec& A, TwoDVec& B){
    for(int i = 0; i < N; i++){
        for( int j = 0; j < N; j++){
            A[i][j] = 5;
            B[i][j] = 5;
            C[i][j] = 0;
        }
    }
}

double computeAvgMemoryAccessLatency(double& L1_DCM, double& L2_DCM, double& L3_TCM, double& LST_INS){
    auto l1_mr = L1_DCM / LST_INS;
    auto l2_mr = L2_DCM / L1_DCM;
    auto l3_mr = L3_TCM / L2_DCM;

    auto l1_access_cost = 4;
    auto l2_access_cost = 14;
    auto l3_access_cost = 68;
    auto mm_access_cost = 79;
    auto avg_mem_cycle = l1_access_cost + l1_mr*(l2_access_cost + l2_mr*(l3_access_cost + l3_mr*mm_access_cost));
    auto avg_mem_latency = avg_mem_cycle * LST_INS;
    return avg_mem_latency;
}

void memoryLatency(){
    TwoDVec A (N, std::vector<double>(N,5));
    TwoDVec B (N, std::vector<double>(N,5));
    TwoDVec C (N, std::vector<double>(N,0));

    int retval;
    std::vector<int> PAPI_EVENTS_CODES{PAPI_L3_TCM, PAPI_L2_DCM, PAPI_L1_DCM, PAPI_LST_INS};
    double L3_TCM, L2_DCM, L1_DCM, LST_INS;
    for(auto& code:PAPI_EVENTS_CODES){
        //================ Initializing the counters and events ===================
        if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT) {
            ERROR_RETURN(retval)
            return;
        }

        long long int event_value;
        int event_set = PAPI_NULL;
        if((retval = PAPI_create_eventset(&event_set)) != PAPI_OK) {
            ERROR_RETURN(retval)
            return;
        }
        if((retval = PAPI_add_event(event_set, code)) != PAPI_OK) {
            ERROR_RETURN(retval)
            return;
        }

        if((retval = PAPI_reset(event_set)) != PAPI_OK){
            ERROR_RETURN(retval)
        }

        if((retval = PAPI_start(event_set)) != PAPI_OK){
            ERROR_RETURN(retval)
        }
        //========================================================================

        //========================== Code to profile =============================
        naiveCode(C, A, B);
        //========================================================================

        //======= Recording the current value from the program counter ========
        if((retval = PAPI_stop(event_set, &event_value)) != PAPI_OK){
            ERROR_RETURN(retval)
        }

        if ( (retval=PAPI_remove_event(event_set, code))!=PAPI_OK){
            ERROR_RETURN(retval)
        }

        if (code == PAPI_L3_TCM){
            L3_TCM = event_value;
        } else if (code == PAPI_L2_DCM){
            L2_DCM = event_value;
        } else if (code == PAPI_L1_DCM){
            L1_DCM = event_value;
        } else if (code == PAPI_LST_INS){
            LST_INS = event_value;
        } else {
            char EventCodeStr[PAPI_MAX_STR_LEN];
            PAPI_event_code_to_name(code, EventCodeStr);
            std::string ret(EventCodeStr);
            std::cerr << "The code "<< ret << " is either invalid or not required." << std::endl;
        }
        //To finish the whole papi initialization
        PAPI_shutdown();
        //========================================================================
    }
    auto avg_mem_latency_block = computeAvgMemoryAccessLatency(L1_DCM, L2_DCM, L3_TCM, LST_INS);
    std::cout << "The naive code average memory latency is: " << avg_mem_latency_block << std::endl;


    for(auto& code:PAPI_EVENTS_CODES){
        //================ Initializing the counters and events ===================
        if((retval = PAPI_library_init(PAPI_VER_CURRENT)) != PAPI_VER_CURRENT) {
            ERROR_RETURN(retval)
            return;
        }

        long long int event_value;
        int event_set = PAPI_NULL;
        if((retval = PAPI_create_eventset(&event_set)) != PAPI_OK) {
            ERROR_RETURN(retval)
            return;
        }
        if((retval = PAPI_add_event(event_set, code)) != PAPI_OK) {
            ERROR_RETURN(retval)
            return;
        }

        if((retval = PAPI_reset(event_set)) != PAPI_OK){
            ERROR_RETURN(retval)
        }

        if((retval = PAPI_start(event_set)) != PAPI_OK){
            ERROR_RETURN(retval)
        }
        //========================================================================

        //========================== Code to profile =============================
        tileCode(C, A, B);
        //========================================================================

        //======= Recording the current value from the program counter ========
        if((retval = PAPI_stop(event_set, &event_value)) != PAPI_OK){
            ERROR_RETURN(retval)
        }

        if ( (retval=PAPI_remove_event(event_set, code))!=PAPI_OK){
            ERROR_RETURN(retval)
        }

        if (code == PAPI_L3_TCM){
            L3_TCM = event_value;
        } else if (code == PAPI_L2_DCM){
            L2_DCM = event_value;
        } else if (code == PAPI_L1_DCM){
            L1_DCM = event_value;
        } else if (code == PAPI_LST_INS){
            LST_INS = event_value;
        } else {
            char EventCodeStr[PAPI_MAX_STR_LEN];
            PAPI_event_code_to_name(code, EventCodeStr);
            std::string ret(EventCodeStr);
            std::cerr << "The code "<< ret << " is either invalid or not required." << std::endl;
        }
        //To finish the whole papi initialization
        PAPI_shutdown();
        //========================================================================
    }
    auto avg_mem_latency_naive = computeAvgMemoryAccessLatency(L1_DCM, L2_DCM, L3_TCM, LST_INS);
    std::cout << "The tile code average memory latency is: " << avg_mem_latency_naive << std::endl;
}

void potentialGain(){

}

int main(int argc, char *argv[])

{
    //Demo 1 - Low-level API - Memory Latency
    memoryLatency();

    //Demo 3 - Low-Level API - Potential Gain
//    potentialGain();

}
