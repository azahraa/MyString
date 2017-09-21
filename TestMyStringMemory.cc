
//
// CS251 Data Structures
// test for MyString class
//

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "MyString.h"

void
test1() {
	const char* s1 = "Hello world";
	MyString ms1(s1);
	printf("Creating mystring1 : %s\n", ms1.cStr());
	MyString ms2(ms1);
	printf("Duplicating mystring1 into mystring2 : %s\n", ms2.cStr());
	printf("Length of mystring1 : %d\n", ms1.length());
	MyString msEmpty;
	printf("Making empty myString : %s\n", msEmpty.cStr());
}


void
test2() {
  const char *s1 = "Hello world";
  MyString ms1(s1);
  MyString ms2(ms1.substring(2,3));
	MyString ms3(ms1.substring(7,8));
	MyString ms4;
	ms4= ms1;
  ms4.remove(2,3);
}


void
test3() {
  MyString ms1("Hello");
  MyString ms2("world");
  MyString ms3("Hello");

  if(ms1!=ms2);
  if(ms1==ms3);
	if(ms1<=ms2);
	if(ms1>ms2);

	MyString ms4 = ms1+" "+ms2+" "+ms3;
	if(ms1[6] == ' ');
}


void
usage()
{
  // Print usage
  fprintf(stderr, "TestMyStringMemory test1|test2|test3\n");
}

int
main( int argc, char ** argv) {

  if (argc == 1) {
    usage();
    exit(1);
  }

  if ( !strcmp(argv[1], "test1")) {
    test1();
  }
  else if ( !strcmp(argv[1], "test2")) {
    test2();
  }
  else if ( !strcmp(argv[1], "test3")) {
    test3();
  }
  else {
    usage();
    exit(1);
  }

  exit(0);
}
