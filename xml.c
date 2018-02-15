#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlstring.h>
#include <libxml/parser.h>

#include "item.h"

int main (int argc, char * argv[]) {
  xmlDocPtr document;
  xmlNodePtr root, first_child, node, cur;
  item_tPtr items = NULL;
  int itemcount = 0;
  unsigned int type_found = 0;
  xmlChar * temp_char = NULL;
  const char * filename = "items.xml";
  int depth = 0;
  xmlKeepBlanksDefault(0);
  document = xmlParseFile(filename);
  if (document == NULL) exit(EXIT_FAILURE);
  root = xmlDocGetRootElement(document);
  if (root == NULL) {
    xmlFreeDoc(document);
    fprintf(stderr, "Empty file");
    exit(EXIT_FAILURE);
  }
  printf("Root is <%s> (%i)\n", root->name, root->type);
  node = root->xmlChildrenNode;
  while (node != NULL) {
    if (!xmlStrcmp(node->name, (const xmlChar *) "item")) {
      ++itemcount;
      items = (item_tPtr) realloc(items, itemcount * sizeof(item_t));
      memset(items + (sizeof(item_t) * (itemcount - 1)), 0, sizeof(item_t));
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
	exit(EXIT_FAILURE);
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
	  /*if (!xmlStrcmp(temp_char, (const xmlChar *) "fists")) {
	    items[itemcount-1].type = WPN_TYPE_FISTS;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "one-handed")) {
	    items[itemcount-1].type = WPN_TYPE_ONEHAND;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "hand")) {
	    items[itemcount-1].type = ARM_TYPE_HAND;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "chest")) {
	    items[itemcount-1].type = ARM_TYPE_CHEST;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "legs")) {
	    items[itemcount-1].type = ARM_TYPE_LEGS;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "feet")) {
	    items[itemcount-1].type = ARM_TYPE_FEET;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "head")) {
	    items[itemcount-1].type = ARM_TYPE_HEAD;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "all")) {
	    items[itemcount-1].type = ARM_TYPE_ALL;
	    }*/
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
  for (int i = 0; i < itemcount; i++) {
    printf("=======\n");
    printf("Id: %d\n", items[i].id);
    printf("Name: %s\n", items[i].name);
    printf("Class: %s\n", CLASS_STR[items[i].class - 1]);
    printf("Type: %s\n", TYPE_STR[items[i].type - 1]);
    printf("Power: %d\n", items[i].power);
    printf("=======\n");
  }
  for (int i = 0; i<itemcount; i++) {
      free(items[i].name);
  }
  free(items);
  exit(EXIT_SUCCESS);
}
