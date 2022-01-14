## Running over network


#### PIR
Go to SealPIR/CMakeLists.txt
and change main.cpp to server,coo and client.cpp accordingly. 

#### Polynomial interpolation
To run polynomial interpolation of PI_Goodindex as client, change L12 of native/examples/CMakeLists.txt into
````
add_executable(sealexamples client_poly.cpp /home/poa/MP-SPDZ/good_index.cpp share_at.cpp verifier_state.cpp pir.cpp pir_server.cpp pir_client.cpp)
````
To run as server, change in native/examples/examples.cpp
````
#define NETWORKING 1 
````
#### Bounded noise
Runs run_good_index_network() instead of run_good_index().
On client, run SEAL/native/examples/client_poly.cpp as
````
cd MP-SPDZ
g++ good_index_client.cpp && ./a.out
````
