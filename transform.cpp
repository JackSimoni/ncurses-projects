#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

char mapData; // Will be a temporary storage space to get characters and transfer them.
int counterBuffer = 0; // This counter is a temporary placeholder used to gauge the maximum COL value in a raw .txt file. 
int counterMax = 0; // This counter will display the max COL value in a given raw .txt file.
int counterLineBreak = 0; // Counts the number of line breaks in a .txt file
int counterLineCount = 0; // Counts the number of lines in a .txt file

string mapDataRawTitle;
string mapDataRefinedTitle;

std::cout << "Name of raw map .txt file you're reading from?: ";
std::cin >> mapDataRawTitle;

std::cout << "Name of refined map .txt file you're creating?: ";
std::cin >> mapDataRefinedTitle;

std::ifstream mapDataRaw(mapDataRawTitle); // Create an input file stream for the raw map .txt file
std::ofstream mapDataRefined(mapDataRefinedTitle); // Create an output file stream for the refined .txt file

while(mapDataRaw.get(mapData))
{
  if(mapData != '\n')
  {
    counterBuffer++; // Increment the counter until a line break is reached.
  }

  else
  {
    if(counterBuffer > counterMax)
      counterMax = counterBuffer;  // If the buffer value is the current maximum, assign this value to the counterMax value.

    counterBuffer = 0;  // Reset counter buffer once line break is detected.
  }
}

counterBuffer = 0; // Reset value for future use. Has same use, being that it measures COL size.

mapDataRaw.clear();
mapDataRaw.seekg(0, mapDataRaw.beg);

while(mapDataRaw.get(mapData))
{
  if(mapData != '\n')
  {
    counterBuffer++; // Keep incrementing to find COL length until a line break.
    mapDataRefined.put(mapData); // Write raw file data to refined file.
  }

  else
  {
    for(int i = 0; i < (counterMax - counterBuffer); i++)
      mapDataRefined.put(' '); // Write n = counterMax - counterBuffer spaces to create rectangle/array compatible .txt file.

    mapDataRefined.put('\n'); // Put a line break after rectangular structure has been established.
    counterBuffer = 0; // Reset COL length and repeat process until all of raw .txt data has been written to refined .txt file.
    counterLineCount++;
  }

}

mapDataRefined.close();

// Now this refined file is "array compatible" in so far as it has made the raw .txt file's contents compressed into an N x M matrix.

string mapDataFinalTitle;

std::cout << "Name of final map .txt file you're creating?: ";
std::cin >> mapDataFinalTitle;

std::ifstream mapDataRefinedI(mapDataRefinedTitle);
std::ofstream mapDataFinal(mapDataFinalTitle);

mapDataRefinedI.clear();
mapDataRefinedI.seekg(0, mapDataRefined.beg);


counterBuffer = 0;

mapDataFinal.put('{');
mapDataFinal.put('{');

while(mapDataRefinedI.get(mapData))
{

  if(mapData == '\n')
  {
    if(counterLineBreak != (counterLineCount - 1))
    {
      mapDataFinal.put(',');
      mapDataFinal.put('\n');
      mapDataFinal.put('{');
    }

    counterLineBreak++;
  }

  else
  {
   counterBuffer++;
   mapDataFinal.put('\'');

   switch(mapData)
   {

     case '\\':
     mapDataFinal.put('\\');
     mapDataFinal.put('\\');
     break;

     case '\'':
     mapDataFinal.put('\\');
     mapDataFinal.put('\'');
     break;

     case '\"':
     mapDataFinal.put('\\');
     mapDataFinal.put('\"');
     break;

     default:
     mapDataFinal.put(mapData);
     break;
   }


   mapDataFinal.put('\'');
   if(counterBuffer % (counterMax) == 0)
   mapDataFinal.put('}');
   if(counterBuffer % (counterMax) != 0 && counterLineBreak != counterLineCount)
   mapDataFinal.put(',');
  }


}

mapDataFinal.put('}');
mapDataFinal.put(';');

mapDataRefinedI.close();
mapDataRaw.close();
mapDataFinal.close();






return 0;
}
