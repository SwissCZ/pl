#!/bin/sh

TEST_SUCCESS=1

echo "Performing tests\n----------------"

# Valid formulas tests

cd test
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

# Invalid formulas tests

for in in prefix infix postfix
do
	../out/pl -e -i $in -f $in\_error.txt > ../out/$in\_error\_test.txt 2>&1
	if ! diff -q $in\_messages.txt ../out/$in\_error\_test.txt > /dev/null;
	then
		echo "Test 'invalid $in syntax' failed!"
		TEST_SUCCESS=0
	fi
done

# Valid axioms test

../out/pl -A -f axiom.txt
if [ $? -ne 0 ];
then
	echo "Test 'valid axioms' failed!"
	TEST_SUCCESS=0
fi

# Invalid axioms test

../out/pl -A -f axiom_error.txt
if [ $? -eq 0 ];
then
	echo "Test 'invalid axioms' failed!"
	TEST_SUCCESS=0
fi

# Valid proof test

../out/pl -P -f proof.txt
if [ $? -ne 0 ];
then
	echo "Test 'valid proof' failed!"
	TEST_SUCCESS=0
fi

# Invalid proof test

../out/pl -P -f proof_error.txt
if [ $? -eq 0 ];
then
	echo "Test 'invalid proof' failed!"
	TEST_SUCCESS=0
fi

# Summary

if [ $TEST_SUCCESS -eq 1 ];
then
	echo "Success!"
else
	echo "-----------------\nFailure!"
fi
