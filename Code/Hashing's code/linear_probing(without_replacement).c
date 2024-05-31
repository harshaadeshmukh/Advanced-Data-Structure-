#include <stdio.h>
#include <math.h>

#define LOAD_FACTOR 0.9

// Function to calculate the hash value
int hash(int key, int tableSize) {
    return key % tableSize;
}

int main() {
    int tableSize;
    printf("Enter the Size of the table : ");
    scanf("%d", &tableSize);

    int possibleElements = tableSize * LOAD_FACTOR;

    printf("\nYou can enter maximum of %d elements.\n", possibleElements);

    // Initialize the hash table with three columns: Index, Key, Chain
    int HashTable[tableSize][3];
	
	int j , i;
    // Initialize the hash table
    for ( j = 0; j < tableSize; j++) {
        HashTable[j][0] = j;    // Index
        HashTable[j][1] = 0;    // Key
        HashTable[j][2] = -1;   // Chain
    }

    int count = 0;
    char choice = 'Y';

    // Loop to insert elements into the hash table
    do {
        int key;
        printf("\nEnter the key : ");
        scanf("%d", &key);
        int hashVal = hash(key, tableSize);  // Calculate the hash value
        int originalHash = hashVal;
        count++;

        // If the slot is empty, insert the key directly
        if (HashTable[hashVal][1] == 0) {
            HashTable[hashVal][1] = key;
        } else {
            // Handle collisions using linear probing
            if (hash(HashTable[hashVal][1], tableSize) != hashVal) {
                // Swap the keys if the current key does not belong to this slot
                int temp = HashTable[hashVal][1];
                HashTable[hashVal][1] = key;
                key = temp;

                hashVal = hash(key, tableSize);
                originalHash = hashVal;
            }

            // Find the next available slot using linear probing
            while (HashTable[hashVal][1] != 0) {
                hashVal = hash(hashVal + 1, tableSize);
            }

            // Insert the key into the next available slot
            HashTable[hashVal][1] = key;

            // Update the chain
            while (HashTable[originalHash][2] != -1) {
                originalHash = HashTable[originalHash][2];
            }
            HashTable[originalHash][2] = hashVal;
        }

        // Ask the user if they want to continue inserting elements
        printf("\nDo you want to continue? [Y/N]\n");
        scanf(" %c", &choice);

    } while (count <= possibleElements && choice == 'Y');

	
    // Display the hash table
    printf("\n\nIndex\tKey\tChain\n\n");
    for ( j = 0; j < tableSize; j++) {
        for ( i = 0; i < 3; i++) {
            printf("%d\t", HashTable[j][i]);
        }
        printf("\n");
    }
}

