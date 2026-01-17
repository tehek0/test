int numbers(int arr[3]) {
    cerr << "Running Three Numbers Function" << endl;
    int max = 25;
    for (int i = 0; i<3; ++i) {
        if (arr[i]>max) {
            max = arr[i];
        };
    };
    return max;
}