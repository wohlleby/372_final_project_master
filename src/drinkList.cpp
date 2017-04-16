//Developer: team 212
//purpose:  To initialize the drink list with hardcoded names for the user to choose from


#include "drinkList.h"
#include <stdlib.h>

//dynamically allocate a drink list and hard code it with names
const char ** initDrinkList() {

  //room for 10 drinks, typecasting because gcc is a little bitch
  const char ** drinkList = (const char**) malloc(10 * sizeof(char*));

  for(int i = 0; i < 10; i++) {
    //each drink can be 14 characters no including null terminator
    drinkList[i] = (const char*) malloc(15 * sizeof(char));
  }

  drinkList[0] = "Prime/Purge";
  drinkList[1] = "Cran-Apple";
  drinkList[2] = "drink three";
  drinkList[3] = "drink four";
  drinkList[4] = "drink five";
  drinkList[5] = "drink six";
  drinkList[6] = "drink seven";
  drinkList[7] = "drink eight";
  drinkList[8] = "drink nine";
  drinkList[9] = "drink ten";

  return drinkList;
}
