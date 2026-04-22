#include "../head/character.h"

void entity::_check_upgrade() {
    if (_xp >= _xp_required) {
        ++_lvl;
        _xp = 0;
        _xp_required = _xp_required + (_xp_required * _required_coef);
    }
}

inventory entity::get_inventory() {
    return _inventory;
}

QString entity::get_name() {
    return _name;
}

unsigned int entity::get_lvl() {
    return _lvl;
}

unsigned long entity::get_xp() {
    return _xp;
}

unsigned long entity::get_xp_required() {
    return _xp_required;
}

float entity::get_required_coef() {
    return _required_coef;
}

void entity::set_inventory(inventory &inventory_) {
    _inventory = inventory_;
}

void entity::set_name(QString &name) {
    _name = name;
}

void entity::set_lvl(unsigned int lvl) {
    _lvl = lvl;
}

void entity::add_xp(unsigned long amount) {
    _xp += amount;
    this->_check_upgrade();
}

void entity::set_xp(unsigned long xp) {
    _xp = xp;
    this->_check_upgrade();
}

void entity::set_xp_required(unsigned long xp_required) {
    _xp_required = xp_required;
    this->_check_upgrade();
}

void entity::set_required_coef(float required_coef) {
    _required_coef = required_coef;
}
