#!/bin/sh

### Initialization

OUT_PATH="../out/"
PL_CMD=$OUT_PATH"pl -e"

TEST_SUCCESS=1

cd test
echo "\nPerforming tests\n----------------"

### Parser

# Positive test
for IN in prefix infix postfix
do
	for OUT in prefix infix postfix
	do
		$PL_CMD -i $IN -o $OUT -f "parser_"$IN"_pos_in.txt" > $OUT_PATH"parser_"$IN"_"$OUT"_pos_test.txt" 2>&1
		if ! diff "parser_"$OUT"_pos_in.txt" $OUT_PATH"parser_"$IN"_"$OUT"_pos_test.txt" > "/dev/null" 2>&1;
		then
			echo "Formula parser: Positive test failed! ($IN to $OUT)"
			TEST_SUCCESS=0
		fi
	done
done

# Negative test
for IN in prefix infix postfix
do
	$PL_CMD -i $IN -f "parser_"$IN"_neg_in.txt" > $OUT_PATH"parser_"$IN"_neg_test.txt" 2>&1
	if ! diff "parser_"$IN"_neg_out.txt" $OUT_PATH"parser_"$IN"_neg_test.txt" > "/dev/null" 2>&1;
	then
		echo "Formula parser: Negative test failed! ($IN syntax)"
		TEST_SUCCESS=0
	fi
done

### Axiom checker

# Positive test
$PL_CMD -A -f "axiom_checker_pos_in.txt" > $OUT_PATH"axiom_checker_pos_test.txt" 2>&1
if ! diff "axiom_checker_pos_out.txt" $OUT_PATH"axiom_checker_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "Axiom checker: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -A -f "axiom_checker_neg_in.txt" > $OUT_PATH"axiom_checker_neg_test.txt" 2>&1
if ! diff "axiom_checker_neg_out.txt" $OUT_PATH"axiom_checker_neg_test.txt" > "/dev/null" 2>&1;
then
	echo "Axiom checker: Negative test failed!"
	TEST_SUCCESS=0
fi

### Proof checker

# Positive test
$PL_CMD -P 0 -f "proof_checker_pos_in.txt" > $OUT_PATH"proof_checker_pos_test.txt" 2>&1
if ! diff "proof_checker_pos_out.txt" $OUT_PATH"proof_checker_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "Proof checker: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -P 0 -f "proof_checker_neg_in.txt" > $OUT_PATH"proof_checker_neg_test.txt" 2>&1
if ! diff "proof_checker_neg_out.txt" $OUT_PATH"proof_checker_neg_test.txt" > "/dev/null" 2>&1;
then
	echo "Proof checker: Negative test failed!"
	TEST_SUCCESS=0
fi

### Proof optimizer

# Positive test
$PL_CMD -O 0 -f "proof_checker_pos_in.txt" > $OUT_PATH"proof_optimizer_pos_test.txt" 2>&1
if ! diff "proof_optimizer_pos_out.txt" $OUT_PATH"proof_optimizer_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "Proof optimizer: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -O 0 -f "proof_optimizer_pos_out.txt" > $OUT_PATH"proof_optimizer_neg_test.txt" 2>&1
if ! diff "proof_optimizer_neg_out.txt" $OUT_PATH"proof_optimizer_neg_test.txt" > "/dev/null" 2>&1;
then
	echo "Proof optimizer: Negative test failed!"
	TEST_SUCCESS=0
fi

### Summary

if [ $TEST_SUCCESS -eq 1 ];
then
	echo "Testing passed!"
else
	echo "----------------\nTesting failed!"
fi
