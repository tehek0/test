int twonumbers(int arr[3]) {
    cerr << "Running Two Numbers Function" << endl;
    int twonumbers_result = 0;
    for(int i = 0; i<3;++i) {
        int number = arr[i];
        do {
		twonumbers_result += number % 10;
		number /= 10;
	    } while (number > 0);
    };
    return twonumbers_result;
};