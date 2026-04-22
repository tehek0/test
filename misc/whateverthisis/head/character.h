#pragma once
#include "inventory.h"
#include <QObject>
#include <mainwindow.h>


class entity {
protected:
    inventory _inventory;
    QString _name;
    unsigned int _lvl;
    unsigned long _xp;
    unsigned long _xp_required;
    float _required_coef = 0.25f;
    void _check_upgrade();
public:
    entity() = default;
    entity(const inventory& inventory_,
           const QString& name,
           unsigned int lvl,
           unsigned long xp,
           unsigned long xp_required,
           float required_coef):
        _inventory(inventory_),
        _name(name),
        _lvl(lvl),
        _xp(xp),
        _xp_required(xp_required),
        _required_coef(required_coef)
    {
        this->_check_upgrade();
    }
    inventory get_inventory();
    QString get_name();
    unsigned int get_lvl();
    unsigned long get_xp();
    unsigned long get_xp_required();
    float get_required_coef();
    void set_inventory(inventory& inventory_);
    void set_name(QString& name);
    void set_lvl(unsigned int lvl);
    void add_xp(unsigned long amount);
    void set_xp(unsigned long xp);
    void set_xp_required(unsigned long xp_required);
    void set_required_coef(float required_coef);

};
