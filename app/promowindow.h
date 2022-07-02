#ifndef PROMOWINDOW_H
#define PROMOWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "crypton.h"
#include "password.h"

namespace Ui {
class PromoWindow;
}

class PromoWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit PromoWindow(QWidget *parent = nullptr);
  ~PromoWindow();

  void addCard(const QString promo);
  void initPromo();
  const QString getRandomString();

 private slots:
  void on_openPromoButton_clicked();

 private:
  Ui::PromoWindow *ui;

  uint fieldSize = 9;
  const uint PROMO_LENGTH = 4;

  QVector<QString> promos;
  QVector<uint> openedPromos;

  Crypton crypton = Crypton(GOOD_PASSWORD);
};

#endif  // PROMOWINDOW_H
