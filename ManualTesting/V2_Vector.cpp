#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Finds the maximum value in a vector of integers.
 *
 * Performs a single linear scan comparing each element against
 * a running maximum, starting from the first element.
 *
 * @param arr  A vector of integers to search. Passed by value —
 *             the original vector is not modified.
 *
 * @return The maximum integer value found in the vector.
 *         Returns -1 if arr.size() < 2 (not enough elements).
 *
 * @note The minimum size requirement of 2 mirrors the contract of
 *       getSecMaxNV2(), since this function exists primarily to
 *       support second-maximum searches.
 *
 * @note Passing by value means a full copy of the vector is made on
 *       each call. For large vectors, prefer passing by const reference.
 *
 * @example
 *   vector<int> v = {3, 7, 1, 9, 4};
 *   getMaxNV2(v); // Returns 9
 */
int getMaxNV2(vector<int> arr)
{
	if (arr.size() < 2)
		return -1; // Error: Not enough elements to find the maximum

	int max = arr[0];

	for (size_t i = 1; i < arr.size(); i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

/**
 * @brief Finds the second largest distinct value in a vector of integers.
 *
 * Seeds the search by comparing the first two elements to establish
 * initial max and secMax values, then iterates through the remainder
 * of the vector updating both trackers as needed.
 *
 * Logic per element:
 *   - Exceeds max      → old max becomes secMax, element becomes max.
 *   - Between secMax and max (exclusive), and not equal to max
 *                      → element becomes the new secMax.
 *   - Otherwise        → element is ignored.
 *
 * @param arr  A vector of integers to search. Passed by value —
 *             the original vector is not modified.
 *
 * @return The second largest distinct integer value in the vector.
 *         Returns -1 if arr.size() < 2, or if all elements are identical
 *         (no distinct second maximum exists).
 *
 * @note Duplicate values equal to the maximum are intentionally skipped
 *       to enforce the "distinct" requirement.
 *
 * @example
 *   vector<int> v = {3, 7, 1, 9, 4};
 *   getSecMaxNV2(v); // Returns 7
 *
 *   vector<int> same = {5, 5, 5};
 *   getSecMaxNV2(same); // Returns -1
 */
int getSecMaxNV2(vector<int> arr)
{
	if (arr.size() < 2)
		return -1; // Error: Not enough elements to find the second maximum

	int max, secMax;

	if (arr[0] > arr[1])
	{
		max = arr[0];
		secMax = arr[1];
	}
	else
	{
		max = arr[1];
		secMax = arr[0];
	}

	for (size_t i = 2; i < arr.size(); i++)
	{
		if (arr[i] > max)
		{
			secMax = max;
			max = arr[i];
		}
		else if (arr[i] > secMax && arr[i] != max)
		{
			secMax = arr[i];
		}
	}

	if (max == secMax)
		return -1; // Error: All elements are the same, no second maximum

	return secMax;
}

/**
 * @brief Independently verifies the second maximum value for test validation.
 *
 * Used as a double-check oracle against getSecMaxNV2(). First retrieves
 * the true maximum via getMaxNV2(), then performs a separate linear scan
 * to find the largest value strictly less than that maximum.
 *
 * Because this function uses a completely different algorithm from
 * getSecMaxNV2(), agreement between the two results gives high confidence
 * that the primary function is correct.
 *
 * @param arr  A vector of integers to search. Passed by value —
 *             the original vector is not modified.
 *
 * @return The second largest distinct integer value in the vector.
 *         Returns -1 if no such value exists (e.g., all elements identical).
 *
 * @warning Initializes secMax to -99999. Vectors containing only values
 *          below this threshold would silently produce wrong results.
 *          This is acceptable here because the test suite generates values
 *          strictly within [-100, 100].
 *
 * @example
 *   vector<int> v = {3, 7, 1, 9, 4};
 *   doubleCheckForSecMaxV2(v); // Returns 7
 */
int doubleCheckForSecMaxV2(vector<int> arr)
{
	size_t size = arr.size();
	int secMax = -99999; // Initialize to a very small number
	bool found = false;
	int max = getMaxNV2(arr);

	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] > secMax && arr[i] != max)
		{
			secMax = arr[i];
			found = true;
		}
	}

	if (!found)
		return -1; // Error: No second maximum found (all elements are the same)

	return secMax;

}

