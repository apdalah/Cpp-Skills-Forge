#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

