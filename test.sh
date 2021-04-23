make all
START=1
END=10
t=0
p=0
for (( c=$START; c<=$END; c++ ))
do
    t=$(( t + 1 ))
    result=`./join1 TestCases/Tests/Join1/binary/input/input1_$c TestCases/Tests/Join1/binary/input/input2_$c output; ./comp TestCases/Tests/Join1/binary/output/output_$c output`
    retval=$?
    # diff output  TestCases_Automated/Join1/binary/output/output_$c ##diff testing doesn't work for join1 since order not guaranteed
    if [[ "$retval" == "0" ]]; then
        p=$(( p + 1 ))
    else
        echo "Failed test case number for join1 $t"
    fi
    rm -f output
    result=`./join2 TestCases/Tests/Join2/binary/input/input1_$c TestCases/Tests/Join2/binary/input/input2_$c output; ./comp TestCases/Tests/Join2/binary/output/output_$c output`
    retval=$?
    # diff output  TestCases_Automated/Join1/binary/output/output_$c ##diff testing doesn't work for join1 since order not guaranteed
    if [[ "$retval" == "0" ]]; then
        p=$(( p + 1 ))
    else
        echo "Failed test case number for join2 $t"
    fi
    rm -f output
done;
echo "$operation: tests=$t passed=$p"
echo ""

