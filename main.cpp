#include <iostream>
#include <cstdio>
using namespace std;

void standard();
void policy();
void measure_custom();

int main() {
    freopen("output.txt", "w", stdout);

    cout << "Necheporenko Mariia K-25, none_of performance study\n";
    cout << "=====================================================\n\n";

    standard();
    cout << "\n============================================\n\n";

    policy();
    cout << "\n============================================\n\n";

    measure_custom();
    cout << "\n============================================\n\n";

    cout << "\nAll experiments completed successfully.\n";

    fclose(stdout);
    return 0;
}