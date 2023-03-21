mergesort:
	/bin/rm -f merged_pass_* sorted_run_* output.txt main analysis.txt
	g++ main.cpp -o main
clean:
	/bin/rm -f merged_pass_* sorted_run_* output.txt main analysis.txt

