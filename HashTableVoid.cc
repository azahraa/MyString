//
// CS251
// Implementation of a HashTable that stores void *
//
#include "HashTableVoid.h"
#include <stdlib.h>
#include <string.h>

// Obtain the hash code of a key
int HashTableVoid::hash(const char * key)
{
  int sum = 0;
  int length = strlen(key);
  for(int i = 0; i < length; i++)
  {
    sum = sum + ((i + 1) * key[i]);
  }
  return sum % TableSize;
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid()
{
  _buckets = new HashTableVoidEntry*[TableSize];
  for(int i = 0;i < TableSize; i++)
  {
    _buckets[i] = NULL;
  }

}

// Add a record to the hash table. Returns true if key already exists.
// Substitute content if key already exists.
bool HashTableVoid::insertItem( const char * key, void * data)
{
  int index = hash(key);
  HashTableVoidEntry *n = _buckets[index];
  // Look for key in the table
  while(n != NULL)
  {
    if(strcmp(key, n -> _key) == 0) // If found, update data
    {
      n -> _data = data;
      return true;
    }
    n = n -> _next;
  }
  // If we did not find one, create new one
  n = new HashTableVoidEntry();
  n -> _key = strdup(key);
  n -> _data = data;
  n -> _next = _buckets[index];
  _buckets[index] = n;
  return false;
}

// Find a key in the dictionary and place in "data" the corresponding record
// Returns false if key is does not exist
bool HashTableVoid::find( const char * key, void ** data)
{
  int index = hash(key);
  HashTableVoidEntry *n = _buckets[index];
  // Look for key in the table
  while(n != NULL)
  {
    if(strcmp(key, n -> _key) == 0) // If found, update data
    {
      *data = n -> _data;
      return true;
    }
    n = n -> _next;
  }
  // If we did not find one, return false
  return false;
}

// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key)
{
  int k = hash(key);
  HashTableVoidEntry *n = _buckets[k];
  HashTableVoidEntry *prev = NULL;
  // Find entry to remove
  while(n != NULL)
  {
    if(strcmp(n -> _key, key) == 0)
    {
      // entry found
      break;
    }
    prev = n;
    n = n -> _next;
  }
  if(n == NULL)
  {
    // Did not find key
    return false;
  }
  // Two cases for prev
  if(prev == NULL)
  {
    // prev points to first element in the list
    _buckets[k] = n -> _next;
    free((void*)n -> _key);
    delete n;
  }
  else
  {
    // n is an internal node in the list
    prev -> _next = n -> _next;
    // we need to free the key because we allocated it with strdup
  free((void*)n -> _key);
  delete n;
  }
  return true;
}

// Creates an iterator object for this hash table
HashTableVoidIterator::HashTableVoidIterator(HashTableVoid * hashTable)
{
  _hashTable = hashTable;
  _currentEntry = NULL;
  _currentBucket = 0;
}

// Returns true if there is a next element. Stores data value in data.
bool HashTableVoidIterator::next(const char * & key, void * & data)  //First
{
  if(_currentEntry != NULL && _currentEntry -> _next != NULL)
  {
    key = _currentEntry -> _next -> _key;
    data = _currentEntry -> _next -> _data;
    _currentEntry = _currentEntry -> _next;
    return true;
  }

  int i = _currentBucket + 1;
  while(i < 2039 && _hashTable -> _buckets[i] == NULL)
  {
    i++;
  }

  if((i < 2039 && _hashTable -> _buckets[i] != NULL))
  {
    key =  _hashTable -> _buckets[i] -> _key;
    data =  _hashTable -> _buckets[i] -> _data;
    _currentBucket = i;
    _currentEntry =  _hashTable -> _buckets[i];
    return true;
  }
  return false;
}


// Destructor for hash table. Deletes hash table
HashTableVoid::~HashTableVoid()
{
  for(int i = 0; i < TableSize; i++)
  {
    if(_buckets[i] != NULL)
    {
      HashTableVoidEntry *n = _buckets[i];
      HashTableVoidEntry *next = NULL;
      while(n != NULL)
      {
        next = n -> _next;
        free((void*)(n -> _key));
        delete n;
        n = next;
      }
    }
  }
  delete [] _buckets;
}
