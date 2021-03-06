// Project3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// How to make the hash table:
// HashTable<NvraRecord>* makeHashTable(OULinkedList<NvraRecord>* linkedRecords)

/*
OULinkedLIst<T> ** table = NULL;
.
.
.
.
OULinkedList<T> ** newTable = new OULinkedList<T>* [newBaseCapacity];
// have a loop to copy the old linkedlist to the newBaseCapacity linked list

	newTable[i] = new OULinkedList<T>(comparator);

newTable[bucketNum] -> insert (item);


*/

/* IN HEAP
// memory where the OULinkedList is
-------------------------
head
-------------------------

-------------------------

-------------------------
tail
-------------------------

-------------------------
//another memory where another OULinkedList is
-------------------------
head
-------------------------

-------------------------

-------------------------
tail
-------------------------

-------------------------
.
.
.
// memory where the newBaseCapacity (0 to newBaseCapacity -1)
-------------------------
0 points to a OULinkedList
-------------------------
1 point to another OULinkedList
-------------------------
.
.
.
-------------------------
newBaseCapacity -1
-------------------------




*/

/*
on HashTable.h
change on the second constructor:
unsigned long size = DEFAULT_TABLE_SIZE;
to
unsigned long size, ;
*/

/*
hasher know the record ID number
getBuckerNumber know the size of the hash table
*/


/*the avl tree have log n performance when insert and removing data as long as the height difference is <= 1*/
/*some deleteing and inserting in avl tree does not cause the tree to be unbalanced then there is no problem*/

/*
destructors - delete anything with new in the class
add an empty function for OULinkedListEnumerator desctructor

do not repeat the default in the implementation

find is the different on column 0 - use hashtable

delete the new throw tableaccess

For HashTableEnumerator:
advancement in next only like Project 2
peek() and hasNext() return NULL or false if it's at the end

*/


/*
2-3 tree
height log2 n or log3 n
overall performance (insert, search, delete) : log2 n or log3 n

for exam: if iti's a valid 2-3 tree

show that it has the similar performance characteristic as AVL & red-black tree
ds7 slide 159 for time complexity

ds7 slide 233 b-tree

ds7 slide 235 splay tree
rearranging the tree to put the most search item to the top
ignore if it's balance 


ds8 Priority Structures
we want the one with the highest priority on the root of the tree (top of the tree)

Standard/Priority heap (this is not the same as heap / free storage)
we care about top to bottom. NOT left and right like the other trees
tree inside of an array
for maximum heap
insertion - log n
remove - 

*/

/*
Project 4
zigzag - call zag on the child then zig on itself
zagzig - call zig on the child then zag on itself
*/
int main()
{
    return 0;
}

