#include <cstdlib>
#include <vector>

#include "papi_utils.h"


int main() {
  int N = 128; int BLOCK_SIZE = 32;

  std::vector<std::vector<double>> A (N, std::vector<double>(N,5));
  std::vector<std::vector<double>> B (N, std::vector<double>(N,5));
  std::vector<std::vector<double>> C (N, std::vector<double>(N,0));

  int ret = PAPI_library_init(PAPI_VER_CURRENT);
  if (ret != PAPI_VER_CURRENT) {
    fprintf(stderr, "PAPI_library_init() failed.\n");
    exit(-1);
  }

  int ctrs[] = { PAPI_DP_OPS, PAPI_VEC_DP  }; // EVENTS defined by cmake
  int num_events = sizeof(ctrs) / sizeof(ctrs[0]);
  int event_set = PAPI_NULL;

  PAPI_SAFE_CALL(PAPI_create_eventset(&event_set));

#ifdef MULTIPLEX
  std::cout << "Using papi multiplexer" << std::endl;
  PAPI_SAFE_CALL(PAPI_multiplex_init());
  PAPI_SAFE_CALL(PAPI_assign_eventset_component(event_set, 0));
  PAPI_SAFE_CALL(PAPI_set_multiplex(event_set));
#endif

  PAPI_SAFE_CALL(PAPI_add_events(event_set, ctrs, num_events));

  std::vector<long long> results(num_events, -1L);

  PAPI_SAFE_CALL(PAPI_start(event_set));
  for (int i = 0; i < N; i ++) {
    for (int j = 0; j < N; j ++) {
      for (int k = 0; k < N; k ++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  PAPI_SAFE_CALL(PAPI_stop(event_set, results.data()));

  std::cout << "== Naive MM ==" << std::endl << std::endl;
  std::cout << "PAPI_DP_OPS, PAPI_VEC_DP" << std::endl;
  for (int i = 0; i < num_events - 1; i ++)
    std::cout << results[i] << ", ";
  std::cout << results[num_events - 1] << std::endl << std::endl;

  PAPI_SAFE_CALL(PAPI_start(event_set));
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
  PAPI_SAFE_CALL(PAPI_stop(event_set, results.data()));

  std::cout << "== Tiled MM ==" << std::endl << std::endl;
  std::cout << "PAPI_DP_OPS, PAPI_VEC_DP" << std::endl;
  for (int i = 0; i < num_events - 1; i ++)
    std::cout << results[i] << ", ";
  std::cout << results[num_events - 1] << std::endl << std::endl;

  PAPI_SAFE_CALL(PAPI_cleanup_eventset(event_set));
  PAPI_SAFE_CALL(PAPI_destroy_eventset(&event_set));
}
