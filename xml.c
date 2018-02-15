#include "xml.h"

int main (int argc, char * argv[]) {
  item_tPtr items = NULL;
  int itemcount;
  const char * filename = "items.xml";
  items = readxmlfile(filename, &itemcount);
  if (items == NULL) {
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < itemcount; i++) {
    printf("Id: %d\n", items[i].id);
    printf("Name: %s\n", items[i].name);
    printf("Class: %s\n", CLASS_STR[items[i].class - 1]);
    printf("Type: %s\n", TYPE_STR[items[i].type - 1]);
    printf("Power: %d\n", items[i].power);
    printf("=======\n");
  }
  for (int i = 0; i < itemcount; i++) {
      free(items[i].name);
  }
  free(items);
  exit(EXIT_SUCCESS);
}
