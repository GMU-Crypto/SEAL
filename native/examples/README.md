#### Running over network

To run polynomial interpolation of PI_Goodindex as client, change L12 of native/examples/CMakeLists.txt into
````
add_executable(sealexamples client_poly.cpp /home/poa/MP-SPDZ/good_index.cpp share_at.cpp verifier_state.cpp pir.cpp pir_server.cpp pir_client.cpp)
````
To run as server, change in native/examples/examples.cpp
````
#define NETWORKING 1 
````
