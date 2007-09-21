

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "u/libu.h"


#include "wsman-soap.h"
#include "wsman-xml.h"
#include "wsman-soap.h"
#include "wsman-xml-serialize.h"
#include "wsman-epr.h"

#include "wsman-debug.h"


static void initialize_logging(void)
{
        debug_add_handler(wsman_debug_message_handler, DEBUG_LEVEL_ALWAYS,
                          NULL);
}

int debug_level = 0;

int main(void)
{

	if (debug_level) {
		initialize_logging();
		wsman_debug_set_level(debug_level);
	}
	WsContextH cntx = ws_create_runtime(NULL);
	SoapH soap = ws_context_get_runtime(cntx);

    WsXmlDocH doc = ws_xml_read_file( "filter.xml", "UTF-8", 0 ); 
    WsXmlNodeH node = ws_xml_get_soap_body(doc);
    if (node && (node = ws_xml_get_child(node, 0,
				    XML_NS_ENUMERATION,
				    WSENUM_ENUMERATE))) {
	    WsXmlNodeH filter = ws_xml_get_child(node,
			    0, XML_NS_WS_MAN, WSM_FILTER);
	    if (filter) {
		    node = ws_xml_get_child(filter, 0, XML_NS_CIM_BINDING, WSMB_ASSOCIATION_INSTANCES);
		    //node = ws_xml_get_child(node, 0, XML_NS_CIM_BINDING, WSMB_OBJECT);

		    epr_t *epr = wsman_get_epr(cntx, node, WSMB_OBJECT, XML_NS_CIM_BINDING );
		    if (!epr)
			    return 1;
		    printf("Resource uri: %s\n", epr->refparams.uri );
		    int i;
		    Selector *ss =
			    (Selector *) epr->refparams.selectorset.selectors.data;
		    if (ss == NULL) {
			    debug("epr->refparams.selectors.data == NULL\n");
			    return 1;
		    }
		    for (i = 0; i < epr->refparams.selectorset.selectors.count; i++) {
			    Selector *s;
			    s = ss + i;
			    XML_NODE_ATTR *a = s->attrs;
			    while (a) {
				    if (strcmp(a->name, WSM_NAME) == 0 ) {
					    printf("%s", a->value );
					    break;
				    }
				    a = a->next;
			    }
			    printf("  =  %s\n", s->value);
		    }
	    }
    }
    return 0;
}
