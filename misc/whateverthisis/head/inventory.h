#pragma once
#include "item.h"

struct full_armor {
    armor* helmet = nullptr;
    armor* chestplate = nullptr;
    armor* boots = nullptr;
};

class inventory {
protected:
    std::vector<item*> _items;
    full_armor _armor;
public:
    ~inventory();
    std::vector<item*> get_items();
    void add_item(item* item_);
    item* get_item(unsigned int slot);
    void remove_item(unsigned int slot);
    bool is_in_inventory(item* item_);
    void equip_armor_helmet(armor* armor_);
    void equip_armor_helmet(item* not_suitable);
    void equip_armor_chestplate(armor* armor_);
    void equip_armor_chestplate(item* not_suitable);
    void equip_armor_boots(armor* armor_);
    void equip_armor_boots(item* not_suitable);
    armor* get_armor_helmet();
    armor* get_armor_chestplate();
    armor* get_armor_boots();
    short get_total_armor();
};
