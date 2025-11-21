#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auto_commit.h"
#include "git_utils.h"
#include "commit_builder.h"
#include "utf8.h"

static t_commit_type eGitCharToType(char c)
{
	switch (c)
	{
		case 'A': return COMMIT_ADD;
		case '?': return COMMIT_ADD;
		case 'M': return COMMIT_MODIFY;
		case 'D': return COMMIT_DELETE;
		case 'R': return COMMIT_RENAME;
		default:  return COMMIT_UNKNOWN;
	}
}

static void vPushTagPatch(void)
{
	char last_tag[128] = {0};
	char new_tag[128];
	int major=0, minor=0, patch=0;

	FILE *fp = popen("git tag --list \"v*\" --sort=-creatordate", "r");
	if (fp && fgets(last_tag, sizeof(last_tag), fp))
	{
		size_t len = strlen(last_tag);
		if (len > 0 && (last_tag[len-1]=='\n'||last_tag[len-1]=='\r'))
			last_tag[len-1] = 0;
		sscanf(last_tag, "v%d.%d.%d", &major, &minor, &patch);
	}
	if (fp) pclose(fp);

	patch++;
	snprintf(new_tag, sizeof(new_tag), "v%d.%d.%d", major, minor, patch);

	char cmd[256];
	snprintf(cmd, sizeof(cmd), "git tag -a %s -m \"Release %s\"", new_tag, new_tag);
	system(cmd);
	snprintf(cmd, sizeof(cmd), "git push origin %s", new_tag);
	system(cmd);
	printf("[TAG] %s\n", new_tag);
}

int main(int argc, char **argv)
{
	t_git_file *pArrFiles;
	size_t iFileCount;
	int bSafeMode = 0;

	if (argc > 1 && strcmp(argv[1], "--safe") == 0)
		bSafeMode = 1;

	vInitUtf8();
	pArrFiles = arrGetGitFiles(&iFileCount);
	if (!pArrFiles || iFileCount == 0)
	{
		printf("[INFO] Aucun fichier modifié détecté.\n");
		return 0;
	}

	for (size_t i=0; i<iFileCount; i++)
	{
		t_commit_type eType = eGitCharToType(pArrFiles[i].cStatus);
		char *sMsg = strBuildCommitMessage(pArrFiles[i].sPath, eType);
		if (!sMsg) continue;

		if (bSafeMode)
		{
			printf("[SAFE] %s\n", sMsg);
			free(sMsg);
			continue;
		}

		char cmd[2048];
		switch (eType)
		{
			case COMMIT_ADD:
			case COMMIT_MODIFY:
			case COMMIT_RENAME:
				snprintf(cmd, sizeof(cmd), "git add \"%s\" && git commit -m \"%s\" -- \"%s\"",
					pArrFiles[i].sPath, sMsg, pArrFiles[i].sPath);
				break;
			case COMMIT_DELETE:
				snprintf(cmd, sizeof(cmd), "git rm \"%s\" && git commit -m \"%s\" -- \"%s\"",
					pArrFiles[i].sPath, sMsg, pArrFiles[i].sPath);
				break;
			default:
				snprintf(cmd, sizeof(cmd), "echo \"[UNKNOWN] %s\"", sMsg);
				break;
		}

		iRunGitCommand(cmd);
		vPushTagPatch();
		free(sMsg);
	}

	vcFreeGitFiles(pArrFiles, iFileCount);
	return 0;
}