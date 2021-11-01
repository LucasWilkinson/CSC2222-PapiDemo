//
// Created by lwilkinson on 10/31/21.
//
// Example from:
//    http://www.serc.iisc.ac.in/serc_web/wp-content/uploads/2019/05/PAPI_USERu2019S_GUIDE.pdf
//
#include <cmath>
#include <vector>

#include <papi.h>
#include "papi_utils.h"


int main()
{
  int N = 128; int BLOCK_SIZE = 32;

  std::vector<std::vector<double>> A (N, std::vector<double>(N,5));
  std::vector<std::vector<double>> B (N, std::vector<double>(N,5));
  std::vector<std::vector<double>> C (N, std::vector<double>(N,0));

  PAPI_SAFE_CALL(PAPI_hl_region_begin("naive_mm"));
  for (int i = 0; i < N; i ++) {
    for (int j = 0; j < N; j ++) {
      for (int k = 0; k < N; k ++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  PAPI_SAFE_CALL(PAPI_hl_region_end("naive_mm"));

  PAPI_SAFE_CALL(PAPI_hl_region_begin("tiled_mm"));
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
#ifdef TILE_SNAPSHOTTING
        PAPI_SAFE_CALL(PAPI_hl_read("tiled_mm"));
#endif
      }
    }
  }
  PAPI_SAFE_CALL(PAPI_hl_region_end("tiled_mm"));
  return 0;
}
