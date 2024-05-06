/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

/* Example test
TEST(GuesserTest, smoke_test)
{
    ASSERT_EQ( 1+1, 2 );
}
*/

// Test if guesses start at 0
TEST(GuesserTest, initial_guesses)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
	int initguess = my_secret.remaining();
	ASSERT_EQ(initguess, 3);
}

// Test that user is locked out when distance of guess exceeds two (brute forcing) so guesses remaining is 0
// This is essential for how guesses work and affects other tests
TEST(GuesserTest, bruteforcing_lockedout)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
	my_secret.match("The quick brown fox jumps over l");
	int guess_dec = my_secret.remaining();
	ASSERT_EQ(guess_dec, 2);
	my_secret.match("The quick brown fox jumps over the lazy dog");
	int bruteforce_l = my_secret.remaining();
	ASSERT_EQ(bruteforce_l, 0);
}

// Test that match is functional and works, using wrong and right guesses - has to take in logic from previous test
TEST(GuesserTest, match_works)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
    bool guess_wrong = my_secret.match("The quick brown fox jumps over l");
    ASSERT_EQ(guess_wrong, false); 
	bool guess_correct = my_secret.match("The quick brown fox jumps over t");
    ASSERT_EQ(guess_correct, true); 
}

// Test that distance detects guesses that are shorter than actual secret
TEST(GuesserTest, short_guess)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
    bool short_g = my_secret.match("The quick brown fox");
    ASSERT_EQ(short_g, false); 
}

// Test if secret truncates to 32 by testing if match is true or false
// If false secret was truncated to being shorter even though the strings typed out are the same, my_secret is different from guess
// Not main purpose but also covers testing strings longer than secret but not lockout
TEST(GuesserTest, shorten_secret)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
    bool trunc_secret = my_secret.match("The quick brown fox jumps over the lazy dog");
    ASSERT_EQ(trunc_secret, false); 
}

// Previous two accounted for changes greater than 2
/* distance is not public it is private so can't test directly but can reach it via public functions
// Test distance to see if it accounts for length of strings for distance
TEST(GuesserTest, string_length_diff)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
	int length_diff = my_secret.distance("The quick brown fox jumps over the lazy dog");
	ASSERT_EQ(length_diff, 12);
}
*/

// Test that guesses decrement if wrong
TEST(GuesserTest, decrement_guess)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
	my_secret.match("The quick brown fox jumps over ");
	int guess_dec = my_secret.remaining();
	ASSERT_EQ(guess_dec, 2);
}

// Test that guesses reset if secret is guessed
TEST(GuesserTest, reset_guess)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
	my_secret.match("The quick brown fox jumps over ");
	int guess_dec = my_secret.remaining();
	ASSERT_EQ(guess_dec, 2);
	my_secret.match("The quick brown fox jumps over t");
	int reset_g = my_secret.remaining();
	ASSERT_EQ(reset_g, 3);
}

// Test that when remaining guesses zero, user is locked out (all guesses are now false even if correct)
TEST(GuesserTest, user_lockedout_too_many_guesses)
{
	Guesser my_secret("The quick brown fox jumps over the lazy dog");
	my_secret.match("The quick brown fox jumps over ");
	int guess_dec = my_secret.remaining();
	ASSERT_EQ(guess_dec, 2);
	my_secret.match("The quick brown fox jumps over ");
	guess_dec = my_secret.remaining();
	ASSERT_EQ(guess_dec, 1);
	my_secret.match("The quick brown fox jumps over ");
	guess_dec = my_secret.remaining();
	ASSERT_EQ(guess_dec, 0);
	bool can_guess = my_secret.match("The quick brown fox jumps over t");
	ASSERT_EQ(can_guess, false);
}
