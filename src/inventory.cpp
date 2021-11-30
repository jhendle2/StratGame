// #include <inventory.h>
// #include <iostream>

// ItemQuantityPair::ItemQuantityPair(){
//     this->quanity = 0;
//     this->item = Item();
// }

// ItemQuantityPair::ItemQuantityPair(int quantity, Item item){
//     this->quanity = quanity;
//     this->item = item;
// }

// ItemQuantityPair::~ItemQuantityPair(){

// }

// Inventory::Inventory(){
    
// }

// Inventory::~Inventory(){

// }

// bool Inventory::has(const char* name){
//     for(ItemQuantityPair* iqp : items){
//         // Item current = std::get<0>(iqp);
//         Item current = iqp.item;
//         if(strcmp(current.name,name)==0) return true;
//     }
//     return false;
// }

// bool Inventory::has(Item item){
//     for(ItemQuantityPair* iqp : items){
//         // Item current = std::get<0>(iqp);
//         Item current = iqp->item;
//         if(strcmp(current.name,item.name)==0) return true;
//     }
//     return false;
// }

// void Inventory::add(Item item){
//     int index = find_index(item);
//     if(index>-1){
//         ItemQuantityPair iqp = find_tup(index);
//         iqp.quanity++;
//     }
//     else{
//         // ItemQuantityPair iqp(item, 0);
//         ItemQuantityPair iqp = {0, item};
//         this->items.push_back(iqp);
//     }
// }

// int Inventory::find_index(const char* name){
//     int counter = 0;
//     for(ItemQuantityPair iqp : items){
//         // Item current = std::get<0>(iqp);
//         Item current = iqp.item;
//         if(strcmp(current.name,name)==0) return counter;
//         counter++;
//     }
//     return -1;
// }

// int Inventory::find_index(Item item){
//     int counter = 0;
//     for(ItemQuantityPair iqp : items){
//         // Item current = std::get<0>(iqp);
//         Item current = iqp.item;
//         if(strcmp(current.name,item.name)==0) return counter;
//         counter++;
//     }
//     return -1;
// }

// Item Inventory::find(int index){
//     int counter = 0;
//     for(ItemQuantityPair iqp : items){
//         // if(index==counter) return std::get<0>(iqp);
//         Item current = iqp.item;
//         counter++;
//     }
//     return Item();
// }

// Item Inventory::find(const char* name){
//     for(ItemQuantityPair iqp : items){
//         // Item current = std::get<0>(iqp);
//         Item current = iqp.item;
//         if(strcmp(current.name,name)==0) return current;
//     }
//     return Item();
// }

// ItemQuantityPair Inventory::find_tup(int index){
//     int counter = 0;
//     for(ItemQuantityPair iqp : items){
//         if(index==counter) return iqp;
//         counter++;
//     }
//     // return ItemQuantityPair(Item(), 0);
//     return {0, Item()};
// }

// ItemQuantityPair Inventory::find_tup(const char* name){
//     for(ItemQuantityPair iqp : items){
//         // Item current = std::get<0>(iqp);
//         Item current = iqp.item;
//         if(strcmp(current.name,name)==0) return iqp;
//     }
//     // return ItemQuantityPair(Item(), 0);
//     return {0, Item()};
// }

// void Inventory::print(int index){
//     ItemQuantityPair iqp = find_tup(index);
//     // std::cout << "(" << std::get<1>(iqp) << ") ";
//     // std::get<0>(iqp).print();
//     std::cout << "(" << iqp.quanity << ") ";
//     iqp.item.print();
//     std::cout<<"\n";
// }

// void Inventory::print_all(){
//     for(ItemQuantityPair iqp : items){
//         // std::cout << "(" << std::get<1>(iqp) << ") ";
//         // std::get<0>(iqp).print();
//         std::cout << "(" << iqp.quanity << ") ";
//         iqp.item.print();
//         std::cout<<"\n";
//     }
// }