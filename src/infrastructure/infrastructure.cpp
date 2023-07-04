#include "include/infrastructure/infrastructure.h"

void benchQt(int argc, char **argv) {
  using namespace std::chrono;
  QCoreApplication app(argc, argv);

  size_t iterations{};
  time_point<high_resolution_clock> startTime;

  QTimer timer;
  timer.setSingleShot(true);

  QStateMachine machine;
  QState starting(&machine);
  QState running(&machine);
  QState first(&running);
  QState second(&running);
  QState third(&running);
  QState stopping(&machine);

  running.setInitialState(&first);
  machine.setInitialState(&starting);

  starting.addTransition(&running);
  first.addTransition(&first, &QState::entered, &second);
  second.addTransition(&second, &QState::entered, &third);
  third.addTransition(&third, &QState::entered, &first);
  running.addTransition(&timer, &QTimer::timeout, &stopping);

  QObject::connect(&starting, &QState::exited, [&]() {
    timer.start(10000);
    startTime = high_resolution_clock::now();
  });
  QObject::connect(&third, &QState::entered, [&]() {
    QCoreApplication::processEvents();
    iterations += 1;
  });
  QObject::connect(&stopping, &QState::entered, [&]() {
    auto duration{high_resolution_clock::now() - startTime};
    auto msecs{duration_cast<milliseconds>(duration)};
    std::cout << double(iterations) / (double(msecs.count()) / 1000)
              << " (iterations/sec)" << std::endl;
    QCoreApplication::instance()->exit();
  });

  machine.start();
  app.exec();
}

void benchBoost() {
  using namespace std::chrono;
  time_point<high_resolution_clock> endTime{high_resolution_clock::now() + 10s};

  Machine machine{};
  machine.initiate();
  while (endTime > high_resolution_clock::now()) {
    machine.process_event(ProceedEvent{});
  }
  machine.process_event(TimeoutEvent{});
}

int main(int argc, char **argv) {
  benchQt(argc, argv);
  benchBoost();
  return 0;
}
