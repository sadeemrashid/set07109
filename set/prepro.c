
/* Name: Sadeem Rashid
   Matriculation: 40402246
*/







#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//struct is declared to store data for define names and values
 
typedef struct
{
	char name[50];
	char value[100];
} Dictionary;

int main(int argc , char ** argv )
{	
	FILE *infile = fopen (argv[2], "r");
	char *fileout = argv[2]; 
	fileout[strlen(fileout) - 1] = 'o'; //for output file to be .o
	FILE *ofile = fopen (fileout, "w");
	FILE *hfile;
	int no_empty_lines = 0;
	int no_of_comments = 0;
	char c;
	char i;
	char m;
	char header;
	char define;
	char cheader;
	char *headername;
	char *hname;
    char iterate[2] = "\"";
	char *definex;
	char define1[100];
	char include1[100];
	char space[2] = " ";
	int flagi = 0;
	int flagc = 0;
	int index = 0;
	
	//the loops are for the functioning of -i and -c as the argument is set to 2 by comparing i.e strcmp function 
	
   for(int i = 0; i < argc; i++)
	{
		
		if(strcmp(argv[i], "-i") == 0)
		{
			flagi = 1;
		}
		
		if(strcmp(argv[i], "-c") == 0)
		{
			flagc = 1;
		}
	}
	

  // while loop for check the line which reads #include the header name is copied read onto and opened as a newfile which i declared hfile
  // after opening the file it should copy all the content in the file and by function putc written onto the ofile which is my output
   
	while((header = fgetc(infile)) != EOF)
	{
		if(header == '#' && (header = fgetc(infile)) == 'i' && (header = fgetc(infile)) == 'n' && (header = fgetc(infile)) == 'c' 
		&& (header = fgetc(infile)) == 'l' && (header = fgetc(infile)) == 'u' 
		&& (header = fgetc(infile)) == 'd' && (header = fgetc(infile)) == 'e' && (header = fgetc(infile)) == ' ')
		
		{
			headername = fgets(include1, 100, infile); 
			hname = strtok(headername, iterate);
			hfile = fopen(hname, "r"); 
		      
			  while((cheader = fgetc(hfile)) != EOF)
				{
					putc(cheader, ofile);
				}	
			        putc('\n', ofile); 
		}	
	}
// while checks for the line #define and then fgets function called to read data and extracted into malloc memory spaces called by function of string copy
//strtok splits the arrays into tokens which makes it able to extract name and variable
	fseek(infile, 0, 0);
	Dictionary* dictionary = (Dictionary*)malloc(sizeof(Dictionary)*500);
	
	while((define = fgetc(infile)) != EOF)
	{
		if(define == '#' && (define = fgetc(infile)) == 'd' && (define = fgetc(infile)) == 'e' && (define = fgetc(infile)) == 'f' 
		&& (define = fgetc(infile)) == 'i' && (define = fgetc(infile)) == 'n' && (define = fgetc(infile)) == 'e' && (define= fgetc(infile)) == ' ')
		{
			
			fgets(define1, 100, infile);
			strcpy (dictionary[index].name , strtok(define1, space));
			strcpy(dictionary[index].value , strtok(NULL, space));
			
			
			//printf("%s\n", dictionary[index].name);
			//printf("%s\n", dictionary[index].value);
			
	        index++;
			
			
			
		}
	}

	//after storing the values loops for string pointers to replace them in the output file by calling function string concatenate function to 
   //look through the points of characters and begin to replace variables with the values and resume if anything else in the line 	
	      
	 char define2[200];  
	 char define3[200];
	 char *def2;
	 
	 fseek(infile, 0, 0);
	while(fgets(define2, 100, infile) != NULL)
	{
		for (int z = 0; z < index; z++)
		{ 
		
			char* def = strstr (define2, dictionary[z].name);	
			if( def == NULL )
			  
			{
				continue;
			} 
			
			for (int t=0; t<strlen(define2)+1 ; t++)
			{
				if(def != (define2 + t))
				{
					define3[t] = define2[t];
				}
				else
				{
					define3[t] = '\0';
					strcat(define3, dictionary[z].value);
					def2 = (strlen(dictionary[z].name) + def);
					strcat(define3, def2);
					
					//printf("%s\n",define3);
					
                } 
				// fscanf(infile,"%s",); 
				 //fputs(define3, ofile);
			}     
			     
			fputs(define3, ofile);
		}
		
	}

	
	//loop to check for if a line contains / or # which represents comments , include and define should be left from output file
	//all the other characters added to the output file
	fseek(infile, 0, 0);
	while ((m = fgetc(infile)) != EOF) 
    {
	    
		if(m == '/' || (m == '#'))
		{
			while ((m != '\n'))
			{
				m = fgetc(infile); 
			}
		}
        putc(m, ofile); 
    } 
//loop to count for the number of empty lines
 fseek(infile, 0, 0);
	while ((c = fgetc(infile)) != EOF)
	{
	   if (c == '\n')
	   {
	   

		      if((c = fgetc(infile)) == '\n')
			  {
			    // break;
				 
		      }
			  
		   no_empty_lines++;
			
       }
			
    }		
	// loop to count for the number of comments	   
  fseek(infile, 0, 0);
 while ((c = fgetc(infile)) != EOF)
    {
	  if (c == '/')
	    
		{
		  if ((c = fgetc(infile) == '/'))
		    {
              no_of_comments++;
            }
        }
    }
	
	
	
// printing the counted empty lines and comments	
 printf("total no of non empty lines: %d\n", no_empty_lines);
 printf("total no of comments: %d\n", no_of_comments);	  
		   
		   
      fclose (infile);
	  fclose (ofile);   
	  fclose (hfile);
	  return 0;
}	  

		   
		   