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

#include "configure.h"

static int
cmd_configure_freq_sync(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static int
cmd_show_freq_sync_interface(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static int
cmd_show_freq_sync_interface_brief(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static int
cmd_configure_freq_sync_quality_opt1(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static int
cmd_configure_freq_sync_quality_opt2gen1(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

static int
cmd_configure_freq_sync_quality_opt2gen2(struct writer *w,
    struct cmd_env *env, void *arg)
{

    return 1;
}

/* ---------------------------------------------------------------------------------------*/
/* ------------------------ REGISTER COMMANDS --------------------------------------------*/
/* ---------------------------------------------------------------------------------------*/
static int
cmd_configure_ifp_freq_sync_ql_opt1_DNU(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_DNU(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"DNU",
		"This signal should not be used for synchronization",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"This signal should not be used for synchronization",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_DNU, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_EEC1(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_EEC1(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"EEC1",
		"ITU-T Option 1: Ethernet equipment clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Ethernet equipment clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_EEC1, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_PRC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_PRC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"PRC",
		"ITU-T Option 1: Primary reference clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Primary reference clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_PRC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_PRTC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_PRTC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"PRTC",
		"ITU-T Option 1: Primary reference timing clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Primary reference timing clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_PRTC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_SEC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_SEC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"SEC",
		"ITU-T Option 1: SONET equipment clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: SONET equipment clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_SEC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_SSUA(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_SSUA(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"SSU-A",
		"ITU-T Option 1: Type I or V slave clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Type I or V slave clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_SSUA, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_SSUB(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_SSUB(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"SSU-B",
		"ITU-T Option 1: Type IV slave clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Type IV slave clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_SSUB, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_eEEC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_eEEC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"eEEC",
		"ITU-T Option 1: Enhanced ethernet equipment clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Enhanced ethernet equipment clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_eEEC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_ePRC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_ePRC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ePRC",
		"ITU-T Option 1: Enhanced primary reference clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Enhanced primary reference clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_ePRC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt1_ePRTC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt1_ql_ePRTC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ePRTC",
		"ITU-T Option 1: Enhanced primary reference timing clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 1: Enhanced primary reference timing clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt1_ePRTC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_DUS(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_DUS(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"DUS",
		"This signal should not be used for synchronization",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"This signal should not be used for synchronization",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_DUS, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_EEC2(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_EEC2(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"EEC2",
		"ITU-T Option 2, Generation 1: Ethernet equipment clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Ethernet equipment clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_EEC2, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_PRS(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_PRS(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"PRS",
		"ITU-T Option 2, Generation 1: Primary reference source",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Primary reference source",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_PRS, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_PRTC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_PRTC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"PRTC",
		"ITU-T Option 2, Generation 1: Primary reference timing clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Primary reference timing clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_PRTC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_RES(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_RES(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"RES",
		"ITU-T Option 2, Generation 1: Reserved for network synchronization use",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Reserved for network synchronization use",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_RES, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_SMC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_SMC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"SMC",
		"ITU-T Option 2, Generation 1: SONET clock self timed",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: SONET clock self timed",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_SMC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_ST2(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_ST2(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ST2",
		"ITU-T Option 2, Generation 1: Stratum 2",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Stratum 2",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_ST2, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_ST3(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_ST3(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ST3",
		"ITU-T Option 2, Generation 1: Stratum 3",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Stratum 3",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_ST3, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_STU(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_STU(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"STU",
		"ITU-T Option 2, Generation 1: Synchronized - traceability unknown",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Synchronized - traceability unknown",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_STU, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_eEEC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_eEEC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"eEEC",
		"ITU-T Option 2, Generation 1: Enhanced ethernet equipment clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Enhanced ethernet equipment clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_eEEC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_ePRC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_ePRC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ePRC",
		"ITU-T Option 2, Generation 1: Enhanced primary reference clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Enhanced primary reference clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_ePRC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen1_ePRTC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen1_ql_ePRTC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ePRTC",
		"ITU-T Option 2, Generation 1: Enhanced primary reference timing clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 1: Enhanced primary reference timing clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen1_ePRTC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_DUS(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_DUS(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"DUS",
		"This signal should not be used for synchronization",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"This signal should not be used for synchronization",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_DUS, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_EEC2(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_EEC2(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"EEC2",
		"ITU-T Option 2, Generation 2: Ethernet equipment clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Ethernet equipment clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_EEC2, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_PROV(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_PROV(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"PROV",
		"ITU-T Option 2, Generation 2: Provisionable by the network operator.",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Provisionable by the network operator.",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_PROV, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_PRS(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_PRS(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"PRS",
		"ITU-T Option 2, Generation 2: Primary reference source",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Primary reference source",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_PRS, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_PRTC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_PRTC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"PRTC",
		"ITU-T Option 2, Generation 2: Primary reference timing clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Primary reference timing clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_PRTC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_SMC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_SMC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"SMC",
		"ITU-T Option 2, Generation 2: SONET clock self timed",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: SONET clock self timed",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_SMC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_ST2(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_ST2(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ST2",
		"ITU-T Option 2, Generation 2: Stratum 2",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Stratum 2",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_ST2, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_ST3(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_ST3(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ST3",
		"ITU-T Option 2, Generation 2: Stratum 3",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Stratum 3",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_ST3, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_ST3E(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_ST3E(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ST3E",
		"ITU-T Option 2, Generation 2: Stratum 3E",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Stratum 3E",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_ST3E, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_STU(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_STU(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"STU",
		"ITU-T Option 2, Generation 2: Synchronized - traceability unknown",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Synchronized - traceability unknown",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_STU, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_TNC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_TNC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"TNC",
		"ITU-T Option 2, Generation 2: Transit node clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Transit node clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_TNC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_eEEC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_eEEC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"eEEC",
		"ITU-T Option 2, Generation 2: Enhanced ethernet equipment clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Enhanced ethernet equipment clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_eEEC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_ePRC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_ePRC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ePRC",
		"ITU-T Option 2, Generation 2: Enhanced primary reference clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Enhanced primary reference clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_ePRC, "interface");

}

static int
cmd_configure_ifp_freq_sync_ql_opt2gen2_ePRTC(struct writer *w,
	struct cmd_env *env, void *arg)
{
	return 1;
}

static void _register_opt2gen2_ql_ePRTC(struct cmd_node *root)
{
	struct cmd_node *ql = commands_new(root,
		"ePRTC",
		"ITU-T Option 2, Generation 2: Enhanced primary reference timing clock",
		cmd_check_env, NULL, "interface");
	commands_new(ql,
		NEWLINE,
		"ITU-T Option 2, Generation 2: Enhanced primary reference timing clock",
		cmd_check_env, cmd_configure_ifp_freq_sync_ql_opt2gen2_ePRTC, "interface");

}

static void _register_freq_sync_quality_level_opt_1_commands_configure(struct cmd_node *root)
{
	_register_opt1_ql_DNU(root);
	_register_opt1_ql_EEC1(root);
	_register_opt1_ql_PRC(root);
	_register_opt1_ql_PRTC(root);
	_register_opt1_ql_SEC(root);
	_register_opt1_ql_SSUA(root);
	_register_opt1_ql_SSUB(root);
	_register_opt1_ql_eEEC(root);
	_register_opt1_ql_ePRC(root);
	_register_opt1_ql_ePRTC(root);
}

static void _register_freq_sync_quality_level_opt_2gen1_commands_configure(struct cmd_node *root)
{
	_register_opt2gen1_ql_DUS(root);
	_register_opt2gen1_ql_EEC2(root);
	_register_opt2gen1_ql_PRS(root);
	_register_opt2gen1_ql_PRTC(root);
	_register_opt2gen1_ql_RES(root);
	_register_opt2gen1_ql_SMC(root);
	_register_opt2gen1_ql_ST2(root);
	_register_opt2gen1_ql_ST3(root);
	_register_opt2gen1_ql_STU(root);
	_register_opt2gen1_ql_eEEC(root);
	_register_opt2gen1_ql_ePRC(root);
	_register_opt2gen1_ql_ePRTC(root);
}

static void _register_freq_sync_quality_level_opt_2gen2_commands_configure(struct cmd_node *root)
{
	_register_opt2gen2_ql_DUS(root);
	_register_opt2gen2_ql_EEC2(root);
	_register_opt2gen2_ql_PROV(root);
	_register_opt2gen2_ql_PRS(root);
	_register_opt2gen2_ql_PRTC(root);
	_register_opt2gen2_ql_SMC(root);
	_register_opt2gen2_ql_ST2(root);
	_register_opt2gen2_ql_ST3(root);
	_register_opt2gen2_ql_ST3E(root);
	_register_opt2gen2_ql_STU(root);
	_register_opt2gen2_ql_TNC(root);
	_register_opt2gen2_ql_eEEC(root);
	_register_opt2gen2_ql_ePRC(root);
	_register_opt2gen2_ql_ePRTC(root);
}

static void _register_freq_sync_quality_opt_commands_configure(struct cmd_node *root, int check_no_env)
{
    /* configure frequency synchronization quality itu-t option 1 */
	struct cmd_node *itu = NULL;


	if (check_no_env)
	{
		itu = commands_new(root, "itu-t", "ITU-T QL options", cmd_check_no_env, NULL, "interface");
	}
	else
	{
		itu = commands_new(root, "itu-t", "ITU-T QL options", NULL, NULL, NULL);
	}
	

	struct cmd_node *option = commands_new(
		itu,
		"option",
		"ITU-T QL options",
		NULL, NULL, NULL);

    struct cmd_node *opt1 = commands_new(
		option,
		"1",
		"ITU-T QL option 1",
		NULL, NULL, NULL);

	if (check_no_env)
	{
		commands_new(
			opt1,
			NEWLINE,
			"ITU-T QL option 1",
			cmd_check_no_env, cmd_configure_freq_sync_quality_opt1, "interface");
	}

	/* configure frequency synchronization quality itu-t option 2 generation (1|2)*/
    struct cmd_node *opt2 = commands_new(
		option,
		"2",
		"ITU-T QL option 2",
		NULL, NULL, NULL);

    struct cmd_node *generation = commands_new(
		opt2,
		"generation",
		"ITU-T QL option 2 generation",
		NULL, NULL, NULL);

    struct cmd_node *opt2gen1 = commands_new(
		generation,
		"1",
		"ITU-T QL option 2, generation 1",
		NULL, NULL, NULL);

	if (check_no_env)
	{
		commands_new(
			opt2gen1,
			NEWLINE,
			"ITU-T QL option 2",
			cmd_check_no_env, cmd_configure_freq_sync_quality_opt2gen1, "interface");
	}

    struct cmd_node *opt2gen2 = commands_new(
		generation,
		"2",
		"ITU-T QL option 2, generation 2",
		NULL, NULL, NULL);

	if (check_no_env)
	{
		commands_new(
			opt2gen2,
			NEWLINE,
			"ITU-T QL option 2, generation 2",
			cmd_check_no_env, cmd_configure_freq_sync_quality_opt2gen2, "interface");
	}

	_register_freq_sync_quality_level_opt_1_commands_configure(opt1);
	_register_freq_sync_quality_level_opt_2gen1_commands_configure(opt2gen1);
	_register_freq_sync_quality_level_opt_2gen2_commands_configure(opt2gen2);
}

static void _register_freq_sync_quality_exact_commands_configure(struct cmd_node *root)
{
	struct cmd_node *exact = commands_new(
		root,
		"exact",
		"Specify the exact QL value to use",
		NULL, NULL, NULL);

	_register_freq_sync_quality_opt_commands_configure(exact, 0);
}

static void _register_freq_sync_quality_transmit_commands_configure(struct cmd_node *root)
{
	struct cmd_node *transmit = commands_new(
		root,
		"transmit",
		"Set the quality level to be transmitted",
		cmd_check_env, NULL, "interface");

	_register_freq_sync_quality_exact_commands_configure(transmit);
}

static void _register_freq_sync_quality_receive_commands_configure(struct cmd_node *root)
{
	struct cmd_node *receive = commands_new(
		root,
		"receive",
		"Adjust the received quality level",
		cmd_check_env, NULL, "interface");

	_register_freq_sync_quality_exact_commands_configure(receive);
}

static void _register_freq_sync_commands_configure(struct cmd_node *root)
{
	commands_new(
		root,
		NEWLINE,
		"Frequency Synchronization configuration",
		NULL, cmd_configure_freq_sync, NULL);

    /* configure frequency synchronization wait-to-restore VALUE */
    struct cmd_node *wait_to_restore = commands_new(
		root,
		"wait-to-restore",
		"Set the wait-to-restore time",
		cmd_check_no_env, NULL, "interface");

    commands_new(
		wait_to_restore,
		NULL,
		"Wait-to-restore time, in seconds",
		NULL, cmd_store_env_value_and_pop, "wts");

    /* configure frequency synchronization quality itu-t option */
    struct cmd_node *quality = commands_new(
		root,
		"quality",
		"Quality level option selection",
		NULL, NULL, NULL);

	_register_freq_sync_quality_opt_commands_configure(quality, 1);

	_register_freq_sync_quality_transmit_commands_configure(quality);
	_register_freq_sync_quality_receive_commands_configure(quality);

}

void register_freq_sync_commands_configure(struct cmd_node *root)
{
	cmd_restrict_ports(root);

    /* configure frequency */
    struct cmd_node *frequency = commands_new(
		root,
		"frequency",
		"Frequency Synchronization configuration",
		NULL, NULL, NULL);

    /* configure frequency synchronization */
    struct cmd_node *synchronization = commands_new(
		frequency,
		"synchronization",
		"Frequency Synchronization configuration",
		NULL, NULL, NULL);

    /* configure frequency synchronization DATA */
    _register_freq_sync_commands_configure(synchronization);
}