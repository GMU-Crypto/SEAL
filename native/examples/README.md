## Running over network


#### PIR
Go to SealPIR/CMakeLists.txt
and change main.cpp to server.cpp and client.cpp accordingly. 
Then 
````
cd ~\SealPIR && cmake . -DSEAL_THROW_ON_TRANSPARENT_CIPHERTEXT=OFF && make && bin/./main
````
#### Polynomial interpolation
In all below:
````
cd ~/SEAL/native/examples && cmake . && make && ~/SEAL/native/bin/./sealexamples
````
To run polynomial interpolation of PI_Goodindex as client, change L12 of native/examples/CMakeLists.txt into
````
add_executable(sealexamples client_poly.cpp /home/poa/MP-SPDZ/good_index.cpp share_at.cpp verifier_state.cpp pir.cpp pir_server.cpp pir_client.cpp)
````
To run as server, change in native/examples/examples.cpp
````
#define NETWORKING 1 
````
and remove run_good_index_network(0); from L212 (add it back when finished)
#### Bounded noise
Runs run_good_index_network() instead of run_good_index().
On client, run SEAL/native/examples/client_poly.cpp as
````
cd MP-SPDZ
g++ good_index_client.cpp && ./a.out
````
#### MPCitH
Runs run_verifier_state_network() instead of run_verifier_state().
On client, run /SEAL/native/examples/verifier_state_client.cpp as
````
cd MP-SPDZ
/home/poa/SEAL/native/examples/verifier_state_client.cpp
````
