#include "mainwindow.h"

#include <QMessageBox>

#include "promowindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

inline void goToNextWindow(MainWindow* w) {
  auto nextWindow = new PromoWindow();
  nextWindow->show();
  w->close();
}

void MainWindow::on_loginButton_clicked() {
  const auto PASSWORD = ui->passwordEdit->text();
  const auto GOOD_PASSWORD = "123";

  if (PASSWORD != GOOD_PASSWORD) {
    QMessageBox::critical(this, "Login Failed", "Try to type password again.");
    return;
  }

  goToNextWindow(this);
}
