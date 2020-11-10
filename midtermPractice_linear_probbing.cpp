#include <iostream>
#include <cmath>

using namespace std;

class item{
    public:
    int key;
    bool empty_since_start = true;
    bool empty_after_removal = false;
};
//Perfect hash function implementation
int modulo_hash_function(int key, int hash_table_size){
    return key % hash_table_size;
}
//Mid square base 10 hash function implementation
int mid_square_base10_hash_function(int key, int hash_table_size){
    int position = key * key;
    int r = ceil(log10(hash_table_size)); //Given by Instructor
    string spos = to_string(position);
    //Deleting right digits
    int rDigits = (spos.size() - r)/2;
    spos.erase(spos.size()-rDigits, rDigits);
    //Deleting left digits
    int lDigits = spos.size() - r;
    spos.erase(0, lDigits);   
    return atoi(spos.c_str()) % hash_table_size;
}

//Mid Square Base2 hash function implementation
int mid_square_base2_hash_function(int key, int hash_table_size){
    int position = key * key;
    int r = ceil(log2(hash_table_size));
    int l_bits = (32 - r)/2;
    int e_bits = position >> l_bits;
    e_bits = e_bits & (0XFFFFFFFF >> (32 - r));
    return e_bits % hash_table_size;
}
//Inserting key into the table
int insert_item(int key, item hash_table[], int hash_table_size){
    int check = 0;
    int position = modulo_hash_function(key, hash_table_size);
    while( check < hash_table_size){
        if(hash_table[position].empty_after_removal || hash_table[position].empty_since_start) //##Inserting item check fot table empty since start and empty after removal
        { 
            hash_table[position].key = key;
            hash_table[position].empty_since_start = false;
            hash_table[position].empty_after_removal = false;
            return 0;
        }
        check++;
        position = (position + 1) % hash_table_size;
        cout <<endl << "Press -1 to end the insertin operation.";
    }
return -1;
}
//Searching key from the table
int search_item(int search_key, item hash_table[], int hash_table_size){
    int check = 0;
    int position = modulo_hash_function(search_key, hash_table_size);
    while( check < hash_table_size){
        if(hash_table[position].key == search_key){
           cout <<"\n" << search_key <<" found successfully.";
            return 0;
        }
        check++;
        position = (position + 1) % hash_table_size;
    }
    cout <<endl << search_key <<" not found in the table.";
    return -1;
}
//Deleting key in the table
int delete_item(int delete_key, item hash_table[], int hash_table_size){
    int check = 0;
    int position = modulo_hash_function(delete_key, hash_table_size);
    while( check < hash_table_size && !hash_table[position].empty_since_start)//@@Important condition to check for table not empty since start
    {
        if(hash_table[position].key == delete_key){
            hash_table[position].key = -1;
            hash_table[position].empty_since_start = false;
            hash_table[position].empty_after_removal = true;
            cout <<"\n" << delete_key <<" deleted successfully.";
            return 0;
        }
        check++;
        position = (position + 1) % hash_table_size;
    }
    cout <<endl << delete_key <<" not found in the table.";
    return -1;
}
void display(item hash_table[], int hash_table_size){
cout << endl;
for (int i = 0; i < hash_table_size; i++)
{
    if(!hash_table[i].empty_since_start && !hash_table[i].empty_after_removal) //##Displaying check if table not empty since start && and not  empty after removal
        cout << i <<" ---> " << hash_table[i].key << endl;
    else
        cout << i << " ---> " << endl;
}
}
//Main function
int main(){
    int hash_table_size, key, search_value, delete_value;
    cout <<"Enter the size of the table: ";
    cin >> hash_table_size;
    item hash_table[hash_table_size];
    cout <<"Enter the element value you want to insert till -1: ";
    cin >> key;
    while(key != -1){
        if(insert_item(key, hash_table, hash_table_size) == 0)
            cout << "\nInsertion Successfull.";
        else
            cout << "\nInsertion Failed.";
    cin >> key;
    }
//Display the table items
display(hash_table, hash_table_size);

cout <<"\nEnter value you want to search: ";
cin >> search_value;
//searching hash table for search value entered
search_item(search_value, hash_table, hash_table_size);
//Deleting value
cout <<"\nEnter the value you want to delete: ";
cin >> delete_value;
delete_item(delete_value,hash_table, hash_table_size);
//Display the table items
display(hash_table, hash_table_size);
}