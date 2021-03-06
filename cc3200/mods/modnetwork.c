/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 * Copyright (c) 2015 Daniel Campora
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <std.h>

#include "py/mpstate.h"
#include MICROPY_HAL_H
#include "modnetwork.h"
#include "mpexception.h"
#include "serverstask.h"
#include "simplelink.h"


/// \module network - network configuration
///
/// This module provides network drivers and routing configuration.

void mod_network_init0(void) {
}

#if (MICROPY_PORT_HAS_TELNET || MICROPY_PORT_HAS_FTP)
STATIC mp_obj_t network_server_start(void) {
    servers_start();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(network_server_start_obj, network_server_start);

STATIC mp_obj_t network_server_stop(void) {
    servers_stop();
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(network_server_stop_obj, network_server_stop);

STATIC mp_obj_t network_server_running(void) {
    return MP_BOOL(servers_are_enabled());
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(network_server_running_obj, network_server_running);

STATIC mp_obj_t network_server_login(mp_obj_t user, mp_obj_t pass) {
    const char *_user = mp_obj_str_get_str(user);
    const char *_pass = mp_obj_str_get_str(pass);
    servers_set_login ((char *)_user, (char *)_pass);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(network_server_login_obj, network_server_login);
#endif

STATIC const mp_map_elem_t mp_module_network_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__),            MP_OBJ_NEW_QSTR(MP_QSTR_network) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_WLAN),                (mp_obj_t)&mod_network_nic_type_wlan },

#if (MICROPY_PORT_HAS_TELNET || MICROPY_PORT_HAS_FTP)
    { MP_OBJ_NEW_QSTR(MP_QSTR_start_server),        (mp_obj_t)&network_server_start_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_stop_server),         (mp_obj_t)&network_server_stop_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_server_running),      (mp_obj_t)&network_server_running_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_server_login),        (mp_obj_t)&network_server_login_obj },
#endif
};

STATIC MP_DEFINE_CONST_DICT(mp_module_network_globals, mp_module_network_globals_table);

const mp_obj_module_t mp_module_network = {
    .base = { &mp_type_module },
    .name = MP_QSTR_network,
    .globals = (mp_obj_dict_t*)&mp_module_network_globals,
};
