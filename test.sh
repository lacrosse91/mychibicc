#!/bin/bash
assert() {
  expected="$1"
  input="$2"

  ./tinycc "$input" > tmp.s
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
assert 41 ' 12 + 34 - 5 '
assert 47 '5+6*7'
assert 8 '16/2'
assert 15 '5*(9-6)'
assert 5 '+5'
assert 10 '- - 10'

echo OK
