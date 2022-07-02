#include "crypton.h"

#include <QCryptographicHash>

QAESEncryption crypto(QAESEncryption::AES_256, QAESEncryption::ECB);

Crypton::Crypton(const QString password) {
  this->password = formatKey(password);
}

const QBA Crypton::formatKey(const QString password) {
  QBA pByte = password.toUtf8();
  return QCryptographicHash::hash(pByte, QCryptographicHash::Sha256);
}
const QString Crypton::encrypt(const QString text) {
  return crypto.encode(text.toUtf8(), password).toHex();
}

const QString Crypton::decrypt(const QString text) {
  auto withPadding = crypto.decode(QBA::fromHex(text.toUtf8()), password);
  return crypto.removePadding(withPadding);
}
