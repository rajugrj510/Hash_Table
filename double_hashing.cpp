#include <iostream>
#include <cmath>
/**
 * Implementation of hash table using quadratic collision strategy 
 * and by using perfect hash function
 */
using namespace std;

class item{
    public:
    int key;
    bool empty_since_start = true;
    bool empty_after_removal = true;
};
//Hash function by mid square base 10
int mid_square_base2_function1(int key){
    return key % 10;
}
//second hash function
int modulo_hash_function2(int key){
    return 11 - key % 11;
}
//Perfect hashing function
// int mid_square_base10_function(int key, int hash_table_size){
//     return key % hash_table_size;
// }
//Insert using quadratic probing
int insert_item(item hash_table[], int key, int hash_table_size){
    int position = mid_square_base2_function1(key);
    cout <<"\ninitial position: " << position << endl;
    int check = 0;
    while(check < hash_table_size){
        if(hash_table[position].empty_since_start || hash_table[position].empty_after_removal){
            hash_table[position].key = key;
            hash_table[position].empty_since_start = false;
            hash_table[position].empty_after_removal = false;
            return 0;
        }
        check++;
        //Changing the index quadratically
        position = (mid_square_base2_function1(key) + check * modulo_hash_function2(key)) % hash_table_size; 
    }
    cout <<"Insertion failed.";
    return -1;
}
//Search key in hash table
int search_item(item hash_table[], int search_key, int hash_table_size){
    int position = mid_square_base2_function1(search_key);
    int check = 0;
    while(check < hash_table_size){
        if(hash_table[position].key == search_key){
            cout <<search_key << " found in the table.";
            return 0;
        }
        check++;
       position = (mid_square_base2_function1(search_key) + (check * modulo_hash_function2(search_key))) % hash_table_size;
    }
    cout << search_key << " not found in the hash table.";
    return -1;
}

//Delete a key from the hash table
int delete_item(item hash_table[], int delete_key, int hash_table_size){
    int position = mid_square_base2_function1(delete_key);
    int check = 0;
    while( check < hash_table_size){
        if(hash_table[position].key == delete_key){
            hash_table[position].key = 0;
            hash_table[position].empty_since_start = false;
            hash_table[position].empty_after_removal = true;
            cout << delete_key << " successfully deleted." << endl;
            return 0;
        }
        check++;
        position = (mid_square_base2_function1(delete_key) + (check * modulo_hash_function2(delete_key))) % hash_table_size;
    }
    cout <<delete_key << " not found in the hash table.";
    return -1;
}
//Display function
void display(item hash_table[], int hash_table_size){
    cout << endl;
    for (int i = 0; i < hash_table_size; i++)
    {
        if(!hash_table[i].empty_since_start && !hash_table[i].empty_after_removal)
            cout << i <<"--->" << hash_table[i].key << endl;
        else
            cout << i << "--->" << endl;     
    }
    
}

//Main 
int main(){
    int hash_table_size;
    int key, search_key, delete_key;
    cout <<"Enter the size of the hash table: ";
    cin >> hash_table_size;
    item hash_table[hash_table_size];
    //Insert element into bucket
    cout <<"\nEnter the element to insert until -1: ";
    cin >> key;
    while(key != -1){
        if(insert_item(hash_table, key, hash_table_size) == 0)
            cout << key <<" successfully inserted."<< endl;
    //empty key buffer    
    cin >> key;
    }
    //Search element from bucket
    cout <<"Enter the key value you want to search: ";
    cin >> search_key;
    search_item(hash_table, search_key, hash_table_size);
    //Delete element from bucket
    cout <<"\nEnter the delete value: ";
    cin >> delete_key;
    delete_item(hash_table, delete_key, hash_table_size);

    //Display whole bucket
    display(hash_table, hash_table_size);
    return 0;
}