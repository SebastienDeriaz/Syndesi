#!/bin/sh
cd arduino
rm -r syndesicp 
mkdir syndesicp
mkdir syndesicp/include
mkdir syndesicp/src
mkdir syndesicp/examples

touch syndesicp/keywords.txt

touch syndesicp/examples/test.ino


cp ../include/*.hpp syndesicp
cp ../src/*.cpp syndesicp

zip -r syndesicp.zip syndesicp