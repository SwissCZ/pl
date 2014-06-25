#!/bin/sh

### Initialization

OUT_PATH="../out/"
PL_CMD=$OUT_PATH"pl -e"
TEST_SUCCESS=1

cd test
echo "\nTesting..."

### Formula parser tests

# Positive test
for IN in prefix infix postfix
do
	for OUT in prefix infix postfix
	do
		$PL_CMD -i $IN -o $OUT -f "parser_"$IN"_pos_in.txt" > $OUT_PATH"parser_"$IN"_"$OUT"_pos_test.txt" 2>&1
		if ! diff "parser_"$OUT"_pos_in.txt" $OUT_PATH"parser_"$IN"_"$OUT"_pos_test.txt" > "/dev/null" 2>&1;
		then
			echo "> Formula parser: Positive test failed! ($IN to $OUT)"
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
		echo "> Formula parser: Negative test failed! ($IN syntax)"
		TEST_SUCCESS=0
	fi
done

### Axiom checker tests

# Positive test
$PL_CMD -A -f "axiom_checker_pos_in.txt" > $OUT_PATH"axiom_checker_pos_test.txt" 2>&1
if ! diff "axiom_checker_pos_out.txt" $OUT_PATH"axiom_checker_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "> Axiom checker: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -A -f "axiom_checker_neg_in.txt" > $OUT_PATH"axiom_checker_neg_test.txt" 2>&1
if ! diff "axiom_checker_neg_out.txt" $OUT_PATH"axiom_checker_neg_test.txt" > "/dev/null" 2>&1;
then
	echo "> Axiom checker: Negative test failed!"
	TEST_SUCCESS=0
fi

### Proof checker tests

# Positive test
$PL_CMD -P 0 -f "proof_checker_pos_in.txt" > $OUT_PATH"proof_checker_pos_test.txt" 2>&1
if ! diff "proof_checker_pos_out.txt" $OUT_PATH"proof_checker_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "> Proof checker: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -P 0 -f "proof_checker_neg_in.txt" > $OUT_PATH"proof_checker_neg_test.txt" 2>&1
if ! diff "proof_checker_neg_out.txt" $OUT_PATH"proof_checker_neg_test.txt" > "/dev/null" 2>&1;
then
	echo "> Proof checker: Negative test failed!"
	TEST_SUCCESS=0
fi

### Proof minimizer tests

# Positive test
$PL_CMD -M 0 -f "proof_checker_pos_in.txt" > $OUT_PATH"proof_minimizer_pos_test.txt" 2>&1
if ! diff "proof_minimizer_pos_out.txt" $OUT_PATH"proof_minimizer_pos_test.txt" > "/dev/null" 2>&1;
then
	echo "> Proof minimizer: Positive test failed!"
	TEST_SUCCESS=0
fi

# Negative test
$PL_CMD -M 0 -f "proof_minimizer_pos_out.txt" > $OUT_PATH"proof_minimizer_neg_test.txt" 2>&1
if ! diff "proof_minimizer_neg_out.txt" $OUT_PATH"proof_minimizer_neg_test.txt" > "/dev/null" 2>&1;
then
	echo "> Proof minimizer: Negative test failed!"
	TEST_SUCCESS=0
fi

### Summary

if [ $TEST_SUCCESS -eq 1 ];
then
	echo "...passed!"
else
	echo "...failed!"
fi
