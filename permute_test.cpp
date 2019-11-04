//permute_test.cpp
#include "InputPermute.cpp"

void clean_up_files(vector<const char *> file_names)
{
    for(const char * file_name : file_names)
        remove(file_name);
}

int main(int argc, char const *argv[]) {

/*
    InputPermute ->
    (1) ::  Give input file_name (e.g. input.txt)
    (2) ::

*/

    InputPermute input = InputPermute("cycle", argv[1]);
    vector<const char *> files = input.permute(10);
    const char * test = files[0];
    input = InputPermute("test", test);

    string buffer = "";
    for(string file : files)
        buffer += file + '\n';

    cout << buffer << endl;

    // clean_up_files(files);

    remove(files[0]);

    return 0;
}
