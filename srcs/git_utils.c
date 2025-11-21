#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "git_utils.h"

#ifdef _WIN32
# define POPEN _popen
# define PCLOSE _pclose
#else
# define POPEN popen
# define PCLOSE pclose
#endif

static t_git_file *vcAppendFile(t_git_file *arr, size_t *piLen, size_t *piCap, const char *sPath, char cStatus)
{
	char *sDup = malloc(strlen(sPath) + 1);
	if (!sDup)
		return arr;
	strcpy(sDup, sPath);

	if (*piLen + 1 >= *piCap)
	{
		*piCap *= 2;
		t_git_file *pNew = realloc(arr, sizeof(t_git_file) * (*piCap));
		if (!pNew)
		{
			free(sDup);
			return arr;
		}
		arr = pNew;
	}

	arr[*piLen].sPath = sDup;
	arr[*piLen].cStatus = cStatus;
	(*piLen)++;
	return arr;
}

static void vcReadGitDiff(const char *sCmd, t_git_file **arr, size_t *piLen, size_t *piCap, int bRename)
{
	FILE *p = POPEN(sCmd, "r");
	if (!p)
		return;

	char buf[1024];
	while (fgets(buf, sizeof(buf), p))
	{
		size_t i = strlen(buf);
		while (i > 0 && (buf[i-1]=='\n'||buf[i-1]=='\r')) buf[--i]='\0';
		if (i < 2) continue;

		char cStatus = buf[0];
		char *sPath = buf + 1;
		while (*sPath=='\t'||*sPath==' ') sPath++;

		if (bRename && cStatus == 'R')
		{
			// Pour les fichiers renommés, on prend le chemin de destination (2ème colonne)
			char *sDest = strchr(sPath, '\t');
			if (!sDest)
				sDest = strchr(sPath, ' ');
			if (sDest)
			{
				while (*sDest=='\t'||*sDest==' ') sDest++;
				sPath = sDest;
			}
		}

		*arr = vcAppendFile(*arr, piLen, piCap, sPath, cStatus);
	}
	PCLOSE(p);
}

t_git_file *arrGetGitFiles(size_t *piCount)
{
	FILE *p;
	char buf[4096];
	size_t iCap = 32;
	size_t iLen = 0;
	t_git_file *arr;

	*piCount = 0;

	p = POPEN("git diff --name-status HEAD && git ls-files --others --exclude-standard", "r");
	if (!p)
		return NULL;

	arr = malloc(sizeof(t_git_file) * iCap);
	if (!arr)
	{
		PCLOSE(p);
		return NULL;
	}

	while (fgets(buf, sizeof(buf), p))
	{
		size_t i = strlen(buf);
		while (i > 0 && (buf[i - 1] == '\n' || buf[i - 1] == '\r'))
			buf[--i] = '\0';
		if (i == 0)
			continue;

		char cStatus = buf[0];
		char *sPath1 = NULL;
		char *sPath2 = NULL;

		if (cStatus == 'R') // renamed
		{
			// Format: R<score>\told_path\tnew_path
			char *tab1 = strchr(buf, '\t');
			if (!tab1) continue;
			char *tab2 = strchr(tab1 + 1, '\t');
			if (!tab2) continue;

			*tab2 = '\0';
			sPath1 = tab1 + 1; // old
			sPath2 = tab2 + 1; // new
		}
		else if (cStatus == '?' || cStatus == 'M' || cStatus == 'A' || cStatus == 'D')
		{
			// tab-separated after status
			char *tab = buf + 1;
			while (*tab == '\t' || *tab == ' ')
				tab++;
			sPath1 = tab;
		}
		else
		{
			continue;
		}

		if (iLen + 1 >= iCap)
		{
			iCap *= 2;
			t_git_file *pNew = realloc(arr, sizeof(t_git_file) * iCap);
			if (!pNew) break;
			arr = pNew;
		}

		if (cStatus == 'R')
		{
			arr[iLen].sPath = strdup(sPath2);
			arr[iLen].cStatus = cStatus;
		}
		else
		{
			arr[iLen].sPath = strdup(sPath1);
			arr[iLen].cStatus = cStatus;
		}
		if (!arr[iLen].sPath) continue;
		iLen++;
	}

	PCLOSE(p);
	if (iLen == 0)
	{
		free(arr);
		return NULL;
	}

	*piCount = iLen;
	return arr;
}

int iRunGitCommand(const char *sCmd)
{
	if (!sCmd)
		return 1;
	return system(sCmd);
}

void vcFreeGitFiles(t_git_file *arr, size_t iCount)
{
	for (size_t i = 0; i < iCount; i++)
		free(arr[i].sPath);
	free(arr);
}
