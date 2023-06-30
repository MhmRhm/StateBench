#pragma once
#include <iostream>
#include "boost/statechart/state_machine.hpp"
#include "boost/statechart/simple_state.hpp"

struct Greeting;
struct Machine : boost::statechart::state_machine<Machine, Greeting>{};
struct Greeting : boost::statechart::simple_state<Greeting, Machine> {
    Greeting() { std::cout << "Hello World!\n"; } // entry
    ~Greeting() { std::cout << "Bye Bye World!\n"; } // exit
};
