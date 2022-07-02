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
  const int randomStringLength = PROMO_LENGTH;
  QString randomString;
  for (int i = 0; i < randomStringLength; ++i) {
    int index = rand() % possibleCharacters.length();
    QChar nextChar = possibleCharacters.at(index);
    randomString.append(nextChar);
  }
  return randomString;
}

void PromoWindow::initPromo() {
  ui->cardsListWidget->clear();

  for (uint i = 0; i < FIELD_SIZE; i++) {
    auto promo = getRandomString();
    promos.append(promo);
    addCard(promo);
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
  if (openedPromos.length() == FIELD_SIZE) return;

  while (true) {
    auto randomIndex = QRandomGenerator::global()->bounded(uint(0), FIELD_SIZE);

    if (openedPromos.contains(randomIndex)) continue;

    const auto item = ui->cardsListWidget->item(randomIndex);
    const auto itemWidget =
        dynamic_cast<CardWidget*>(ui->cardsListWidget->itemWidget(item));

    itemWidget->showPromo();
    openedPromos.append(randomIndex);
    break;
  }
}