/**
 * @brief Prints all elements of an integer vector in bracketed format.
 *
 * Outputs the vector to stdout as: [a, b, c, ...]
 * Elements are comma-space separated with no trailing comma after the
 * last element. A newline is appended at the end via endl.
 *
 * @param arr  A vector of integers to print. Passed by value —
 *             the original vector is not modified.
 *
 * @example
 *   vector<int> v = {1, 2, 3};
 *   printArrV2(v); // Outputs: [1, 2, 3]
 */
void printArrV2(vector<int> arr)
{
	size_t size = arr.size();
	cout << "[";
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i];
		if (i < size - 1)
			cout << ", ";
	}
	cout << "]" << endl;
}

/**
 * @brief Runs a randomized test suite to validate getSecMaxNV2().
 *
 * Generates between 20 and 120 random test cases. For each test:
 *   - Creates a vector of 2–20 elements filled with values in [-100, 100].
 *   - Calls getSecMaxNV2()          (the function under test).
 *   - Calls doubleCheckForSecMaxV2() (the reference oracle).
 *   - Compares both results and records pass/fail.
 *
 * The first 10 test cases are always printed to stdout for manual
 * inspection, regardless of pass/fail status. A full summary is
 * printed at the end.
 *
 * Key differences from V1:
 *   - Uses std::vector instead of raw arrays — no manual new/delete needed.
 *   - Uses static_cast<unsigned int>(time(nullptr)) for cleaner seeding.
 *
 * @note Uses srand(time(nullptr)) for non-deterministic seeding, so
 *       test counts and values vary between runs.
 *
 * @note No parameters, no return value. Intended as a standalone
 *       development-time correctness check.
 *
 * @example Output (abbreviated):
 *   Running 58 random tests...
 *
 *   Test 1 PASSED: [12, -5, 3, 99, 7]
 *    -> Second Max: 12
 *   ...
 *   ========== TEST SUMMARY ==========
 *   Total Tests:   58
 *   Passed:        58 [OK]
 *   Failed:         0 [X]
 *   Success Rate: 100%
 */
void runTestCodeV2()
{
	srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator with the current time

	int passed = 0;
	int failed = 0;
	int testNumber = rand() % 101 + 20; // Generate a random test number between 20 and 120
	cout << "Running " << testNumber << " random tests..." << endl;

	for (int testIndex = 0; testIndex < testNumber; testIndex++)
	{
		int size = rand() % 19 + 2; // Generate a random size between 2 and 20


		vector<int> arr(size);

		for (int arrIndex = 0; arrIndex < size; arrIndex++)
		{
			arr[arrIndex] = rand() % 200 - 100; // Fill the array with random numbers between -100 and 100
		}

		int result = getSecMaxNV2(arr);
		int doubleCheckResult = doubleCheckForSecMaxV2(arr);

		if (result == doubleCheckResult)
		{
			passed++;
			if (testIndex < 10) {
				cout << "\nTest " << testIndex + 1 << " PASSED: ";
				printArrV2(arr);
				cout << " -> Second Max: " << result << endl;
			}
		}
		else
		{
			failed++;
			if (testIndex < 10) {
				cout << "\nTest " << testIndex + 1 << " FAILED: ";
				printArrV2(arr);
				cout << "Expected second maximum: " << doubleCheckResult << ", but got: " << result << endl;
			}
		}
	}

	cout << "\n========== TEST SUMMARY ==========" << endl;
	cout << "Total Tests: " << testNumber << endl;
	cout << "Passed: " << passed << " [OK]" << endl;
	cout << "Failed: " << failed << " [X]" << endl;
	cout << "Success Rate: " << (passed * 100.0 / testNumber) << "%" << endl;
}


int main()
{
	runTestCodeV2();
	return 0;

}

