#include "include/infrastructure/infrastructure.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);
  QStateMachine qmachine;
  QState qstate(&qmachine);
  qmachine.setInitialState(&qstate);
  qstate.connect(
      &qstate, &QState::entered, &qstate,
      []() {
        std::cout << "Entered!" << std::endl;
        QCoreApplication::instance()->exit();
      },
      Qt::DirectConnection);
  qmachine.start();
  app.exec();

  Machine myMachine;
  myMachine.initiate();

  return 0;
}
