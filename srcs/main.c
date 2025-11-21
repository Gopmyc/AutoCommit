#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
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

int main(int argc, char **argv)
{
	t_git_file *arrFiles;
	size_t iFileCount;
	int bSafeMode = 0;

	if (argc > 1 && strcmp(argv[1], "--safe") == 0)
		bSafeMode = 1;

	vInitUtf8();

	arrFiles = arrGetGitFiles(&iFileCount);
	if (!arrFiles || iFileCount == 0)
	{
		printf("[INFO] Aucun fichier modifié détecté.\n");
		return 0;
	}

	for (size_t i = 0; i < iFileCount; i++)
	{
		t_commit_type eType = eGitCharToType(arrFiles[i].cStatus);
		int exists = (access(arrFiles[i].sPath, F_OK) == 0);

		char *sMsg = strBuildCommitMessage(arrFiles[i].sPath, eType);
		if (!sMsg) continue;

		// Mode debug safe
		if (bSafeMode)
		{
			printf("[SAFE DEBUG] %zu | status='%c' | exists=%d | path='%s'\n",
				i, arrFiles[i].cStatus, exists, arrFiles[i].sPath);
			printf("[SAFE DEBUG] commit message: %s\n", sMsg);
			free(sMsg);
			continue;
		}

		// Skip deleted files that no longer exist on disk
		if (eType == COMMIT_DELETE && !exists)
		{
			printf("[SKIP] Deleted file not on disk: %s\n", arrFiles[i].sPath);
			free(sMsg);
			continue;
		}

		// Création d’un fichier temporaire pour commit
		char sTmpName[256];
		snprintf(sTmpName, sizeof(sTmpName), ".commitmsg_%lu_%zu.tmp", (unsigned long)time(NULL), i);

		FILE *pTmp = fopen(sTmpName, "wb");
		if (!pTmp)
		{
			free(sMsg);
			continue;
		}
		fwrite(sMsg, 1, strlen(sMsg), pTmp);
		fclose(pTmp);

		char sCmd[2048];
		switch (eType)
		{
			case COMMIT_ADD:
			case COMMIT_MODIFY:
			case COMMIT_RENAME:
				snprintf(sCmd, sizeof(sCmd),
					"git add \"%s\" && git commit -F \"%s\" -- \"%s\"",
					arrFiles[i].sPath, sTmpName, arrFiles[i].sPath);
				break;
			case COMMIT_DELETE:
				snprintf(sCmd, sizeof(sCmd),
					"git rm \"%s\" && git commit -F \"%s\" -- \"%s\"",
					arrFiles[i].sPath, sTmpName, arrFiles[i].sPath);
				break;
			default:
				snprintf(sCmd, sizeof(sCmd), "echo \"[UNKNOWN] %s\"", sMsg);
				break;
		}

		iRunGitCommand(sCmd);
		remove(sTmpName);
		free(sMsg);
	}

	vcFreeGitFiles(arrFiles, iFileCount);
	return 0;
}
