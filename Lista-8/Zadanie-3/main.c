/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <glob.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>


//    /bin/tar -tf archiwum.tar Lista-4/build/ | awk '{print "/"$1}' | sed 's:/Lista-4/build::g' | cut -d $'/' -f 2 | uniq | awk '{print "/"$1}'


static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/Zadanie-1";

static char *rootdir = "";

size_t arraySize(char *array);

static int tar_getattr(const char *path, struct stat *stbuf)
{
	//printf("\nATTR: %s\n", path);

	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0)
	{
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
	}
	else
	{

		printf("\nPATH: %s\n", path);

		char pathNew[400];
		char execute[400];
		char result[400];

		int i;

		for (i = 0; i < 400; i++)
		{
			pathNew[i] = 0;
			execute[i] = 0;
		}

		memcpy(pathNew, path, arraySize(path));
		pathNew[0] = ' ';


		printf("\nNEW PATH: %s\n", pathNew);


		memcpy(execute, "/bin/tar -tvf ", arraySize("/bin/tar -tvf "));

		strncat(execute, rootdir, arraySize(rootdir));

		strncat(execute, pathNew, arraySize(pathNew));


		printf("\nEXECUTE: %s\n", execute);


		char *fp = popen(execute, "r");

		if (fp == NULL)
		{
			//printf("Failed to run command\n");
			exit(1);
		}

		while (fgets(result, sizeof(result) - 1, fp) != NULL)
		{
			break;
		}


		printf("\nRESULT: %s\n", result);

		if (result == NULL)
		{
			return -ENOENT;
		}


		if (result[0] == 'd')
		{
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;
		}
		else if (result[0] == '-')
		{

			char* split=strtok(result," ");
			char* word;
			int i = 0;

			while(split != NULL)
			{
				i++;
				word=split;
				if (i==3) {
					break;
				}
				split=strtok(NULL," ");

			}

			//printf("\nSIZE:%s\n", word);

			int size;
			sscanf(word, "%d", &size);


			stbuf->st_mode = S_IFREG | 0777;
			stbuf->st_nlink = 1;
			stbuf->st_size = size;
		}

	}

	return res;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	filler(buf, hello_path + 1, NULL, 0);

	return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi)
{
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	return 0;
}


size_t arraySize(char *array);

char *pathFix(char *path);

void shiftArray(char* array)
;

void deleteNewLine(char* array) ;

static int tar_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);

	if (strcmp(path, "/") == 0)
	{


		char pathNew[400];
		char path[1035];


		int i = 0;

		for (i = 0; i < 400; i++)
		{
			pathNew[i] = 0;
		}

		memcpy(pathNew, "/bin/tar --exclude=\"*/*\" -tf ", arraySize("/bin/tar --exclude=\"*/*\" -tf "));

		strncat(pathNew, rootdir, arraySize(rootdir));

		//cleanArray(pathNew);


		char *fp = popen(pathNew, "r");

		if (fp == NULL)
		{
			//printf("Failed to run command\n");
			exit(1);
		}

		while (fgets(path, sizeof(path) - 1, fp) != NULL)
		{


			//printf("\n%s\n", path);

			path[arraySize(path)] = NULL;

			filler(buf, pathFix(path) + 1, NULL, 0);

		}


	}
	else
	{


		printf("\n%s\n", path);


		//filler(buf, hello_path + 1, NULL, 0);

		char pathNew[3000];
		int i;
		for (i = 0; i < 3000; i++)
		{
			pathNew[i] = 0;
		}



		char temp[400];

		for (i = 0; i < 400; i++)
		{
			temp[i] = 0;
		}

		memcpy(temp, path, arraySize(path));
		temp[0] = ' ';


		memcpy(pathNew, "/bin/tar -tf ", arraySize("/bin/tar -tf "));

		strncat(pathNew, rootdir, arraySize(rootdir));

		strncat(pathNew, " ", arraySize(" "));

		strncat(pathNew, temp, arraySize(temp));


		strncat(pathNew, " | awk '{print \"/\"$1}' | sed 's:/", arraySize(" | awk '{print \"/\"$1}' | sed 's:/"));

        printf("\nTEMP1: %s\n", temp);

        shiftArray(temp);

        printf("\nTEMP2: %s\n", temp);

		strncat(pathNew, temp, sizeof(temp));

        strncat(pathNew, "::g' | cut -d $'/' -f 2 | uniq | awk '{print \"/\"$1}'", arraySize("::g' | cut -d $'/' -f 2 | uniq | awk '{print \"/\"$1}'"));

        strncat(pathNew, "", arraySize(""));

		printf("\nTESTTEST: %s\n", pathNew);



        char *fp = popen(pathNew, "r");


//        printf("\n%s\n", fp);

        if (fp == NULL)
        {
            printf("Failed to run command\n");
            exit(1);
        }

        char buff[512];

        bool pierwsza_linia = true;

		int ilosc = 0;

        while (fgets(buff, sizeof(buff), fp) != NULL)
        {
			ilosc++;

            if (pierwsza_linia) {
                pierwsza_linia = false;
                continue;
            }

           // deleteNewLine(buff);

            buff[arraySize(buff)] = NULL;

            printf("%s", buff);

            filler(buf, buff + 1, NULL, 0);

        }

	}


	return 0;
}

