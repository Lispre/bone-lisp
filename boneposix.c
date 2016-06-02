/* boneposix.c -- POSIX bindings for Bone Lisp.
 * Copyright (C) 2016 Wolfgang Jaehrling
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "bone.h"

DEFSUB(getpid) { bone_result(int2any(getpid())); }
DEFSUB(getuid) { bone_result(int2any(getuid())); }
DEFSUB(geteuid) { bone_result(int2any(geteuid())); }
DEFSUB(getgid) { bone_result(int2any(getgid())); }
DEFSUB(getegid) { bone_result(int2any(getegid())); }
my any getenv_any(const char *name) { char *res = getenv(name); return res ? charp2str(res) : BFALSE; }
my void getenv_str(any x) { char *name = str2charp(x); bone_result(getenv_any(name)); free(name); }
my void getenv_sym(any x) { bone_result(getenv_any(symtext(x))); }
DEFSUB(getenv) { if(is_str(args[0])) getenv_str(args[0]); else getenv_sym(args[0]); }

void bone_posix_init() {
  bone_register_csub(CSUB_getpid, "getpid", 0, 0);
  bone_register_csub(CSUB_getuid, "getuid", 0, 0);
  bone_register_csub(CSUB_geteuid, "geteuid", 0, 0);
  bone_register_csub(CSUB_getgid, "getgid", 0, 0);
  bone_register_csub(CSUB_getegid, "getegid", 0, 0);
  bone_register_csub(CSUB_getenv, "getenv?", 1, 0);
}