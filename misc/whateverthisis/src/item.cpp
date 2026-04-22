#include "../head/item.h"


bool item::can_add(item* other) {
    if (*this != other || _stack + other->_stack > _max_stack_size)
        return false;
    return true;
}


bool item::can_add(item* other, unsigned int count) {
    if (*this != other || _stack + count > _max_stack_size || other->_stack < count)
        return false;
    return true;
}


void item::add() {
    _stack++;
}


void item::add(unsigned int count) {
    _stack += count;
}


bool item::has_amount(unsigned int count) {
    if (_stack >= count)
        return true;
    return false;
}


void item::remove() {
    _stack--;
}


void item::remove(unsigned int count) {
    _stack -= count;
}



QString item::get_name() {
    return _name;
}

QString item::get_asset() {
    return _asset;
}

unsigned int item::get_stack() {
    return _stack;
}

unsigned int item::get_max_stack_size() {
    return _max_stack_size;
}

unsigned int item::get_base_cost() {
    return _base_cost;
}

void item::set_name(const QString& name) {
    _name = name;
}

void item::set_asset(const QString& asset) {
    _asset = asset;
}

void item::set_stack(unsigned int stack) {
    _stack = stack;
}

void item::set_max_stack_size(unsigned int max_stack_size) {
    _max_stack_size = max_stack_size;
}

void item::set_base_cost(unsigned int base_cost) {
    _base_cost = base_cost;
}

bool item::operator==(item* other) {
    if (this->_name != other->_name || this->_asset != other->_asset || this->_max_stack_size != other->_max_stack_size || this->_base_cost != other->_base_cost)
        return false;

    return true;
}

bool item::operator!=(item* other) {
    if (this->_name != other->_name || this->_asset != other->_asset || this->_max_stack_size != other->_max_stack_size || this->_base_cost != other->_base_cost)
        return true;

    return false;
}

armor_slot armor::get_armor_slot() {
    return _armor_slot;
}

short armor::get_armor_points() {
    return _armor_points;
}


void armor::set_armor_slot(armor_slot armor_slot_) {
    _armor_slot = armor_slot_;
}

void armor::set_armor_points(short armor_points) {
    _armor_points = armor_points;
}

bool armor::operator==(armor* other) {
    if (this->_name != other->_name || this->_asset != other->_asset || this->_max_stack_size != other->_max_stack_size || this->_base_cost != other->_base_cost || this->_armor_slot != other->_armor_slot || this->_armor_points != other->_armor_points)
        return false;

    return true;
}

bool armor::operator!=(armor* other) {
    if (this->_name != other->_name || this->_asset != other->_asset || this->_max_stack_size != other->_max_stack_size || this->_base_cost != other->_base_cost || this->_armor_slot != other->_armor_slot || this->_armor_points != other->_armor_points)
        return true;

    return false;
}

bool armor::operator==(item* other) {
    return false;
}

bool armor::operator!=(item* other) {
    return true;
}
