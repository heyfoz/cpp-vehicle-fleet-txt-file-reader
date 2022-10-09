// Vehicle IDs were randomly generated for academic purposes 
// Source(s) of logic assistance:  
// Gaddis, T. (2018). Starting out with C++: From control structures through objects. Pearson. 
//
// https://docs.microsoft.com/en-us/troubleshoot/developer/visualstudio/cpp/libraries/stl-sqrt-pow-functions
// https://docs.microsoft.com/en-us/cpp/standard-library/iomanip-functions?view=msvc-170

#include <iostream> // To use cin/cout
#include <iomanip>  // To access setw for output width
#include <cmath>    // To access power function for calculations
#include <string>   // To implement to_string() & length() functions
#include <fstream>  // To utilize ifstream, ofstream, fstream
using namespace std;

// Constant Variable Initialization
const string TITLE = "Fleet TXT File Input Program", AUTHOR_LINE = "By Forrest Moulin";

const string TABLE_TITLE = "Forrest's Green Vehicle Fleet Report";
const string TABLE_HEAD1 = "Vehicle ID", TABLE_HEAD2 = "Miles";
const string TABLE_HEAD3 = "Gallons", TABLE_HEAD4 = "MPG ";

const string COUNT_STR = "Fleet Count:", MILES_STR = "Total Miles:", MPG_STR = "Average MPG:";
const string BEST_STR = "Vehicle ID - Best MPG:";
const string WORST_STR = "Vehicle ID - Worst MPG:";

const int COL_GAP = 3;
// COL1: Vehicle ID, COL2: Miles, COL3: Gallons, COL4: MPG, COL5: WORST_STR
const int COL1_WIDTH = TABLE_HEAD1.length() + COL_GAP, COL2_WIDTH = TABLE_HEAD2.length() + COL_GAP;
const int COL3_WIDTH = TABLE_HEAD3.length() + COL_GAP, COL4_WIDTH = TABLE_HEAD4.length() + COL_GAP;
const int COL5_WIDTH = WORST_STR.length() + COL_GAP;
const int TABLE_WIDTH = COL1_WIDTH + COL4_WIDTH + COL5_WIDTH;

int main()
{
	// Dynamic Variable Initialization
	int fleetCount;
	double miles, gal, avgMPG, worstMPG, bestMPG, totalGal, totalMiles, fleetAvgMPG;
	string vehicleID, worstMPGStr, bestMPGStr, rowDivider = "-";

	string filePath = "C:\\Users\\Forrest\\OneDrive - The Pennsylvania State University\\FleetInput.txt";
	ifstream inputFile;

	inputFile.open(filePath);
	if (inputFile.fail())
	{
		cout << "File open failure:" << endl
			<< filePath << endl;
		inputFile.close();
		// End program in the event of file loading failure
		return 0;
	}

	// Format the row dividers to the proper width
	while (rowDivider.length() < TABLE_WIDTH)
	{
		rowDivider += "-";
	}

	fleetCount = 0;
	miles = 0.0;
	gal = 0.0;
	worstMPG = 0.0;
	bestMPG = 0.0;
	totalMiles = 0.0;
	totalGal = 0.0;
	avgMPG = 0.0;
	fleetAvgMPG = 0.0;
	vehicleID = "ABCDEFGHIJ";
	worstMPGStr = "";
	bestMPGStr = "";

	// Program Logic/Output with double precision fixed to 1 decimal
	cout << fixed << setprecision(1)
		<< TITLE << endl << AUTHOR_LINE << endl << endl
		<< right << setw((TABLE_WIDTH - TABLE_TITLE.length()) / 2 + TABLE_TITLE.length())
		
		<< TABLE_TITLE << endl << rowDivider << endl 
		<< left << setw(COL1_WIDTH) << TABLE_HEAD1 
		<< left << setw(COL2_WIDTH) << TABLE_HEAD2 
		<< left << setw(COL3_WIDTH) << TABLE_HEAD3
		<< left << setw(COL4_WIDTH) << TABLE_HEAD4 
		<< endl << rowDivider << endl;

	// While there are lines to read in the file,
	// set the variables to the read values.
	while (inputFile >> vehicleID >> miles >> gal)
	{
		avgMPG = miles / gal;
		totalGal += gal;
		totalMiles += miles;
		fleetCount++;
		
		// 1st iteration sets the floor for worst MPG
		if (fleetCount == 1)
		{
			worstMPG = avgMPG;
		}
		// Find worst MPG
		if (avgMPG < worstMPG)
		{
			worstMPG = avgMPG;
			worstMPGStr = vehicleID;
		}
		// Find best MPG
		if (avgMPG > bestMPG)
		{
			bestMPG = avgMPG;
			bestMPGStr = vehicleID;
		}
		cout << left << setw(COL1_WIDTH) << vehicleID
			<< left << setw(COL2_WIDTH) << miles
			<< left << setw(COL3_WIDTH) << gal
			<< left << setw(COL4_WIDTH) << avgMPG
			<< endl;
	}
	inputFile.close();
	// Calculate average mpg of the fleet
	fleetAvgMPG = totalMiles / totalGal;


	cout  << rowDivider << endl
		<< left << setw(COL5_WIDTH) << COUNT_STR << fleetCount << endl
		<< left << setw(COL5_WIDTH) << MILES_STR << totalMiles << endl
		<< left << setw(COL5_WIDTH) << MPG_STR << fleetAvgMPG << endl
		
		<< left << setw(COL5_WIDTH) << WORST_STR 
		<< left << setw(COL1_WIDTH) << worstMPGStr
		<< left << setw(COL4_WIDTH) << worstMPG << endl
		
		<< left << setw(COL5_WIDTH) << BEST_STR
		<< left << setw(COL1_WIDTH) << bestMPGStr 
		<< left << setw(COL4_WIDTH) << bestMPG << endl
		<< rowDivider << endl;
}
