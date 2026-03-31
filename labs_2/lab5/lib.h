#pragma once
#include <QString>
#include <QLabel>
#include "card.h"
#include <ui_card.h>


struct armor {
    unsigned int helmet;
    unsigned int chestplate;
    unsigned int boots;
    unsigned int total();
    armor();
};

class entity {
protected:
    QString _name;
    unsigned int _health;
    armor _armor;
public:
    virtual void Craft(Ui::card* ui) = 0;
    entity() = default;
    virtual ~entity() = default;
    QString get_name() {
        return _name;
    }
    unsigned int get_health() {
        return _health;
    }
    armor get_armor() {
        return _armor;
    }
    virtual QString make_list_item() = 0;
};

class magician : public entity {
private:
    QString _ability;
    unsigned int _mana;
public:
    magician() = default;
    magician(QString name, QString ability, unsigned int mana, unsigned int health, armor armor_);
    virtual void Craft(Ui::card* ui);
    virtual QString make_list_item();
    QString get_ability() {
        return _ability;
    }
    unsigned int get_mana() {
        return _mana;
    }
};

class enemy : public entity {
private:
    QString _rarity;
    unsigned int _dmg;
public:
    enemy() = default;
    enemy(QString name, QString rarity, unsigned int dmg, unsigned int health, armor armor_);
    virtual void Craft(Ui::card* ui);
    virtual QString make_list_item();
    QString get_rariry() {
        return _rarity;
    }
    unsigned int get_dmg() {
        return _dmg;
    }
};
