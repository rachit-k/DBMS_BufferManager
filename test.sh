START=1
END=10
operations=(deletion)
for operation in "${operations[@]}"
do
    t=0
    p=0

    for (( c=$START; c<=$END; c++ ))
    do

        t=$(( t + 1 ))
        if [[ $operation == linearsearch ]]; then
           result=`./tester linearsearch TestCases_Automated/LinearSearch/input/input_$c.txt TestCases_Automated/LinearSearch/query/query_$c.txt`
           retval=$?
           diff output TestCases_Automated/LinearSearch/binary/output/output_$c
           if [[ "$retval" == "0" ]]; then
                p=$(( p + 1 ))
           fi
        fi

        if [[ $operation == binarysearch ]]; then
            result=`./tester binarysearch TestCases_Automated/BinarySearch/input/input_$c.txt TestCases_Automated/BinarySearch/query/query_$c.txt`
            retval=$?
            diff output TestCases_Automated/BinarySearch/binary/output/output_$c
            if [[ "$retval" == "0" ]]; then
                p=$(( p + 1 ))
            fi
        fi

        if [[ $operation == deletion ]]; then
            result=`./deletion Tests/Deletion/binary/input/input_$c Tests/Deletion/query/query_$c.txt`
            retval=$?
            diff input_$c TestCases_Automated/Deletion/binary/output/output_$c
            if [[ "$retval" == "0" ]]; then
                p=$(( p + 1 ))
            fi
            # diff input1 TestCases_Automated/Deletion/binary/output/output_1 ## diff doesn't work for deletion (piazza discussion)
        fi

        if [[ $operation == join1 ]]; then
            result=`./tester join1 TestCases_Automated/Join1/input/input1_$c.txt TestCases_Automated/Join1/input/input2_$c.txt`
            retval=$?
            # diff output  TestCases_Automated/Join1/binary/output/output_$c ##diff testing doesn't work for join1 since order not guaranteed
            if [[ "$retval" == "0" ]]; then
                p=$(( p + 1 ))
            fi
        fi

        if [[ $operation == join2 ]]; then
            result=`./tester join2 TestCases_Automated/Join2/input/input1_$c.txt TestCases_Automated/Join2/input/input2_$c.txt`
            retval=$?
            diff output  TestCases_Automated/Join2/binary/output/output_$c
            if [[ "$retval" == "0" ]]; then
                p=$(( p + 1 ))
            fi
        fi
    done;
    echo "$operation: tests=$t passed=$p"
    echo ""
done;
