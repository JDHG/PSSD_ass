//permute_test.cpp
#include "InputPermute.cpp"

int main(int argc, char const *argv[]) {

/*
    InputPermute ->
    (1) ::  Give input file_name (e.g. input.txt)
    (2) ::

*/

    InputPermute input = InputPermute("cycle", argv[1]);
    // input.permute_input(argv[2]);
    // cout << input.write_to_file(1) << endl;
    vector<string> files = input.permute();
    for(string file : files)
        cout << file << endl;



    return 0;
}
