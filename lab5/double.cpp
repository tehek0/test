int numbers(int a, int b) {
    cerr << "Running Two Numbers Function" << endl;
    int arr[2] = {a,b};
    int twonumbers_result = 0;
    for(int i = 0; i<2;++i) {
        int number = (arr[i] >=0 ? arr[i] : -1*arr[i]);
        do {
		twonumbers_result += number % 10;
		number /= 10;
	    } while (number > 0);
    };
    return twonumbers_result;
};