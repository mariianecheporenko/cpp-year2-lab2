#include <iostream>
using namespace std;

void standard();
void policy();
void custom();

int main() {
    int choice = 0;
    using Experiment = void (*)();

    // Array of available experiments
    Experiment experiments[] = {
        standard, policy, custom,
    };
    const size_t N = sizeof(experiments) / sizeof(Experiment);

    cout << " Necheporenko Mariia K-25, none_of performance study\n";
    cout << "=====================================================\n\n";
    cout << "Select experiment to run:\n";
    cout << "  1 - Standard std::none_of (no policy)\n";
    cout << "  2 - std::none_of with execution policies\n";
    cout << "  3 - Custom parallel none_of implementation\n\n";
    cout << "Enter your choice (1, 2, or 3): ";

    cin >> choice;

    if (cin && choice >= 1 && choice <= static_cast<int>(N))
        experiments[choice - 1]();
    else
        cout << "Invalid input. Please enter 1, 2, or 3.\n";

    return 0;
}
