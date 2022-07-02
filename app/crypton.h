#ifndef CRYPTON_H
#define CRYPTON_H

#include <QByteArray>
#include <QString>

#include "qaesencryption.h"

using QBA = QByteArray;

class Crypton {
 public:
  Crypton(){};
  Crypton(const QString password);
  QBA password;

  const static QBA formatKey(const QString password);

  const QString encrypt(const QString text);
  const QString decrypt(const QString text);
};

#endif  // CRYPTON_H
