#!/bin/bash

cd test
for in in prefix infix postfix
do
	for out in prefix infix postfix
	do
		../output/pl -e -i $in -o $out -f $in.txt > $in\_to\_$out\_test.txt 2>&1
		if ! diff -q $out.txt $in\_to\_$out\_test.txt > /dev/null;
		then
			echo "Test '$in ---> $out' failed!"
		fi
	done
done

../output/pl -e -f axiom.txt > axiom_test.txt 2>&1
if [ $? -ne 0 ];
then
	echo "Axiom testing failed!"
fi

../output/pl -e -f proof.txt > proof_test.txt 2>&1
if [ $? -ne 0 ];
then
	echo "Proof testing failed!"
fi

echo "---\nTesting complete!"