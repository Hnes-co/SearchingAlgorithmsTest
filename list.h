#include "Utility.h"
#include <iostream>

const int max_list = 1000;

template <class List_entry>
class List {
public:
//  methods of the List ADT
   List();
   int size() const;
   bool full() const;
   bool empty() const;
   void clear();
   void traverse();
   Error_code retrieve(int position, List_entry &x) const;
   Error_code replace(int position, const List_entry &x);
   Error_code remove(int position, List_entry &x);
   Error_code insert(int position, const List_entry &x);

protected:
//  data members for a contiguous list implementation
   int count;
   List_entry entry[max_list];
};

template <class List_entry>
List<List_entry>::List() 
{
    count = 0;
}

template <class List_entry>
void List<List_entry>::clear() 
{
    count = 0;
}

template <class List_entry>
bool List<List_entry>::empty() const
{
    return count == 0;
}

template <class List_entry>
bool List<List_entry>::full() const
{
    return count == max_list;
}

template <class List_entry>
int List<List_entry>::size() const
/*
Post: The function returns the number of entries in the List.
*/
{
   return count;
}


template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
      where n is the number of entries in the List, the function succeeds:
      Any entry formerly at position and all later entries have their
      position numbers increased by 1 and x is inserted at position of the List.
      Else: The function fails with a diagnostic error code.
*/
{
   if (full())
      return overflow;

   if (position < 0 || position > count)
      return utility_range_error;

   for (int i = count - 1; i >= position; i--)
      entry[i + 1] = entry[i];

   entry[position] = x;
   count++;
   return success;
}


template <class List_entry>
void List<List_entry>::traverse()
/*
Post: The action specified by function (*visit) has been performed on every
      entry of the List, beginning at position 0 and doing each in turn.
*/
{
   for (int i = 0; i < count; i++)
   {
      cout << entry[i] << endl;
   }
      
}


template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)

{

   if (position < 0 || position > count)
      return utility_range_error;


   entry[position] = x;
   return success;
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const

{


   if (position < 0 || position > count)
      return utility_range_error;


   x = entry[position];
   return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)

{
   if (empty())
      return underflow;

   if (position < 0 || position > count)
    { 
        return utility_range_error;
    }

    x = entry[position];


   for (int i = position + 1; i <= count; i++)
      entry[i - 1] = entry[i];

   
   count--;
   return success;
}