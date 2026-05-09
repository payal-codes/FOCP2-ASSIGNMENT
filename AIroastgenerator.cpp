

#include <iostream>   // cin, cout
#include <vector>     // std::vector
#include <string>     // std::string
#include <cstdlib>    // rand(), srand()
#include <algorithm>  // std::all_of
#include <chrono>     // high-resolution clock for seeding rand()

// ─────────────────────────────────────────────────────────────
// replaceNamePlaceholder()
//   Replaces every "{name}" inside a roast template with the
//   actual name the user typed in.
// ─────────────────────────────────────────────────────────────
std::string replaceNamePlaceholder(std::string roastTemplate,
                                   const std::string& userName)
{
    const std::string placeholder = "{name}";
    size_t position = roastTemplate.find(placeholder);

    while (position != std::string::npos)
    {
        roastTemplate.replace(position, placeholder.length(), userName);
        position = roastTemplate.find(placeholder, position + userName.length());
    }

    return roastTemplate;
}

// ─────────────────────────────────────────────────────────────
// isBlankInput()
//   Returns true if the string is empty or only whitespace.
// ─────────────────────────────────────────────────────────────
bool isBlankInput(const std::string& text)
{
    return text.empty() ||
           std::all_of(text.begin(), text.end(), ::isspace);
}

// ─────────────────────────────────────────────────────────────
// pickRandomRoast()
//   Picks a random index that is different from lastIndex,
//   so the same roast is never shown twice in a row.
// ─────────────────────────────────────────────────────────────
int pickRandomRoast(int totalRoasts, int lastIndex)
{
    int newIndex;
    do {
        newIndex = rand() % totalRoasts;
    } while (newIndex == lastIndex && totalRoasts > 1); // retry if repeated

    return newIndex;
}

// ─────────────────────────────────────────────────────────────
// main() — program entry point
// ─────────────────────────────────────────────────────────────
int main()
{
    // ── FIX 1: Seed with nanoseconds instead of seconds ──────
    // time() only changes every second — two quick runs share
    // the same seed and get the same roast.
    // high_resolution_clock ticks in nanoseconds, making
    // seed collisions virtually impossible.
    auto now   = std::chrono::high_resolution_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>
                     (now.time_since_epoch()).count();
    srand(static_cast<unsigned int>(nanos));

    // ── Roast templates (13 total) ────────────────────────────
    // {name} is the placeholder — it gets replaced before printing
    std::vector<std::string> roastTemplates = {
        "Hey {name}, I've seen better decision-making from a coin flip.",
        "{name}, your WiFi password is probably your only secret worth keeping.",
        "Scientists confirmed it: {name} is proof that evolution sometimes takes a day off.",
        "They say every person is unique. Then there's {name}, who somehow managed to be uniquely forgettable.",
        "{name}, even your GPS gets lost trying to find your potential.",
        "I asked an AI to describe {name} and it returned a 404 error.",
        "{name}'s search history must read like a cautionary tale.",
        "The good news, {name}: you make everyone around you look smarter.",
        "{name} was voted 'Most Likely to Get Outsmarted by a Roomba'.",
        "Somewhere out there, {name}, a tree is working overtime producing the oxygen you waste.",
        "{name}, your brain must be in airplane mode — always out of service.",
        "They put {name}'s photo next to the word 'mediocre' in the dictionary, but {name} asked for a more flattering angle.",
        "Studies show {name} takes 3 minutes to remember why they walked into a room — and 4 minutes to forget the study.",
    };

    int totalRoasts = static_cast<int>(roastTemplates.size());

    // ── FIX 2: Remember the last roast to avoid repeats ──────
    // Starts at -1 so the very first pick is always free
    int lastRoastIndex = -1;

    // ── Welcome banner ────────────────────────────────────────
    std::cout << "\n";
    std::cout << "  ====================================\n";
    std::cout << "        🔥  AI Roast Generator  🔥\n";
    std::cout << "  ====================================\n";
    std::cout << "  (Warning: results may cause laughter\n";
    std::cout << "   and mild embarrassment.)\n";

    // ── FIX 3: Run-again loop ─────────────────────────────────
    // The user can get fresh roasts without restarting.
    // srand() runs only once above, so the random sequence
    // keeps advancing — no repeats from re-seeding.
    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y')
    {
        // ── Ask for the user's name ───────────────────────────
        std::string userName;

        std::cout << "\n";
        while (true)
        {
            std::cout << "  Enter your name: ";
            std::getline(std::cin, userName);

            if (isBlankInput(userName))
            {
                std::cout << "  ⚠  Oops! You left your name blank.\n"
                          << "     Even your name can't be bothered to show up?\n\n";
            }
            else
            {
                break; // valid name — move on
            }
        }

        // ── Pick a non-repeating random roast ─────────────────
        int roastIndex    = pickRandomRoast(totalRoasts, lastRoastIndex);
        lastRoastIndex    = roastIndex; // save so next pick avoids it
        std::string roast = replaceNamePlaceholder(roastTemplates[roastIndex], userName);

        // ── Print the roast ───────────────────────────────────
        std::cout << "\n  ------------------------------------\n";
        std::cout << "  " << roast << "\n";
        std::cout << "  ------------------------------------\n";
        std::cout << "\n  (Just kidding, " << userName << "! You're doing great. 😄)\n";

        // ── Ask if they want another roast ────────────────────
        std::cout << "\n  Roast someone else? (y/n): ";
        std::cin  >> playAgain;
        std::cin.ignore(); // discard the leftover newline before next getline()
    }

    std::cout << "\n  Stay roasted. Goodbye! 👋\n\n";
    return 0;
}

====
 */
