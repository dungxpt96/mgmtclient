/*
 * Copyright (c) 2023 Bernard Nguyen <dungxpt96@gmail.com>
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

#include <string.h>
#include <limits.h>

#include "display.h"
/*  ----------------------------------------------------------------------------- */
static void
_display_freq_sync_interface(struct writer *w,
    struct cmd_env *env)
{
    tag_start(w, "interface", "Interface");
    tag_attr(w, "name", "",
        cmdenv_get(env, "interface"));
    tag_end(w);
}

void 
display_freq_sync_interface_spec(struct writer *w,
    struct cmd_env *env)
{

    tag_start(w, "freqsync", "Frequency Synchronization Interface");

    _display_freq_sync_interface(w, env);

    tag_end(w);
    return;
}

/*  ----------------------------------------------------------------------------- */

void 
display_freq_sync_interfaces_all(struct writer *w,
    struct cmd_env *env)
{
    tag_start(w, "freqsync", "Frequency Synchronization Interfaces All");
    tag_end(w);
    return;
}

/*  ----------------------------------------------------------------------------- */

static const char *
_display_freq_sync_interfaces_brief_flag(void)
{
    static char flag[254];

    snprintf(flag, sizeof(flag),
        "\nFlags:  > - Up                D - Down              S - Assigned for selection" \
        "\n        d - SSM Disabled      x - Peer timed out    i - Init state" \
        "\n        s - Output squelched");
    
    return flag;
}

static const char *
_display_freq_sync_interfaces_brief_title(void)
{
    static char title[254];

    snprintf(title, sizeof(title),
        "\n%-4s %-24s %-5s %-5s %-3s %-5s %-24s" \
        "\n==== ======================== ===== ===== === ===== ========================",
        "Fl", "Interfaces", "QLrcv", "QLuse", "Pri", "QLsnd", "Output driven by");
    
    return title;
}

void 
display_freq_sync_interfaces_brief(struct writer *w,
    struct cmd_env *env)
{

    tag_start(w, "freqsync", "Frequency Synchronization Interfaces Brief");

    tag_attr(w, "tag", "",
        _display_freq_sync_interfaces_brief_flag());
    tag_attr(w, "title", "",
        _display_freq_sync_interfaces_brief_title());

    tag_end(w);
    return;
}

/*  ----------------------------------------------------------------------------- */
