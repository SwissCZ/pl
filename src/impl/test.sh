#!/bin/sh

### Initialization

OUT_PATH="../out/"
PL_CMD=$OUT_PATH"pl -e"

TEST_SUCCESS=1

cd test
echo "Performing tests\n----------------"

### Parser

# Positive test
for IN in prefix infix postfix
do
	for OUT in prefix infix postfix
	do
		$PL_CMD -i $IN -o $OUT -f $IN"_valid.txt" > $OUT_PATH"parser_"$IN"_"$OUT"_pos_test.txt" 2>&1
		if ! diff $OUT"_valid.txt" $OUT_PATH"parser_"$IN"_"$OUT"_pos_test.txt" > "/dev/null" 2>&1;
		then
			echo "Parser: Positive test failed! ($IN to $OUT)"
			TEST_SUCCESS=0
		fi
	done
done

# Negative test
for IN in prefix infix postfix
do
	$PL_CMD -i $IN -f $IN"_invalid.txt" > $OUT_PATH"parser_"$IN"_neg_test.txt" 2>&1
	if ! diff $IN"_invalid_msg.txt" $OUT_PATH"parser_"$IN"_neg_test.txt" > "/dev/null" 2>&1;
	then
		echo "Parser: Negative test failed! ($IN syntax)"
		TEST_SUCCESS=0
	fi
done

### Axiom checker

# Positive test
$PL_CMD -A -f "axiom_valid.txt" > $OUT_PATH"axiom_checker_pos_test.txt" 2>&1
if ! diff "axiom_valid_msg.txt" $OUT_PATH"axiom_checker_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "Axiom checker: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
while read LINE
do
	echo $LINE | $PL_CMD -A >> $OUT_PATH"axiom_checker_neg_test.txt" 2>&1
	if [ $? -eq 0];
	then
		echo "Axiom checker: Negative test failed! (axiom $LINE)"
		TEST_SUCCESS=0
	fi
done < "axiom_invalid.txt"

### Proof checker

# Positive test
$PL_CMD -P -f "proof_valid.txt" > $OUT_PATH"proof_checker_pos_test.txt" 2>&1
if ! diff "proof_valid_msg.txt" $OUT_PATH"proof_checker_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "Proof checker: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -P -f "proof_invalid.txt" > $OUT_PATH"proof_checker_neg_test.txt" 2>&1
if [ $? -eq 0 ];
then
	echo "Proof checker: Negative test failed!"
	TEST_SUCCESS=0
fi

### Proof optimizer

# Positive test
$PL_CMD -O -f "proof_redundant.txt" > $OUT_PATH"proof_optimizer_pos_test.txt" 2>&1
if ! diff "proof_valid.txt" $OUT_PATH"proof_optimizer_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "Proof optimizer: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -O -f "proof_valid.txt" > $OUT_PATH"proof_optimizer_neg_test.txt" 2>&1
if [ $? -eq 0 ];
then
	echo "Proof optimizer: Negative test failed!"
	TEST_SUCCESS=0
fi

### Summary

if [ $TEST_SUCCESS -eq 1 ];
then
	echo "Testing succeeded!"
else
	echo "----------------\nTesting failed!"
fi
