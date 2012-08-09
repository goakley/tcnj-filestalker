#ifndef HASHMAP_H
#define HASHMAP_H

#include "List.h"
#include <cstdlib>
#include <errno.h>

using namespace std;

template <class B>
struct HashNode
{
  B value;
  unsigned long int key;

  bool operator== (HashNode<B> rhs)
  {
    bool result = false;

    if (key == rhs.key)
      result = true;

    return result;
  }
};

template <class A> class HashMap
{
 private:
  // true implementation goes on the next line! //
  List <HashNode<A> > *buckets;
  
  // the number of buckets in the HashMap
  int bucketCount;
  
  // the number of elements in the HashMap
  int elementCount;
  
  //returns the hashcode of a key
  int getHash(unsigned long int);
 
 public:
  
  HashMap(int = 128);
  ~HashMap();
  bool add (unsigned long int, A /*&*/);
  A get(unsigned long int);
  A remove(unsigned long int);
  int getCount();
  List<A> iterator();
};

#include "../src/HashMap.icc"

#endif
