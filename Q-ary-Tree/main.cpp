#include <string.h>
#include "stdio.h"
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#include <iostream>
#include <string>

const int tagnum=100;
const int idlong=8;
int collisionnum=0;

char answer[idlong+1];
struct node{
	bool sleep;
	char id[idlong+1];

};
struct node tag[tagnum];

void request(char tag_command[],int tag_com_bitnum)
{
	int tag_tran;
	for (tag_tran=0;tag_tran<tagnum;tag_tran++)
	{
		if (tag[tag_tran].sleep&&strcmp(tag_command,tag[tag_tran].id)<=0)
			break;

	}
	if (tag_tran==tagnum)
	{
		return;
	}

	for(int i=0;i<idlong;i++)
	{
		for(int j=0;j<tagnum-1;j++)
		{

			if (tag[j].sleep&&strcmp(tag_command,tag[j].id)<=0)
			{

				for (int k=j+1;k<tagnum;k++)
					if(tag[k].sleep&&strcmp(tag_command,tag[k].id)<=0)
					{
						if (tag[j].id[i]!=tag[k].id[i])
						{collisionnum++;
						answer[i]='*';
						break;
						}

					}
					else continue;
					if (answer[i]=='*')
						break;
			}
			else continue;

		}
	if (answer[i]=='*')
	continue;
	else
	answer[i]=tag[tag_tran].id[i];
	}
	answer[idlong]='\0';

}

void creatID()
{
	int i;
	int j;
	//printf("GENERATED RANDOM TAGS:\n");
	int cnt = 1;

	for( i=0;i<tagnum;i++)
	{
		tag[i].sleep=true;
		for(j=0;j<idlong;j++)
			tag[i].id[j]=rand()%2+48;
		tag[i].id[idlong]='\0';
		////printf("ID %d :%s\n",i+1,tag[i].id);
	}

}

void generateTags()
{
	int i;
	int j;
	printf("                        GENERATED RANDOM TAGS\n");
	int cnt = 1;

    for(int a=1;a<=20;a++)
    {
        for(int b=1;b<=5;b++)
        {
            printf("|-------------");
        }
        printf("|\n");
        //printf("|-------------|-------------|-------------|-------------|-------------|\n");

        for(int b=1;b<=5;b++)
        {
            if(cnt<10) printf("|  %d=%s ",cnt, tag[cnt].id);
            if(cnt>=10) printf("| %d=%s ",cnt, tag[cnt].id);
            if(cnt==100) printf("|%d=%s ",cnt, tag[cnt].id);

            cnt++;
        }
        printf("|\n");


        //printf("| 01=10100101 | 02=10100101 | 03=10100101 | 04=10100101 | 05=10100101 |\n");
        //printf("|-------------|-------------|-------------|-------------|-------------|\n");

        for(int b=1;b<=5;b++)
        {
            printf("|-------------");
        }
        printf("|\n");

    }

}


int main()
{

	 creatID();
 generateTags();


	int i;
	int delid=0;
	int clearnu;
	char tag_commandbit[idlong+1]="";

	int  befor_bit[idlong][2];

	int befor_tagnum=0;
		befor_bit[befor_tagnum][1]=1;


	int out_num=0;
	for (clearnu=0;clearnu<idlong;clearnu++)
	{
		tag_commandbit[clearnu]='0';
	}
	tag_commandbit[idlong]='\0';


	int request_num=1;
	int befor_bitnum=0;

	for (clearnu=0;clearnu<idlong;clearnu++)
	{
		answer[clearnu]=' ';
	}

	request(tag_commandbit,idlong);

			for (clearnu=0;clearnu<idlong;clearnu++)
			{
				tag_commandbit[clearnu]=' ';
			}

	while (request_num>0)
	{

		if (befor_tagnum>0&&befor_bit[befor_tagnum-1][1]==0)
		{
			for(i=0;i<befor_bit[befor_tagnum-1][0];i++)
				tag_commandbit[i]=answer[i];

			tag_commandbit[i]='0';
			for (clearnu=0;clearnu<idlong;clearnu++)
			{
				answer[clearnu]=' ';
			}

			request(tag_commandbit,i+1);

			for (clearnu=0;clearnu<idlong;clearnu++)
			{
				tag_commandbit[clearnu]=' ';
			}

		}


		while (collisionnum>1)
		{
            printf("\ncollisionnum>1 = %s",tag[i].id);
			for(i=0;i<idlong;i++)
			{

				if (answer[i]=='*')
				{
					tag_commandbit[i]='1';
					collisionnum=0;
					request_num++;

					for (clearnu=0;clearnu<idlong;clearnu++)
					{
						answer[clearnu]=' ';
					}

					request(tag_commandbit,i+1);

 					for (clearnu=0;clearnu<idlong;clearnu++)
					{
						tag_commandbit[clearnu]=' ';
					}

					befor_bit[befor_tagnum][0]=i;
					befor_bit[befor_tagnum][1]=1;
					befor_tagnum++;
					break;
				}

				tag_commandbit[i]=answer[i];

			}

		}



		if (collisionnum==0)
		{
			request_num--;
			if( answer[0]!=' ')
			{	out_num++;
			printf("\nsuccessful     = ");
			printf("%s\n",answer);




				for (int look_cout=befor_tagnum-1;look_cout>=0;look_cout--)
				{
                    printf("\nsuccessful     = %s",tag[i].id);
					if (befor_bit[look_cout][1]==1)
					{
						befor_tagnum=look_cout+1;
						befor_bit[look_cout][1]=0;
						break;
					}

				}

			}

			for (delid=0;delid<tagnum;delid++)
			{
                    ////printf("answer2");
				if (strcmp(tag[delid].id,answer)==0)
				{
					tag[delid].sleep=false;
					break;
				}
			}


		}

		else if(collisionnum==1)
		{
            printf("\ncollisionnum=1 = %s",tag[i].id);
			collisionnum=0;

				for (int look_cout=befor_tagnum-1;look_cout>=0;look_cout--)
				{
					if (befor_bit[look_cout][1]==1)
					{
						befor_tagnum=look_cout+1;
						befor_bit[look_cout][1]=0;
						break;
					}

				}


			for (i=0;i<idlong;i++)
			{
				if (answer[i]=='*')
				{
					answer[i]='1';
					out_num++;
					printf("\nsuccessful     = ");
					printf("%s\n",answer);



					request_num--;


					for (delid=0;delid<tagnum;delid++)
					{
						if (strcmp(tag[delid].id,answer)==0)
						{
							tag[delid].sleep=false;
							break;
						}
					}

					answer[i]='0';
					out_num++;
					printf("\nsuccessful     = ");
					printf("%s\n",answer);


				//	if(befor_tagnum!=0)
					//	befor_tagnum--;

					for (int delid=0;delid<tagnum;delid++)
					{
						if (strcmp(tag[delid].id,answer)==0)
						{
							tag[delid].sleep=false;
							break;
						}
					}
				break;
				}


			}
			//read(id)

		}

	}
	return 0;
   //system("pause");
}
