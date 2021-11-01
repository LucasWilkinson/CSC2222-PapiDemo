# PAPI Demo

### Build

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release
make
```

### Run Highlevel Demo

```
export PAPI_EVENTS="PAPI_L1_DCM"
export PAPI_HL_VERBOSE=11
export PAPI_REPORT=1

./high_level_demo
```