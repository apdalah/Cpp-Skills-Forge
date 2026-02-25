#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Finds the maximum value in an integer array.
 *
 * Performs a single linear scan comparing each element against
 * a running maximum, starting from the first element.
 *
 * @param arr   Pointer to the integer array to search.
 * @param size  Number of elements in the array.
 *
 * @return The maximum integer value found in the array.
 *         Returns -1 if size < 2 (not enough elements).
 *
 * @note A size requirement of at least 2 is enforced because this
 *       function is designed to support second-maximum searches,
 *       which require a minimum of two elements.
 *
 * @example
 *   int arr[] = {3, 7, 1, 9, 4};
 *   getMaxNV1(arr, 5); // Returns 9
 */
int getMaxNV1(int arr[], const int size)
{
	if (size < 2)
		return -1; // Error: Not enough elements to find the maximum

	int max = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

/**
 * @brief Finds the second largest distinct value in an integer array.
 *
 * Seeds the search by comparing the first two elements to establish
 * initial max and secMax values, then iterates through the remainder
 * of the array updating both trackers as needed.
 *
 * Logic:
 *   - If a new element exceeds max  → old max becomes secMax, element becomes max.
 *   - If a new element is between secMax and max → element becomes secMax.
 *   - Duplicate values of max are ignored to ensure distinctness.
 *
 * @param arr   Pointer to the integer array to search.
 * @param size  Number of elements in the array.
 *
 * @return The second largest distinct integer value in the array.
 *         Returns -1 if size < 2, or if all elements are identical
 *         (no distinct second maximum exists).
 *
 * @example
 *   int arr[] = {3, 7, 1, 9, 4};
 *   getSecMaxNV1(arr, 5); // Returns 7
 *
 *   int same[] = {5, 5, 5};
 *   getSecMaxNV1(same, 3); // Returns -1
 */
int getSecMaxNV1(int arr[], const int size)
{
	if (size < 2)
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

	for (int i = 2; i < size; i++)
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
 * @brief Prints all elements of an integer array in bracketed format.
 *
 * Outputs the array to stdout as: [a, b, c, ...]
 * Each element is separated by a comma and space, with no trailing
 * comma after the last element. A newline is appended at the end.
 *
 * @param arr   Pointer to the integer array to print.
 * @param size  Number of elements in the array.
 *
 * @example
 *   int arr[] = {1, 2, 3};
 *   printArrV1(arr, 3); // Outputs: [1, 2, 3]
 */
void printArrV1(int arr[], const int size)
{
	cout << "[";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i];
		if (i < size - 1)
			cout << ", ";
	}
	cout << "]" << endl;
}

/**
 * @brief Independently verifies the second maximum value for test validation.
 *
 * Used as a double-check oracle against getSecMaxNV1(). First retrieves
 * the true maximum via getMaxNV1(), then performs a separate linear scan
 * to find the largest value that is strictly less than the maximum.
 *
 * Unlike getSecMaxNV1(), this function does NOT rely on a seeded
 * two-element comparison, making it a simpler and independently
 * implemented reference for correctness checking.
 *
 * @param arr   Pointer to the integer array to search.
 * @param size  Number of elements in the array.
 *
 * @return The second largest distinct integer value in the array.
 *         Returns -1 if no such value exists (e.g., all elements identical).
 *
 * @note Initializes secMax to -99999. Arrays with all values below
 *       this threshold would produce incorrect results — acceptable
 *       here since the test suite generates values in [-100, 100].
 *
 * @example
 *   int arr[] = {3, 7, 1, 9, 4};
 *   doubleCheckForSecMaxV1(arr, 5); // Returns 7
 */
int doubleCheckForSecMaxV1(int arr[], const int size)
{
	int secMax = INT_MIN; // Initialize to a very small number
	bool found = false;
	int max = getMaxNV1(arr, size);

	for (int i = 0; i < size; i++)
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
 * @brief Runs a randomized test suite to validate getSecMaxNV1().
 *
 * Generates between 20 and 120 random test cases. For each test:
 *   - Creates an array of 2–20 elements filled with values in [-100, 100].
 *   - Calls getSecMaxNV1() (the function under test).
 *   - Calls doubleCheckForSecMaxV1() (the reference oracle).
 *   - Compares both results and records pass/fail.
 *
 * The first 10 test cases are always printed to stdout for manual
 * inspection, regardless of pass/fail status. A summary is printed
 * at the end showing total, passed, failed, and success rate.
 *
 * @note Uses srand(time(0)) for non-deterministic seeding, so results
 *       vary between runs. Dynamically allocated arrays are freed after
 *       each test to prevent memory leaks.
 *
 * @note This function has no parameters and no return value — it is
 *       purely a self-contained test runner intended for development use.
 *
 * @example Output (abbreviated):
 *   Running 73 random tests...
 *   Test 1 PASSED: [4, -3, 12, 7] -> Second Max: 7
 *   ...
 *   ========== TEST SUMMARY ==========
 *   Total Tests: 73 | Passed: 73 [OK] | Failed: 0 [X]
 *   Success Rate: 100%
 */
void runTestCodeV1()
{
	srand(time(0)); // Seed the random number generator with the current time

	int passed = 0;
	int failed = 0;
	int testNumber = rand() % 101 + 20; // Generate a random test number between 20 and 120
	cout << "Running " << testNumber << " random tests..." << endl;

	for (int testIndex = 0; testIndex < testNumber; testIndex++)
	{
		int size = rand() % 19 + 2; // Generate a random size between 2 and 20


		int* arr = new int[size];

		for (int arrIndex = 0; arrIndex < size; arrIndex++)
		{
			arr[arrIndex] = rand() % 201 - 100; // Fill the array with random numbers between -100 and 100
		}

		int result = getSecMaxNV1(arr, size);
		int doubleCheckResult = doubleCheckForSecMaxV1(arr, size);

		if (result == doubleCheckResult)
		{
			passed++;
			// Only print the first 10 tests for manual inspection to avoid cluttering the output
			if (testIndex < 10) {
				cout << "\nTest " << testIndex + 1 << " PASSED: ";
				printArrV1(arr, size);
				cout << " -> Second Max: " << result << endl;
			}
		}
		else
		{
			failed++;
			if (testIndex < 10) {
				cout << "\nTest " << testIndex + 1 << " FAILED: ";
				printArrV1(arr, size);
				cout << "Expected second maximum: " << doubleCheckResult << ", but got: " << result << endl;
			}
		}

		delete[] arr; // Clean up dynamically allocated memory
	}

	cout << "\n========== TEST SUMMARY ==========" << endl;
	cout << "Total Tests: " << testNumber << endl;
	cout << "Passed: " << passed << " [OK]" << endl;
	cout << "Failed: " << failed << " [X]" << endl;
	cout << "Success Rate: " << (passed * 100.0 / testNumber) << "%" << endl;
}


//int main()
//{
//	runTestCodeV1();
//	return 0;
//
//}

