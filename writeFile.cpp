#include <iostream>
#include <fstream>
#include <string>

// HARDCODED FOR 141 x 37 .txt MAPS. TO MAKE IT WORK FOR OTHER DIMENSIONS, JUST REPLACE EACH RESPECTIVE NUMBER WITH N - 1, N BEING THE APPROPRIATE DIMENSION.

using namespace std;

int main()
{

char mapData;
int counter = 0;
int counter_lineBr = 0;

std::ifstream mapDataRaw("testMap1.txt");
std::ofstream mapDataRefined("array1.txt");

mapDataRefined.put('{');
mapDataRefined.put('{');

while(mapDataRaw.get(mapData))
{

  if(mapData == '\n')
  {
  if(counter_lineBr != 36) // != 36 b/c COL length
  mapDataRefined.put('\n');
  if(counter_lineBr != 36)
  mapDataRefined.put('{');
  counter_lineBr++;
  }

  else
  {
   counter++;
   mapDataRefined.put('\'');
   mapDataRefined.put(mapData);
   mapDataRefined.put('\'');
   if(counter % 140 == 0) // width - 1
   mapDataRefined.put('}');
   if(counter % 140 != 0)
   mapDataRefined.put(',');
  }


}

mapDataRefined.put('}');

mapDataRaw.close();
mapDataRefined.close();

return 0;
}
