#!/bin/sh
cd arduino
rm -r syndesicp 
mkdir syndesicp
mkdir syndesicp/include
mkdir syndesicp/src
mkdir syndesicp/user_config
mkdir syndesicp/examples

touch syndesicp/keywords.txt

touch syndesicp/examples/test.ino


cp ../include/*.hpp syndesicp
cp ../src/*.cpp syndesicp
cp ../user_config/*.hpp syndesicp

zip -r syndesicp.zip syndesicp