#!/bin/sh

TEST_SUCCESS=1

cd test
echo "Performing tests\n----------------"

### Parser tests

# Positive parser tests

for in in prefix infix postfix
do
	for out in prefix infix postfix
	do
		../out/pl -e -i $in -o $out -f $in.txt > ../out/$in\_$out\_test.txt 2>&1
		if ! diff -q $out.txt ../out/$in\_$out\_test.txt > /dev/null;
		then
			echo "Test '$in ---> $out' failed!"
			TEST_SUCCESS=0
		fi
	done
done

# Negative parser tests

for in in prefix infix postfix
do
	../out/pl -e -i $in -f $in\_error.txt > ../out/$in\_error\_test.txt 2>&1
	if ! diff -q $in\_messages.txt ../out/$in\_error\_test.txt > /dev/null;
	then
		echo "Invalid $in syntax test failed!"
		TEST_SUCCESS=0
	fi
done

### Axiom checker testing

# Positive axioms test

../out/pl -A -f axiom.txt
if [ $? -ne 0 ];
then
	echo "Positive axioms testing failed!"
	TEST_SUCCESS=0
fi

# Negative axioms test

../out/pl -e -A -f axiom\_error.txt > ../out/axiom\_error\_test.txt 2>&1
if ! diff -q axiom_error_messages.txt ../out/axiom\_error\_test.txt > /dev/null;
then
	echo "Negative axioms testing failed!"
	TEST_SUCCESS=0
fi

### Proof checker testing

# Positive proof test

../out/pl -P -f proof.txt
if [ $? -ne 0 ];
then
	echo "Test 'valid proof' failed!"
	TEST_SUCCESS=0
fi

# Negative proof test

../out/pl -P -f proof_error.txt
if [ $? -eq 0 ];
then
	echo "Test 'invalid proof' failed!"
	TEST_SUCCESS=0
fi

### Summary

if [ $TEST_SUCCESS -eq 1 ];
then
	echo "Success!"
else
	echo "----------------\nFailure!"
fi
