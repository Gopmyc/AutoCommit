#ifndef AUTO_COMMIT_H
# define AUTO_COMMIT_H

# include <stddef.h>

typedef enum e_commit_type
{
	COMMIT_ADD,
	COMMIT_MODIFY,
	COMMIT_DELETE,
	COMMIT_RENAME,
	COMMIT_UNKNOWN
}	t_commit_type;

typedef struct s_commit_action
{
	const char	*sTag;
	const char	*sEmoji;
	const char	*sDesc;
}	t_commit_action;

typedef struct s_commit_rule
{
	const char			*sPathPrefix;
	t_commit_action		actions[4]; // Index = t_commit_type
}	t_commit_rule;

static const t_commit_rule gCommitRules[] =
{
	{
		"docs/",
		{
			[COMMIT_ADD]    = { "docs", "📚", "Added documentation files" },
			[COMMIT_MODIFY] = { "docs", "📚", "Updated documentation files" },
			[COMMIT_DELETE] = { "docs", "🗑️", "Removed documentation files" },
			[COMMIT_RENAME] = { "docs", "🔄", "Renamed documentation files" }
		}
	},
	{
		"tools/",
		{
			[COMMIT_ADD]    = { "chore", "🔧", "Added internal tooling" },
			[COMMIT_MODIFY] = { "chore", "🔧", "Updated internal tooling" },
			[COMMIT_DELETE] = { "chore", "🗑️", "Removed internal tooling" },
			[COMMIT_RENAME] = { "chore", "🔄", "Renamed internal tooling" }
		}
	},
	{
		"lua/autorun/init.lua",
		{
			[COMMIT_ADD]    = { "feat", "🚀", "Added project initializer" },
			[COMMIT_MODIFY] = { "feat", "🚀", "Updated project initializer" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed project initializer" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed project initializer" }
		}
	},
	{
		"lua/weapons/",
		{
			[COMMIT_ADD]    = { "feat", "🔫", "Added weapon logic" },
			[COMMIT_MODIFY] = { "feat", "🔫", "Updated weapon logic" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed weapon logic" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed weapon logic" }
		}
	},
	{
		"lua/line_of_fire/base/",
		{
			[COMMIT_ADD]    = { "refactor", "♻️", "Added core base systems" },
			[COMMIT_MODIFY] = { "refactor", "♻️", "Updated core base systems" },
			[COMMIT_DELETE] = { "refactor", "🗑️", "Removed core base systems" },
			[COMMIT_RENAME] = { "refactor", "🔄", "Renamed core base systems" }
		}
	},
	{
		"lua/line_of_fire/subloaders/",
		{
			[COMMIT_ADD]    = { "feat", "🧩", "Added subloader system" },
			[COMMIT_MODIFY] = { "feat", "🧩", "Updated subloader system" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed subloader system" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed subloader system" }
		}
	},
	{
		"lua/line_of_fire/client/panels/",
		{
			[COMMIT_ADD]    = { "feat", "🪟", "Added client UI panel" },
			[COMMIT_MODIFY] = { "feat", "🪟", "Updated client UI panel" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed client UI panel" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed client UI panel" }
		}
	},
	{
		"lua/line_of_fire/client/",
		{
			[COMMIT_ADD]    = { "feat", "🖥️", "Added client system" },
			[COMMIT_MODIFY] = { "feat", "🖥️", "Updated client system" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed client system" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed client system" }
		}
	},
	{
		"lua/line_of_fire/classes/",
		{
			[COMMIT_ADD]    = { "feat", "🧱", "Added class definition" },
			[COMMIT_MODIFY] = { "feat", "🧱", "Updated class definition" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed class definition" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed class definition" }
		}
	},
	{
		"lua/line_of_fire/config/",
		{
			[COMMIT_ADD]    = { "chore", "⚙️", "Added project configuration" },
			[COMMIT_MODIFY] = { "chore", "⚙️", "Updated project configuration" },
			[COMMIT_DELETE] = { "chore", "🗑️", "Removed project configuration" },
			[COMMIT_RENAME] = { "chore", "🔄", "Renamed project configuration" }
		}
	},
	{
		"lua/line_of_fire/modules/player/managers/",
		{
			[COMMIT_ADD]    = { "feat", "🧑‍💼", "Added player manager" },
			[COMMIT_MODIFY] = { "feat", "🧑‍💼", "Updated player manager" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed player manager" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed player manager" }
		}
	},
	{
		"lua/line_of_fire/modules/player/modules/",
		{
			[COMMIT_ADD]    = { "feat", "🧬", "Added player module" },
			[COMMIT_MODIFY] = { "feat", "🧬", "Updated player module" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed player module" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed player module" }
		}
	},
	{
		"lua/line_of_fire/modules/",
		{
			[COMMIT_ADD]    = { "feat", "🧩", "Added server module" },
			[COMMIT_MODIFY] = { "feat", "🧩", "Updated server module" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed server module" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed server module" }
		}
	},
	{
		"lua/line_of_fire/nets/",
		{
			[COMMIT_ADD]    = { "feat", "📡", "Added network definition" },
			[COMMIT_MODIFY] = { "feat", "📡", "Updated network definition" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed network definition" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed network definition" }
		}
	},
	{
		"lua/line_of_fire/struct/base/",
		{
			[COMMIT_ADD]    = { "refactor", "🧱", "Added base entity structure" },
			[COMMIT_MODIFY] = { "refactor", "🧱", "Updated base entity structure" },
			[COMMIT_DELETE] = { "refactor", "🗑️", "Removed base entity structure" },
			[COMMIT_RENAME] = { "refactor", "🔄", "Renamed base entity structure" }
		}
	},
	{
		"lua/line_of_fire/struct/",
		{
			[COMMIT_ADD]    = { "feat", "🏗️", "Added project entity" },
			[COMMIT_MODIFY] = { "feat", "🏗️", "Updated project entity" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed project entity" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed project entity" }
		}
	},
	{
		"lua/line_of_fire/",
		{
			[COMMIT_ADD]    = { "feat", "🔥", "Added project logic" },
			[COMMIT_MODIFY] = { "feat", "🔥", "Updated project logic" },
			[COMMIT_DELETE] = { "feat", "🗑️", "Removed project logic" },
			[COMMIT_RENAME] = { "feat", "🔄", "Renamed project logic" }
		}
	},
	{ NULL }
};

#define ROOT_LUA_PREFIX "lua/"
#define FALLBACK_TAG "chore"
#define FALLBACK_EMOJI "🔧"
#define FALLBACK_DESC "Updated file"

#endif
