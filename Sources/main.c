#include "../Headers/main.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define u 0
#define g 1
#define o 2

#define r 0
#define w 1
#define x 2

typedef struct _chmod
{
	unsigned short int
		who,
		what;
	bool grant;
}_chmod;

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("schmod: Syntax: u:rx o:rw <file> instead of:\nchmod {u+r,u-w,u+x,g-r,g-w,g-x,o+r,o-w,o+x} <file>");
		return -1;
	}
	else
	{
		//Processing
		const char 
			*_granted[] =
			{
				[u] = "u",
				[g] = "g",
				[o] = "o"
			},
			*_grant[] =
			{
				[r] = "r",
				[w] = "w",
				[x] = "x"
			};
		_chmod chmod[9];
		int i, j;

		//Revoking the 9 possible chmods
		for(i = 0; i < 9; i++)
			chmod[i] = (_chmod)
			{
				.who = i / 3,
				.what = i % 3,
				.grant = false
			};
		
		//Scrolling arguments to grant chmods from revoked
		for(i = 1; i < argc - 1; i++)
		{
			short int _who = -1;
			bool _what[3] =
			{
				[r] = false,
				[w] = false,
				[x] = false
			};
			
			//Detecting grantee
			if(strstr(argv[i], "u") != 0)
				_who = u;
			else if(strstr(argv[i], "g") != 0)
				_who = g;
			else if(strstr(argv[i], "o") != 0)
				_who = o;
			else 
			{
				printf("schmod: Neither r, w or x in granting argument: %s\nNo action has been done.", argv[i]);
				return -1;
			}
			
			//Detecting grant
			if(strstr(argv[i], "r") != 0)
				_what[r] = true;
			if(strstr(argv[i], "w") != 0)
				_what[w] = true;
			if(strstr(argv[i], "x") != 0)
				_what[x] = true;
			
			//Setting the right grant to 'true'
			for(j = 0; j < 9; j++)
				if(chmod[j].who == _who)
					//Once the good grantee/who{u,g,o} (in argument) is seleted
					//Grant the good offset corresponding to a grant/what{r,w,x}
					chmod[j].grant = _what[j % 3];
		}
		
		//Scrolling through established chmods to grant/revoke
		unsigned short int who = u, what;
		j = 0;
		while(who <= o)
		{
			//For each who
			what = r;
			while(what <= x)
			{
				//Apply what
				char launch[100] = "chmod ";

				//Granting or revoking
				strcat(launch, _granted[who]);
				if(chmod[j++].grant)
					strcat(launch, "+");
				else
					strcat(launch, "-");
				
				//Ending launched command
				strcat(launch, _grant[what++]);
				strcat(launch, " ");
				strcat(launch, argv[argc - 1]);
				
				//Launching command
				system(launch);
			}
			who++;
		}
	}

	return 0;
}
