#include "../head/inventory.h"


inventory::~inventory() {
    for (size_t i = 0; i < _items.size(); ++i) {
        delete _items[i];
    }
}

std::vector<item*> inventory::get_items() {
    return _items;
}


void inventory::add_item(item* item_) {
    for (size_t i = 0; i < _items.size(); ++i) {
        if (item_->get_max_stack_size() == 1) {
            break;
        }
        if (_items[i]->can_add(item_) == true) {
            _items[i]->add(item_->get_stack());
            delete item_;
            return;
        } else if (_items[i]->can_add(item_,_items[i]->get_max_stack_size() - _items[i]->get_stack())) {
            item_->set_stack(item_->get_stack() - (_items[i]->get_max_stack_size() - _items[i]->get_stack()));
            _items[i]->set_stack(_items[i]->get_max_stack_size());
            continue;
        }
    }
    _items.reserve(_items.size() + 1);
    _items.emplace_back(item_);
}

item* inventory::get_item(unsigned int slot) {
    if (slot >= _items.size()) {
        throw std::exception("[inventory::get_item] reached end of vector");
    }
    return _items[slot];
}

void inventory::remove_item(unsigned int slot) {
    if (slot >= _items.size()) {
        throw std::exception("[inventory::remove_item] reached end of vector");
    }
    delete _items[slot];
    _items.erase(_items.begin() + slot);
    _items.shrink_to_fit();
}

bool inventory::is_in_inventory(item *item_) {
    for (size_t i = 0; i < _items.size(); ++i) {
        if (_items[i] == item_) {
            return true;
        }
    }
    return false;
}

void inventory::equip_armor_helmet(armor* armor_) {
    if (armor_->get_armor_slot() != armor_slot::helmet || !(this->is_in_inventory(armor_)))
        return;

    _armor.helmet = armor_;
}

void inventory::equip_armor_helmet(item* not_suitable) {
    return;
}

void inventory::equip_armor_chestplate(armor* armor_) {
    if (armor_->get_armor_slot() != armor_slot::chestplate || !(this->is_in_inventory(armor_)))
        return;

    _armor.chestplate = armor_;
}

void inventory::equip_armor_chestplate(item* not_suitable) {
    return;
}


void inventory::equip_armor_boots(armor* armor_) {
    if (armor_->get_armor_slot() != armor_slot::boots || !(this->is_in_inventory(armor_)))
        return;

    _armor.boots = armor_;
}

void inventory::equip_armor_boots(item* not_suitable) {
    return;
}

armor* inventory::get_armor_helmet() {
    return _armor.helmet;
}

armor* inventory::get_armor_chestplate() {
    return _armor.chestplate;
}

armor* inventory::get_armor_boots() {
    return _armor.boots;
}

short inventory::get_total_armor() {
    return _armor.helmet->get_armor_points() + _armor.chestplate->get_armor_points() + _armor.boots->get_armor_points();
}

