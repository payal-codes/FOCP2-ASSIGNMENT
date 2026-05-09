
#include <iostream>   // For input/output (cin, cout)
#include <vector>     // For using std::vector
#include <string>     // For using std::string
#include <random>     // FIX 1: Modern random number generation (replaces rand/srand)
#include <algorithm>  // For std::all_of — used to check blank input

using namespace std;

// -----------------------------------------------
// Function: isBlankInput
// Returns true if the string is empty OR contains
// only spaces/tabs (e.g. "   " counts as blank).
//
// FIX 2: Old code only caught fully empty strings.
//        This catches space-only input too.
// -----------------------------------------------
bool isBlankInput(const string& text) {
    // all_of checks every character in the string.
    // ::isspace returns true for spaces, tabs, newlines, etc.
    return text.empty() || all_of(text.begin(), text.end(), ::isspace);
}

// -----------------------------------------------
// Function: replaceNameInExcuse
// Replaces every occurrence of "{name}" in the
// excuse template with the actual student name.
// (No changes needed here — this was working fine.)
// -----------------------------------------------
string replaceNameInExcuse(string excuseTemplate, const string& studentName) {
    string placeholder = "{name}";
    size_t position = excuseTemplate.find(placeholder); // Find where {name} is

    // Keep replacing as long as {name} exists in the string
    while (position != string::npos) {
        excuseTemplate.replace(position, placeholder.length(), studentName);
        position = excuseTemplate.find(placeholder); // Look for the next one
    }

    return excuseTemplate;
}

int main() {

    // -----------------------------------------------
    // FIX 1: Modern random number setup
    //
    // OLD (buggy) approach:
    //   srand(time(0));
    //   int index = rand() % total;
    //
    // Problem: rand() uses a simple algorithm that
    // produces patterns. If you run the program
    // quickly (within the same second), time(0)
    // returns the same value → same seed → same excuse!
    //
    // NEW approach uses two modern C++ tools:
    //   random_device  → gets a truly unpredictable seed
    //                    from the operating system
    //   mt19937        → a high-quality random engine
    //                    (Mersenne Twister) that produces
    //                    much better random numbers
    // -----------------------------------------------
    random_device rd;           // Asks the OS for a truly random seed
    mt19937 randomEngine(rd()); // Creates a high-quality random engine

    // -----------------------------------------------
    // List of 12 excuse templates.
    // {name} will be replaced with the student's name.
    // -----------------------------------------------
    vector<string> excuses = {
        "{name} couldn't finish the assignment because the laptop decided to update for 6 hours.",
        "{name} was about to submit the homework when the Wi-Fi mysteriously disappeared.",
        "{name} tried completing the assignment, but the keyboard suddenly stopped working.",
        "{name}'s dog sat on the laptop and somehow deleted everything.",
        "{name} finished the homework, but the printer ran out of ink on the very last page.",
        "{name} was almost done when a power cut hit the entire neighborhood.",
        "{name} accidentally submitted a recipe for pasta instead of the assignment file.",
        "{name} left the notes at home, and home is currently two cities away.",
        "{name} spent three hours on the wrong chapter because the textbook had a typo in the index.",
        "{name} got a software update notification and by the time it finished, it was 3 AM.",
        "{name} tried to email the assignment but autocorrect changed the professor's name and it bounced back.",
        "{name} was fully prepared until the cat walked across the keyboard and closed everything without saving."
    };

    // -----------------------------------------------
    // Step 1: Greet the user
    // -----------------------------------------------
    cout << "===========================================" << endl;
    cout << "       Welcome to the Student Excuse       " << endl;
    cout << "              Generator 3000               " << endl;
    cout << "===========================================" << endl;
    cout << endl;

    // -----------------------------------------------
    // Step 2: Ask for the student's name
    // -----------------------------------------------
    string studentName;
    cout << "Enter the student's name: ";
    getline(cin, studentName); // getline reads the full name, including spaces

    // -----------------------------------------------
    // Step 3: Handle blank input (FIX 2 applied here)
    //
    // OLD check:  studentName.empty()
    //   Problem: "   " (spaces only) is NOT empty,
    //   so it passed through and generated an excuse
    //   like "   couldn't finish..." — broken output!
    //
    // NEW check: isBlankInput() catches both "" and "   "
    // -----------------------------------------------
    if (isBlankInput(studentName)) {
        cout << endl;
        cout << "Oops! No name entered (spaces don't count)." << endl;
        cout << "Please run the program again and type a real name." << endl;
        return 1; // Exit the program early
    }

    // -----------------------------------------------
    // Step 4: Pick a random excuse from the list
    //
    // uniform_int_distribution ensures every index
    // from 0 to (size-1) has an equal chance of
    // being picked — no bias, no patterns.
    // -----------------------------------------------
    uniform_int_distribution<int> pickIndex(0, excuses.size() - 1);
    int randomIndex = pickIndex(randomEngine); // Pick a fair random index
    string chosenExcuse = excuses[randomIndex];

    // -----------------------------------------------
    // Step 5: Replace {name} with the actual name
    // -----------------------------------------------
    string finalExcuse = replaceNameInExcuse(chosenExcuse, studentName);

    // -----------------------------------------------
    // Step 6: Display the generated excuse
    // -----------------------------------------------
    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "   Your Official Academic Excuse is:       " << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
    cout << ">> " << finalExcuse << endl;
    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Use responsibly. Or don't. We're not cops." << endl;
    cout << "===========================================" << endl;

    return 0; // Program ended successfully
}

/*
 * ============================================
 *           SAMPLE OUTPUTS
 * ============================================
 *
 * --- Run 1 ---
 * Enter the student's name: Arjun
 *
 * >> Arjun's dog sat on the laptop and somehow deleted everything.
 *
 * --- Run 2 (run immediately after Run 1 — different excuse!) ---
 * Enter the student's name: Arjun
 *
 * >> Arjun got a software update notification and by the time it finished, it was 3 AM.
 *
 * --- Run 3: spaces-only input (now caught correctly) ---
 * Enter the student's name: (typed "    " and pressed Enter)
 *
 * >> Oops! No name entered (spaces don't count).
 *    Please run the program again and type a real name.
 *
 * --- Run 4: fully empty input ---
 * Enter the student's name: (just pressed Enter)
 *
 * >> Oops! No name entered (spaces don't count).
 *    Please run the program again and type a real name.
 *
 * --- Run 5: name with spaces ---
 * Enter the student's name: Priya Sharma
 *
 * >> Priya Sharma tried to email the assignment but autocorrect changed
 *    the professor's name and it bounced back.
 *
 * ============================================
 */