static int tar_read(const char *path, char *buf, size_t size, off_t offset,
		struct fuse_file_info *fi)
{

	FILE *fp;
	long lSize;
	char *buffer;

	size_t len;
	(void) fi;
//	if (strcmp(path, hello_path) != 0)
//		return -ENOENT;


	char execute[400] = {"tar xvf "};


	char temp[400];

	int i;

	for (i = 0; i < 400; i++)
	{
		temp[i] = 0;
	}

	memcpy(temp, path, arraySize(path));
	temp[0] = ' ';


	strncat(execute, rootdir, arraySize(rootdir));

	strncat(execute, " -C ", arraySize(" -C "));

	strncat(execute, " /tmp ", arraySize(" /tmp "));

	strncat(execute, temp, arraySize(temp));


	printf("\nEXECUTE: %s\n", execute);


		char* foo = popen(execute, "r");





	char filePath[600];

	for (i =0; i<=600; i++) {
		filePath[i] = '\0';
	}


	shiftArray(temp);

	memcpy(filePath, "/tmp/", arraySize("/tmp/"));
	strncat(filePath, temp, arraySize(temp));

	printf("\nFILEPATH: %s\n", filePath);

	if (filePath[arraySize(filePath)] == ' ') {
		filePath[arraySize(filePath)] = '\0';
	}
	if (filePath[arraySize(filePath)-1] == ' ') {
		filePath[arraySize(filePath)-1] = '\0';
	}


	fp = fopen ( filePath , "rb" );
	if( !fp ) {perror("FILE OPENING ERROR"); return 0;}

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );

	/* allocate memory for entire content */
	buffer = calloc( 1, lSize+1 );
	if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

/* copy the file into the buffer */
	if( 1!=fread( buffer , lSize, 1 , fp) )
		fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);


	printf("\n%s\n", buffer);


	len = strlen(buffer);



	if (offset < len)
	{
		if (offset + size > len) {
			size = len - offset;
		}
		memcpy(buf, buffer + offset, size);
		printf("\n:-)\n");
	} else {
		printf("\n:-(\n");
		size = 0;
	}

	fclose(fp);
	free(buffer);

	return size;
}



static int hello_read(const char *path, char *buf, size_t size, off_t offset,
		struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	len = strlen(hello_str);
	if (offset < len)
	{
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, hello_str + offset, size);
	} else
		size = 0;

	return size;
}


static struct fuse_operations hello_oper = {
		.readdir    = tar_readdir,
		.getattr = tar_getattr,
		.read		= tar_read,

};

int main(int argc, char *argv[])
{

	if ((argc < 3) || (argv[argc - 2][0] == '-') || (argv[argc - 1][0] == '-'))
		return -1;

	rootdir = realpath(argv[argc - 2], NULL);

	argv[argc - 2] = argv[argc - 1];
	argv[argc - 1] = NULL;
	argc--;

	return fuse_main(argc, argv, &hello_oper, NULL);
}

size_t arraySize(char *array)
{
	size_t i = 0;

	while ((int) array[i] >= 32 && (int) array[i] <= 125)
	{
		i++;
	}

	////printf("\n%d\n", (int) i);

	return i;
}

char *pathFix(char *path)
{

	char temp[400] = "/";
	strncat(temp, path, 300);

	char ukosnik[1];

	ukosnik[0] = temp[sizeof(temp)];

	int i = 1;

	for (i = 1; i <= sizeof(temp); i++)
	{
		if (temp[i] == '/')
		{
			temp[i] = '\0';
			break;
		}
	}


	//printf("\n\n%s\n\n", temp);

	return temp;

}

void shiftArray(char* array)
{

    int i;

	for (i = 0; i<400; i++)
	{
        array[i] = array[i+1];
	}

}

void deleteNewLine(char* array) {

    int i;

    for (i = 1; i < sizeof(array); i++)
    {
        if (array[i] == '\n')
        {
            array[i] = '\0';
            break;
        }
    }

}