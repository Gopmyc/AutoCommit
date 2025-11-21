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
		char *sMsg = strBuildCommitMessage(arrFiles[i].sPath, eType);
		if (!sMsg) continue;

		if (bSafeMode)
		{
			printf("[SAFE] %s\n", sMsg);
			free(sMsg);
			continue;
		}

		char tmpFile[256];
		snprintf(tmpFile, sizeof(tmpFile), ".commitmsg_%lu_%zu.tmp", (unsigned long)time(NULL), i);
		FILE *f = fopen(tmpFile, "wb");
		if (!f) { free(sMsg); continue; }
		fwrite(sMsg, 1, strlen(sMsg), f);
		fclose(f);

		char cmd[2048];
		switch (eType)
		{
			case COMMIT_ADD:
			case COMMIT_MODIFY:
			case COMMIT_RENAME:
				snprintf(cmd, sizeof(cmd), "git add \"%s\" && git commit -F \"%s\" -- \"%s\"",
					arrFiles[i].sPath, tmpFile, arrFiles[i].sPath);
				break;
			case COMMIT_DELETE:
				if (access(arrFiles[i].sPath, F_OK) == 0)
					snprintf(cmd, sizeof(cmd), "git rm \"%s\" && git commit -F \"%s\" -- \"%s\"",
						arrFiles[i].sPath, tmpFile, arrFiles[i].sPath);
				else
					snprintf(cmd, sizeof(cmd), "git rm --cached \"%s\" && git commit -F \"%s\" -- \"%s\"",
						arrFiles[i].sPath, tmpFile, arrFiles[i].sPath);
				break;
			default:
				snprintf(cmd, sizeof(cmd), "echo \"[UNKNOWN] %s\"", sMsg);
				break;
		}

		iRunGitCommand(cmd);
		remove(tmpFile);
		free(sMsg);
	}

	vcFreeGitFiles(arrFiles, iFileCount);
	return 0;
}
