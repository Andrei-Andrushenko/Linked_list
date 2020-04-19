#include "list.h"
#include <stdio.h>
#include <stdlib.h>

static void AssertEq(int expected, int actual, const char* msg) {
  if (expected != actual) {
    printf("Test failed: %s\n expected %d but got %d\n", msg, expected, actual);
    exit(-1);
  }
}

int main(void) {
  List* list = NewList();
  List* list2 = NewList();
  AssertEq(0, Length(list), "empty list length should be zero");
  Append(list, 42);
  Append(list2, 100);
  AssertEq(1, Length(list), "Length([42]) should be 1");
  AssertEq(42, GetAt(list, 0), "GetAt([42], 0) should be 42");
  Prepend(list, 25);
  Prepend(list, 10);
  AssertEq(3, Length(list), "Length([10] [25] [42]) should be 3");
  AssertEq(10, GetAt(list, 0), "GetAt(list, 0) should be 10");
  AssertEq(42, Pop(list), "Pop(list) should be 42");
  AssertEq(2, Length(list), "Length([10] [42]) should be 2");
  AssertEq(10, Dequeue(list), "Dequeue(list) should be 10");
  AppendAll(list, list2);
  AssertEq(2, Length(list), "should be 2");
  InsertAt(list, 0, 10);
  AssertEq(10, GetAt(list, 1), "should be 10");
  RemoveAt(list, 2);
  AssertEq(-1, GetAt(list, 2), "should be 100");
  RemoveAll(list);
  AssertEq(0, Length(list), "should be 0");
  DestroyList(list);
}