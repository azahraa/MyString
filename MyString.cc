
// CS251 Data Structures
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include "MyString.h"

// My own implementation of strlen
int
MyString::slength(const char *s) const
{
  int count = 0;
  while(s[count] != '\0')
  {
    count++;
  }
  return count;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
{
  // Add implementation here
  // Allocate memory for _s.

  // Copy s into _s
  int size = slength(s) + 1;

  _s = new char[size];

  int i = 0;
  while(s[i] != '\0')
  {
    _s[i] = s[i];
    i++;
  }
  _s[i] = '\0';
}

// Create a MyString from a C string
MyString::MyString(const char * s)
{
  initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
  initialize(s._s);
}

// Create a MyString with an empty string
MyString::MyString()
{
  _s = new char[1];
  _s[0] = '\0';
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) {
  if (this != &other) // protect against invalid self-assignment
  {
    // deallocate old memory
    delete [] _s;

    // Initialize _s with the "other" object.
    initialize(other._s);

    // by convention, always return *this
    return *this;
  }
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
  if(i > slength(_s))
  {
    return MyString();
  }

  // Make sure that i is not beyond the end of string
  char *subString;
  subString = new char[n];
  int j = 0;
  int k = i;
  while(j < n)
  {
    subString[j++] = _s[k++];
  }

  MyString sub = MyString(subString);
  delete subString;

  return sub;

}

// Remove at most n chars starting at location i
void
MyString::remove(int i, int n)
{
  // Add implementation here

  // If i is beyond the end of string return

  // If i+n is beyond the end trunc string

  // Remove characters

  if (i > length())
  {
      return;
  }

  if (i + n > length())
  {
      return;
  }

  for(int k = 0; k < n; k++)
  {
    for(int j = i; j < length() - 1; j++)
    {
        _s[j] = _s[j + 1];
    }
  }

  _s[length() - n] = '\0';

  return;
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & s)
{
  if(slength(_s) != slength(s._s))
  {
    return false;
  }
  else
  {
    if(_s[0] != '\0' && s._s[0] != '\0')
    {
      int i;
      for(i = 0; i < slength(_s); i++)
      {
        if(_s[i] != s._s[i])
        {
          return false;
        }
      }
    }
  }
  return true;
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
  if(slength(_s) != slength(s._s))
  {
    return true;
  }
  else
  {
    if(_s[0] != '\0' && s._s[0] != '\0')
    {
      int i;
      for(i = 0; i < slength(_s); i++)
      {
        if(_s[i] != s._s[i])
        {
          return true;
        }
      }
    }
    else  // If both are empty
    {
        return true;
    }
  }
  return true;
}

// Return true if string "this" and s is less or equal
bool
MyString::operator <= (const MyString &s)
{
  int i = 0;
  int smaller;
  if(slength(_s) > slength(s._s))
  {
    if(s._s[0] == '\0')
    {
      return false;
    }
    smaller = slength(s._s);
  }
  else if(slength(s._s) > slength(_s))
  {
    if(_s[0] == '\0')
    {
      return true;
    }
    smaller = slength(_s);
  }
  else
  {
    smaller = slength(_s);
  }
  while(i < smaller)
  {
    if(_s[i] == s._s[i])
    {
      i++;
    }
    else
    {
      break;
    }
  }
  return (_s[i] - s._s[i] <= 0);
}

// Return true if string "this" is greater than s
bool
MyString::operator > (const MyString &s)
{
  int i = 0;
  int smaller;
  if(slength(_s) > slength(s._s))
  {
    if(s._s[0] == '\0')
    {
      return true;
    }
    smaller = slength(s._s);
  }
  else if(slength(s._s) > slength(_s))
  {
    if(_s[0] == '\0')
    {
      return false;
    }
    smaller = slength(_s);
  }
  else
  {
    smaller = slength(_s);
  }
  while(i < smaller)
  {
    if(_s[i] == s._s[i])
    {
      i++;
    }
    else
    {
      break;
    }
  }
  return (_s[i] - s._s[i] > 0);
}

// Return character at position i.  Return '\0' if out of bounds.
char
MyString::operator [] (int i)
{
  char y;
  if(i > slength(_s))
  {
    y = '\0';
  }
  else
  {
    char *x = new char();
    x = _s + i;
    y = *x;
  }
  return y;
}

// Return C representation of string
const char *
MyString::cStr()
{

  return _s;
}

// Get string length of this string.
int
MyString::length() const
{

  return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{

  delete [] _s;
}

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
  MyString s;
  delete s._s;

  int size = s1.length() + s2.length() + 1;

  s._s = new char[size];

  int i = 0;
  while(s1._s[i] != '\0')
  {
    s._s[i] = s1._s[i];
    i++;
  }
  int j = 0;
  while(s2._s[j] != '\0')
  {
    s._s[i++] = s2._s[j++];
  }
  s._s[i] = '\0';

return s;
}
