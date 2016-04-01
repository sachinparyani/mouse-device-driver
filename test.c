#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

int main(){

	char i =0;
	int bytes, left, middle, right;
	int fp = open("/dev/ourDev",O_RDWR);
	char buff[100];
	//printf("%s\n",buff);
	float current = 0.5;
	
	//bytes =read(fp,&buff[0],1);
	//printf("%s %d\n",buff, bytes);
	
	
	while(1){
	
	
	bytes = read(fp,&buff[0],1);
	printf("%c\n",buff[0]);
	if(bytes > 0)
        {
        	
            left = buff[0] & 0x1;
            right = buff[0] & 0x2;
            middle = buff[0] & 0x4;

			//printf("left = %d right = %d", left , right);
            //x = data[1];
            //y = data[2];
			if(right > 0)
			{
				char num[50];
				char cmd[1024] = "xrandr --output VGA1 --brightness ";
				current = current + 0.05;
				if(current > 1)
					current = 1;
				sprintf(num,"%f",current);
				strcat(cmd,num);
				system(cmd);
				//fprintf(fd1,"%f",current);
				//fclose(fd1);
			}
			
			else if(left > 0)
			{
				char num[50];
				char cmd[1024] = "xrandr --output VGA1 --brightness ";
				current = current - 0.05;
				if(current < 0)
					current = 0;
				sprintf(num,"%f",current);
				strcat(cmd,num);
				system(cmd);
				//fprintf(fd1,"%f",current);
			//	fclose(fd1);
			}
			
			else
			{
				
			}
		}	
		}
}
