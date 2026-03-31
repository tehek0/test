#include "lib.h"
#include "card.h"
#include "mainwindow.h"

armor::armor() {
    helmet = 0;
    chestplate = 0;
    boots = 0;
}

unsigned int armor::total() {
    return (helmet + chestplate + boots);
}

magician::magician(QString name, QString ability, unsigned int mana, unsigned int health, armor armor_) {
    _name = name;
    _ability = ability;
    _mana = mana;
    _health = health;
    _armor = armor_;
}

QString magician::make_list_item() {
QString item = QString("%1 %2 %3 %4 <%5/%6/%7>").arg(_name, _ability).arg(_mana).arg(_health).arg(_armor.helmet).arg(_armor.chestplate).arg(_armor.boots);
    return item;
}

void magician::Craft(Ui::card* ui) {
    ui->pic->setPixmap(QPixmap(QString::fromUtf8(":/rs/maghr.png")));

    ui->name->setText(this->get_name());

    QString magician_ability = this->get_ability();
    ui->magician_ability->setText(magician_ability);
    if (magician_ability == "земля")
        ui->magician_ability->setStyleSheet(QString::fromUtf8("color: rgb(173,123,73);"));
    if (magician_ability == "вода")
        ui->magician_ability->setStyleSheet(QString::fromUtf8("color: rgb(43,59,237);"));
    if (magician_ability == "огонь")
        ui->magician_ability->setStyleSheet(QString::fromUtf8("color: rgb(255,234,0);"));

    QString magician_health = QString::number(this->get_health());
    ui->magician_health->setText(magician_health);
    QString magician_mana = QString::number(this->get_mana());
    ui->magician_mana->setText(magician_mana);

    ui->enemy_armor->setText(" ");
    ui->enemy_health->setText(" ");
}

enemy::enemy(QString name, QString rarity, unsigned int dmg, unsigned int health, armor armor_) {
    _name = name;
    _rarity = rarity;
    _dmg = dmg;
    _health = health;
    _armor = armor_;
}

QString enemy::make_list_item() {
    QString item = QString("%1 %2 %3 %4 <%5/%6/%7>").arg(_name, _rarity).arg(_dmg).arg(_health).arg(_armor.helmet).arg(_armor.chestplate).arg(_armor.boots);
    return item;
}

void enemy::Craft(Ui::card* ui) {
    ui->pic->setPixmap(QPixmap(QString::fromUtf8(":/rs/vraghr.png")));

    ui->name->setText(this->get_name());

    QString enemy_rarity = this->get_rariry();
    if (enemy_rarity == "Обычный")
        ui->name->setStyleSheet(QString::fromUtf8("color: rgb(91,237,43);"));
    if (enemy_rarity == "Редкий")
        ui->name->setStyleSheet(QString::fromUtf8("color: rgb(43,59,237);"));
    if (enemy_rarity == "Легенда")
        ui->name->setStyleSheet(QString::fromUtf8("color: rgb(255,234,0);"));


    QString enemy_health = QString::number(this->get_health());
    ui->enemy_health->setText(enemy_health);

    QString enemy_armor = QString("<%1/%2/%3>").arg(this->get_armor().helmet).arg(this->get_armor().chestplate).arg(this->get_armor().boots);
    ui->enemy_armor->setText(enemy_armor);

    ui->magician_mana->setText(" ");
    ui->magician_ability->setText(" ");
    ui->magician_health->setText(" ");
}

