#include <iostream>
#include <string>

using namespace std;

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

int doubleCheckForSecMaxV1(int arr[], const int size)
{
	int secMax = -99999; // Initialize to a very small number
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
			arr[arrIndex] = rand() % 200 - 100; // Fill the array with random numbers between -100 and 100
		}

		int result = getSecMaxNV1(arr, size);
		int doubleCheckResult = doubleCheckForSecMaxV1(arr, size);

		if (result == doubleCheckResult)
		{
			passed++;
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

