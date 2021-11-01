#include <cmath>
#include <cstdlib>
#include <vector>

#include "papi_utils.h"


const int NUM_LOOP = 1000000;

typedef double real_t;
// typedef double real_t;

template<typename T> inline T sqrtx(T v);
template<> inline float sqrtx<float>(float v) { return sqrtf(v); }
template<> inline double sqrtx<double>(double v) { return sqrt(v); }

int main() {
  int ret = PAPI_library_init(PAPI_VER_CURRENT);
  if (ret != PAPI_VER_CURRENT) {
    fprintf(stderr, "PAPI_library_init() failed.\n");
    exit(-1);
  }

  int ctrs[] = {PAPI_L1_DCM, PAPI_DP_OPS};
  int num_events = sizeof(ctrs) / sizeof(ctrs[0]);
  int event_set = PAPI_NULL;

  std::cout << num_events << std::endl;
  PAPI_SAFE_CALL(PAPI_create_eventset(&event_set));
  PAPI_SAFE_CALL(PAPI_add_events(event_set, ctrs, num_events));

  for (int i = 0; i < 10; i++) {
    volatile real_t d = rand()  * 1.0/ RAND_MAX;

    std::vector<long long> results(num_events, -1L);

    // Start measurement
    PAPI_SAFE_CALL(PAPI_start(event_set));
    {
      volatile real_t d = 1.0;
#pragma unroll
      for(int i=0; i < NUM_LOOP; i++) {
        d += sqrtx(d); // to prevent optimization
      }
    }
    PAPI_SAFE_CALL(PAPI_stop(event_set, results.data()));

    std::cout << "L1 Cache Misses: " << results[0] << " Flops: " << results[1] <<  std::endl;
  }

  PAPI_SAFE_CALL(PAPI_cleanup_eventset(event_set));
  PAPI_SAFE_CALL(PAPI_destroy_eventset(&event_set));
}