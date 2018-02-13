#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xmlstring.h>
#include <libxml/parser.h>

#include "item.h"

int main (int argc, char * argv[]) {
  xmlDocPtr document;
  xmlNodePtr root, first_child, node, cur;
  item_t * items = NULL;
  xmlChar * temp_char = NULL;
  const char * filename = "items.xml";
  int depth = 0;
  document = xmlParseFile(filename);
  if (document == NULL) exit(EXIT_FAILURE);
  root = xmlDocGetRootElement(document);
  if (root == NULL) {
    fprintf(stderr, "Error: empty document\n");
    xmlFreeDoc(document);
    exit(EXIT_FAILURE);
  }
  items = (item_tPtr) malloc(sizeof(item_t));
  if (items == NULL) {
    fprintf(stderr, "No memory space\n");
    exit(EXIT_FAILURE);
  }
  printf("Root is <%s> (%i)\n", root->name, root->type);
  node = root->xmlChildrenNode;
  while (node != NULL) {
    if (xmlStrcmp(node->name, (const xmlChar *) "item")) {
      temp_char = xmlGetProp(node, (const xmlChar *) "id");
	  items->id = atoi((const char *) temp_char);
	  xmlFree(temp_char);
      cur = node->xmlChildrenNode;
      while (cur != NULL) {
	if (!xmlStrcmp(cur->name, (const xmlChar *) "class")) {
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  if (xmlStrcmp(temp_char, (const xmlChar *) "weapon")) {
	    items->class = CLASS_WEAPON;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "armor")) {
	    items->class = CLASS_ARMOR;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "hold")) {
	    items->class = CLASS_HOLD;
	  }
	  xmlFree(temp_char);
	} else if (!xmlStrcmp(cur->name, (const xmlChar *) "type")) {
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  if (!xmlStrcmp(temp_char, (const xmlChar *) "fists")) {
	    items->type = WPN_TYPE_FISTS;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "one-handed")) {
	    items->type = WPN_TYPE_ONEHAND;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "hand")) {
	    items->type = ARM_TYPE_HAND;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "chest")) {
	    items->type = ARM_TYPE_CHEST;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "legs")) {
	    items->type = ARM_TYPE_LEGS;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "feet")) {
	    items->type = ARM_TYPE_FEET;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "head")) {
	    items->type = ARM_TYPE_HEAD;
	  } else if (!xmlStrcmp(temp_char, (const xmlChar *) "all")) {
	    items->type = ARM_TYPE_ALL;
	  }
	  xmlFree(temp_char);
	} else if (!xmlStrcmp(cur->name, (const xmlChar *) "name")) {
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  strcpy(items->name, (const char *) temp_char);
	  xmlFree(temp_char);
	} else if (!xmlStrcmp(cur->name, (const xmlChar *) "power")) {
	  temp_char = xmlNodeListGetString(document, cur->xmlChildrenNode, 1);
	  items->power = atoi((const char *) temp_char);
	  xmlFree(temp_char);
	}
	cur = cur->next;
      }
    }
    node = node->next;
  }
  xmlFreeNode(root);
  xmlFreeDoc(document);
  exit(EXIT_SUCCESS);
}
