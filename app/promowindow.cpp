#include "promowindow.h"

#include <QMessageBox>
#include <QRandomGenerator>

#include "cardwidget.h"
#include "ui_promowindow.h"

PromoWindow::PromoWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::PromoWindow) {
  ui->setupUi(this);
  ui->cardsListWidget->setSelectionRectVisible(false);

  initPromo();
}

PromoWindow::~PromoWindow() { delete ui; }

const QString PromoWindow::getRandomString() {
  const QString possibleCharacters(
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
  const uint randomStringLength = PROMO_LENGTH;
  QString randomString;
  for (uint i = 0; i < randomStringLength; ++i) {
    uint index = rand() % possibleCharacters.length();
    QChar nextChar = possibleCharacters.at(index);
    randomString.append(nextChar);
  }
  return randomString;
}

void PromoWindow::initPromo() {
  ui->cardsListWidget->clear();

  for (uint i = 0; i < fieldSize; i++) {
    const auto promo = getRandomString();
    const auto encPromo = crypton.encrypt(promo);

    qDebug() << promo << " : " << encPromo;

    promos.append(encPromo);
    addCard(encPromo);
  }
}

void PromoWindow::addCard(const QString promo) {
  auto listItemW = new QListWidgetItem();
  auto itemW = new CardWidget(promo, this);

  listItemW->setSizeHint(itemW->sizeHint());

  ui->cardsListWidget->addItem(listItemW);
  ui->cardsListWidget->setItemWidget(listItemW, itemW);
}

void PromoWindow::on_openPromoButton_clicked() {
  while (true) {
    auto randomIndex = QRandomGenerator::global()->bounded(uint(0), fieldSize);

    if (openedPromos.contains(randomIndex)) continue;

    const auto item = ui->cardsListWidget->item(randomIndex);
    const auto itemWidget =
        dynamic_cast<CardWidget*>(ui->cardsListWidget->itemWidget(item));

    itemWidget->showPromo(crypton.decrypt(promos[randomIndex]));
    openedPromos.append(randomIndex);
    fieldSize++;

    const auto promo = getRandomString();
    const auto encpromo = crypton.encrypt(promo);
    promos.append(encpromo);
    addCard(encpromo);

    break;
  }
}
