/*
    A simple xml reader using libxml2
    Copyright (C) 2018 Aiden Woodruff

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
