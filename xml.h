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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlstring.h>
#include <libxml/parser.h>

#include "item.h"

#ifndef GAME_XML_H_
#define GAME_XML_H_

item_tPtr readxmlfile (const char * filename, int * count) {
  xmlDocPtr document;
  xmlNodePtr root, first_child, node, cur;
  item_tPtr items = NULL;
  int itemcount = 0;
  unsigned int type_found = 0;
  xmlChar * temp_char = NULL;
  int depth = 0;
  xmlKeepBlanksDefault(0);
  document = xmlParseFile(filename);
  if (document == NULL) exit(EXIT_FAILURE);
  root = xmlDocGetRootElement(document);
  if (root == NULL) {
    xmlFreeDoc(document);
    fprintf(stderr, "Empty file");
    return NULL;
  }
  if (xmlStrcmp(root->name, (const xmlChar *) "item_list")) {
    fprintf(stderr, "Error: root element is not item_list\n");
    return NULL;
  }
  node = root->xmlChildrenNode;
  while (node != NULL) {
    if (!xmlStrcmp(node->name, (const xmlChar *) "item")) {
      ++itemcount;
      items = realloc(items, itemcount * sizeof(item_t));
      memset(items + (itemcount - 1), 0, sizeof(item_t));
      if (items == NULL) {
	errno = ENOMEM;
	perror("Couldn't realloc items\n");
	exit(EXIT_FAILURE);
      }
      temp_char = xmlGetProp(node, (const xmlChar *) "id");
      if (temp_char == NULL) {
	xmlFreeNodeList(node);
	xmlFreeNode(root);
	xmlFreeDoc(document);
	xmlCleanupParser();
	fprintf(stderr, "Invalid XML Document; no id attribute\n");
	return NULL;
      }
      items[itemcount-1].id = atoi((const char *) temp_char);
      xmlFree(temp_char);
      cur = node->xmlChildrenNode;
      while (cur != NULL) {
	if (!xmlStrcmp(cur->name, (const xmlChar *) "class")) {
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  if (!xmlStrcmp(temp_char, (const xmlChar *) "weapon")) {
	    items[itemcount-1].class = CLASS_WEAPON;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "armor")) {
	    items[itemcount-1].class = CLASS_ARMOR;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "hold")) {
	    items[itemcount-1].class = CLASS_HOLD;
	  }
	  xmlFree(temp_char);
	} else if (!xmlStrcmp(cur->name, (const xmlChar *) "type")) {
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  for (int i = 0; type_found == 0 || i < TYPE_COUNT; i++) {
	    if (!xmlStrcmp(temp_char, (const xmlChar *) TYPE_STR[i])) {
	      items[itemcount-1].type = (TYPE) i+1;
	      type_found = 1;
	    }
	  }
	  type_found = 0;
	  xmlFree(temp_char);
	} else if (!xmlStrcmp(cur->name, (const xmlChar *) "name")) {
	  items[itemcount-1].name = (char *) malloc(32);
	  memset(items[itemcount-1].name, 0, 32);
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  strncpy(items[itemcount-1].name, (const char *) temp_char, 31);
	  xmlFree(temp_char);
	} else if (!xmlStrcmp(cur->name, (const xmlChar *) "power")) {
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  items[itemcount-1].power = atoi((const char *) temp_char);
	  xmlFree(temp_char);
	}
	cur = cur->next;
      }
    }
    node = node->next;
  }
  xmlFreeNode(cur);
  xmlFreeNodeList(node);
  xmlFreeNode(root);
  xmlCleanupParser();
  *count = itemcount;
  return items;
}

#endif // GAME_XML_H_
