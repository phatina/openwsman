/*******************************************************************************
* Copyright (C) 2004-2006 Intel Corp. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
*  - Neither the name of Intel Corp. nor the names of its
*    contributors may be used to endorse or promote products derived from this
*    software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL Intel Corp. OR THE CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/**
 * @author Anas Nashif
 */


#ifndef __WSMAND_DAEMON_H__
#define __WSMAND_DAEMON_H__

#include <glib.h>

typedef void (*WsmandShutdownFn) (gpointer);

/* At shutdown time, handlers are executed in the
   reverse of the order in which they are added. */
void wsmand_shutdown_add_handler (WsmandShutdownFn fn,
                               gpointer      user_data);

void wsmand_shutdown_block (void);

void wsmand_shutdown_allow (void);

/* wsmand_shutdown does return.  The actual shutdown happens
   in an idle function. */

void wsmand_shutdown (void);
void wsmand_restart  (void);


gboolean wsmand_parse_options(int argc, char **argv);

gboolean wsmand_options_get_daemon_flag(void);
gboolean wsmand_options_get_no_plugins_flag(void);
int wsmand_options_get_debug_level(void);
int wsmand_options_get_syslog_level(void);
int wsmand_options_get_server_port(void);
int wsmand_options_get_server_ssl_port(void);
char *wsmand_options_get_ssl_key_file(void);
char *wsmand_options_get_ssl_cert_file(void);
char *wsmand_options_get_auth_type(void);

const char *wsmand_options_get_config_file(void);

const char **
wsmand_options_get_argv (void);



#endif /* __WSMAND_DAEMON_H__ */

