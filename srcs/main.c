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

	for (size_t i = 0; i < iFileCount; i++)
	{
		t_commit_type eType = eGitCharToType(pArrFiles[i].cStatus);
		char *sMsg = strBuildCommitMessage(pArrFiles[i].sPath, eType);
		if (!sMsg)
			continue;

		if (bSafeMode)
		{
			printf("[SAFE] %s\n", sMsg);
			free(sMsg);
			continue;
		}

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

		char sCmd[4096];
		switch (eType)
		{
			case COMMIT_ADD:
			case COMMIT_MODIFY:
				if (access(pArrFiles[i].sPath, F_OK) == 0)
					snprintf(sCmd, sizeof(sCmd),
						"git add \"%s\" && git commit -F \"%s\" -- \"%s\"",
						pArrFiles[i].sPath, sTmpName, pArrFiles[i].sPath);
				else
					snprintf(sCmd, sizeof(sCmd),
						"echo \"[SKIP] %s\"",
						pArrFiles[i].sPath);
				break;

			case COMMIT_DELETE:
				if (access(pArrFiles[i].sPath, F_OK) == 0)
					snprintf(sCmd, sizeof(sCmd),
						"git rm \"%s\" && git commit -F \"%s\" -- \"%s\"",
						pArrFiles[i].sPath, sTmpName, pArrFiles[i].sPath);
				else
					snprintf(sCmd, sizeof(sCmd),
						"git rm --cached \"%s\" && git commit -F \"%s\" -- \"%s\"",
						pArrFiles[i].sPath, sTmpName, pArrFiles[i].sPath);
				break;

			case COMMIT_RENAME:
			{
				char *sSpace = strchr(pArrFiles[i].sPath, ' ');
				if (sSpace)
				{
					*sSpace = '\0';
					const char *sOld = pArrFiles[i].sPath;
					const char *sNew = sSpace + 1;

					if (access(sNew, F_OK) == 0)
						snprintf(sCmd, sizeof(sCmd),
							"git add \"%s\" && git rm --cached \"%s\" && git commit -F \"%s\" -- \"%s\"",
							sNew, sOld, sTmpName, sNew);
					else
						snprintf(sCmd, sizeof(sCmd),
							"echo \"[SKIP RENAME] %s -> %s\"", sOld, sNew);
				}
				else
					snprintf(sCmd, sizeof(sCmd),
						"echo \"[INVALID R FORMAT] %s\"", pArrFiles[i].sPath);
				break;
			}

			default:
				snprintf(sCmd, sizeof(sCmd), "echo \"[UNKNOWN] %s\"", sMsg);
				break;
		}

		iRunGitCommand(sCmd);
		remove(sTmpName);
		free(sMsg);
	}

	vcFreeGitFiles(pArrFiles, iFileCount);
	return 0;
}
