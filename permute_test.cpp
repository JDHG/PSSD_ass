//permute_test.cpp
#include "InputPermute.cpp"

int main(int argc, char const *argv[]) {


    InputPermute input = InputPermute("cycle");
    input.permute_input(argv[2]);
    // cout << input.write_to_file(1) << endl;
    cout << input.permute() << endl;




    return 0;
}
