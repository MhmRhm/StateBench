#include "include/infrastructure/infrastructure.h"

void benchQt(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  size_t iterations{};
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

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
    startTime = std::chrono::system_clock::now();
  });
  QObject::connect(&third, &QState::entered, [&]() {
    QCoreApplication::processEvents();
    iterations += 1;
  });
  QObject::connect(&stopping, &QState::entered, [&]() {
    auto duration{std::chrono::high_resolution_clock::now() - startTime};
    auto msecs{std::chrono::duration_cast<std::chrono::milliseconds>(duration)};
    std::cout << double(iterations) / (double(msecs.count()) / 1000)
              << " (iterations/sec)" << std::endl;
    QCoreApplication::instance()->exit();
  });

  machine.start();
  app.exec();
}

void benchBoost() {}

int main(int argc, char **argv) {
  benchQt(argc, argv);
  return 0;
}
