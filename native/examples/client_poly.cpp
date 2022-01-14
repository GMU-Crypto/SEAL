#include "pir.hpp"
#include "pir_client.hpp"
#include "pir_server.hpp"
#include <seal/seal.h>
#include <chrono>
#include <memory>
#include <random>
#include <cstdint>
#include <cstddef>
#include <constants.h>
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <ctime>
#include <chrono>
#include <thread>
#define PORT 12345

using namespace std::chrono;
using namespace std;
using namespace seal;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

inline unsigned int to_uint(char ch)
{
    // EDIT: multi-cast fix as per David Hammen's comment
    return static_cast<unsigned int>(static_cast<unsigned char>(ch));
}

std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "abcdef";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

int main(int argc, char *argv[]) {

    cout << "Initializing Poly interpolation prover (client)..." << endl;

    srand((unsigned)time(NULL) * getpid());  
    std::string firstreply = gen_random(65536);
    std::string comm_answer = gen_random(16);
    std::string answer = gen_random(sizeof(uint64_t));


    //NETWORKING - CLIENT ROLE
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "10.193.124.164", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    else
    {
        cout << "Connected to server" << endl;
    }


    sleep_for(1000000ns);

    //send firstreply:  send 2x2x64xN bits= 65536 bytes
    uint32_t msgLength;
    std::vector<unsigned char> pkt ;
    std::string temp ;
    msgLength = firstreply.length();
    std::cout << "() Sending firstreply of length " << msgLength << endl;
    send(sock,&msgLength ,sizeof(uint32_t) ,0); // Send the message length
    send(sock,firstreply.c_str() ,msgLength ,0); // Send the message data 
    std::cout << "() First reply sent." << endl;
    std::cout << "Correctness check:" << to_uint(firstreply.at(10)) << endl;

    sleep_for(1000000ns);

    //receive c_i
    cout << "Receiving c_i.." << endl;
    recv(sock,&msgLength,sizeof(uint32_t),0); // Receive the message length
    //msgLength = ntohl(msgLength); // Ensure host system byte order
    std::cout << "c_i length: " <<msgLength <<endl;
    pkt.resize(msgLength,0x00);
    recv(sock,&(pkt[0]),msgLength,0); // Receive the message data
    temp = { pkt.begin(), pkt.end() } ;
    printf("c_i received\n");
    std::cout << "Actual c_i length: " <<temp.size() <<endl;
    std::cout << "Correctness check:" << to_uint(temp.at(10)) << endl;

    sleep_for(1000000ns);

    //Client: Comm(answer) (not listed) send 16 bytes 
    msgLength = comm_answer.length();
    std::cout << "() Sending Comm(answer) of length " << msgLength << endl;
    send(sock,&msgLength ,sizeof(uint32_t) ,0); // Send the message length
    send(sock,comm_answer.c_str() ,msgLength ,0); // Send the message data 
    std::cout << "() Comm(answer) sent." << endl;
    std::cout << "Correctness check:" << to_uint(comm_answer.at(10)) << endl;

    sleep_for(1000000ns);

    cout << "Receiving seed.." << endl;
    recv(sock,&msgLength,sizeof(uint32_t),0); // Receive the message length
    //msgLength = ntohl(msgLength); // Ensure host system byte order
    std::cout << "Seed length: " <<msgLength <<endl;
    msgLength = 16;
    pkt.resize(msgLength,0x00);
    recv(sock,&(pkt[0]),msgLength,0); // Receive the message data
    temp = { pkt.begin(), pkt.end() } ;

    printf("Seed received\n");
    std::cout << "Actual seed length: " <<temp.size() <<endl;
    std::cout << "Correctness check:" << to_uint(temp.at(10)) << endl;


    sleep_for(1000000ns);

    //Client: Send answer 
    msgLength = answer.length();
    std::cout << "() Sending answer of length " << msgLength << endl;
    send(sock,&msgLength ,sizeof(uint32_t) ,0); // Send the message length
    send(sock,answer.c_str() ,msgLength ,0); // Send the message data 
    std::cout << "() answer sent." << endl;
    std::cout << "Correctness check:" << to_uint(answer.at(5)) << endl;



/*
   
    //Server: Receive seed (?) -random number
    cout << "Receiving seed.." << endl;
    recv(sock,&msgLength,sizeof(uint32_t),0); // Receive the message length
    std::cout << "Seed length: " <<msgLength <<endl;
    pkt.resize(msgLength,0x00);
    recv(sock,&(pkt[0]),msgLength,0); // Receive the message data
    temp = { pkt.begin(), pkt.end() } ;
    printf("Seed received\n");
    std::cout << "Actual seed length: " <<temp.size() <<endl;
    std::cout << "Correctness check:" << to_uint(temp.at(10)) << endl;

*/

    return 0;
}
