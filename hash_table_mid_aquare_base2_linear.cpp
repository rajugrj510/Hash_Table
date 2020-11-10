#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

class item{
	
    public:
    int key;
	bool empty_since_start = true;
	bool empty_after_removal = false;
};
//Mid Square Hashing Base 2
int mid_square_base2_hash_function(int key, int hash_table_size){
	int pos = key * key;
	int r = ceil(log2(hash_table_size)); // This re-size value will be provided in by instructor
		
	//Shifting left digits and keeping r digits
	int l_bits = (32 - r)/2;
	int e_bits = pos >> l_bits;
    e_bits = e_bits & (0XFFFFFFFF >> (32 - r));	
	return e_bits % hash_table_size;
}


//Insert using linear probing
bool insert_Item(item hash_table[], int input_value, int hash_table_size)
{
	int position = mid_square_base2_hash_function(input_value, hash_table_size); //using mid square  base2 hash function
	int check = 0;
	while(check < hash_table_size)
	{
		if(hash_table[position].empty_since_start || hash_table[position].empty_after_removal){
			hash_table[position].key = input_value;
			hash_table[position].empty_since_start = false;
			hash_table[position].empty_after_removal = false;
			return true;
		}else
        {
            cout <<"\nCollision occured performing linear probing.";
        }
        
		check++;
		position = (position + 1 ) % hash_table_size;
	}
	cout <<"\nBucket FULL Press -1 to end insert operation: ";
	return false;
}

void display_hash(item hash_table[], int hash_table_size)
{   cout << endl;
	for(int i=0; i < hash_table_size; i++)
	{
		if(!hash_table[i].empty_since_start && !hash_table[i].empty_after_removal){
            cout << i << " -----> " << hash_table[i].key <<endl;	
		}
		else{
			cout << i << " -----> " << endl;
		}
	}
}

int delete_item(item hash_table[], int delete_value, int hash_table_size)
{
	
	int position = mid_square_base2_hash_function(delete_value, hash_table_size); // Using mid square base2 hash function
	int bucket_checked = 0;
	while(bucket_checked < hash_table_size &&  !hash_table[position].empty_since_start)
	{
		if(hash_table[position].key == delete_value)
		{
			hash_table[position].key = 0;
			hash_table[position].empty_since_start = false;
			hash_table[position].empty_after_removal = true;
			cout << delete_value << " deleted successfully.";
			return true;
		}
		bucket_checked++;
		position = (position + 1) % hash_table_size;
	}
	cout <<delete_value << " not found in the table.";
	return false;
}

void search_item(item hash_table[], int search_value, int hash_table_size)
{
	for(int i=0; i < hash_table_size; i++)
	{
		if(hash_table[i].key == search_value){
			cout << search_value << " was found in the table!" << endl;
			return;
		}
	}
	cout << "Item not found in table." << endl;
	return;
}


int main()
{
    int hash_table_size, input_value, search_value, delete_value;
    cout <<"Enter the Size of Table: ";
    cin >> hash_table_size;
	item hash_table[hash_table_size];
	//Inserting key in hash table: 
    cout <<"\nEnter the element to insert until -1: ";
    cin >> input_value;
    while(input_value != -1){
        if(insert_Item(hash_table, input_value, hash_table_size) == true)
            cout << input_value << " inserted successfully." << endl;
        cin >> input_value;
    }
    
    cout <<"\nEnter value you want to search: ";
    cin >> search_value;
    //searching hash table for search value entered
    search_item(hash_table, search_value, hash_table_size);
    //Deleting value
	cout <<"\nEnter the value you want to delete: ";
	cin >> delete_value;
	delete_item(hash_table, delete_value, hash_table_size);
    //display the hash table
    display_hash(hash_table, hash_table_size);
	return 0;
}