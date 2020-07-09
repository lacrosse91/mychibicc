#!/bin/bash
assert() {
  expected="$1"
  input="$2"

  ./tinycc "$input" > tmp.s || exit
  gcc -static -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 0 0
assert 42 42
assert 5 '2+3'
assert 8 '9-1'

echo OK