#pragma once

#include <QAbstractTransition>
#include <QCoreApplication>
#include <QDebug>
#include <QState>
#include <QTimer>
#include <QtStateMachine>

#include <boost/statechart/event.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/state_machine.hpp>
#include <boost/statechart/transition.hpp>

namespace sc = boost::statechart;

static std::chrono::time_point<std::chrono::high_resolution_clock> StartTime{};
static size_t Iterations{};

struct ProceedEvent : sc::event<ProceedEvent> {};
struct TimeoutEvent : sc::event<TimeoutEvent> {};

struct Starting;
struct Running;
struct Stopping;
struct Machine : sc::state_machine<Machine, Starting> {};
struct Starting : sc::simple_state<Starting, Machine> {
  typedef sc::transition<ProceedEvent, Running> reactions;
  ~Starting() {
    StartTime = std::chrono::high_resolution_clock::now();
    Iterations = 0;
  }
};
struct First;
struct Second;
struct Third;
struct Running : sc::simple_state<Running, Machine, First> {
  typedef sc::transition<TimeoutEvent, Stopping> reactions;
};
struct First : sc::simple_state<First, Running> {
  typedef sc::transition<ProceedEvent, Second> reactions;
};
struct Second : sc::simple_state<Second, Running> {
  typedef sc::transition<ProceedEvent, Third> reactions;
};
struct Third : sc::simple_state<Third, Running> {
  typedef sc::transition<ProceedEvent, First> reactions;
  ~Third() { Iterations += 1; }
};
struct Stopping : sc::simple_state<Stopping, Machine> {
  ~Stopping() {
    auto duration{std::chrono::high_resolution_clock::now() - StartTime};
    auto msecs{std::chrono::duration_cast<std::chrono::milliseconds>(duration)};
    std::cout << double(Iterations) / (double(msecs.count()) / 1000)
              << " (iterations/sec)" << std::endl;
  }
};
