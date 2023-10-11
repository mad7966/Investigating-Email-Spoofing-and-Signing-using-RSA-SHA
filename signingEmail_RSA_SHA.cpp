
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 256

//signing the email with RSA and SHA
double time=0;

double signature(char **hash, char **message, char *rsa_key, char *sha){
    int i = 0;
    int pid;
    time_t end_time, start_time;
    start_time=time(NULL);

    for(i=0;i<10;i++)
    {
        pid = fork();
        if(pid<0)
        {
            printf("i :%d\n", i);

            /*
           Executes the command openssl dgst -sha256 -sign "$(whoami)s Sign Key.key" -out sign.txt.sha256 sign.txt 
 */
            execl("/usr/bin/openssl","openssl","dgst",sha,"-sign",rsa_key,"-out",hash[i],message[i],NULL);
        }
        else
        {
            wait(pid,NULL, 0);
        }
        
    }
    end_time=time(NULL);
    time =(double)(end_time/3600 - start_time/3600);
return time;
}

//Verify the signed email with RSA and SHA
double verification(char **hash, char **message, char *rsa_key, char *sha){
    int i = 0;
    int pid;
    time_t end_time, start_time;
    start_time=time(NULL);
    for(i=0;i<10;i++)
    {
       	printf("i :%d\n", i);
        pid = fork();
        if(pid<0)
        {
            execl("/usr/bin/openssl","openssl","dgst",sha,"-verify",rsa_key,"-signature",hash[i],message[i],NULL);
        }
        else
        {
        	wait(pid,NULL, 0);
        }
        i++;
    }
    end_time=time(NULL);
    time =(double)(end_time/3600 - start_time/3600);
return time;
}

void main(){
    int i =0;
    double Total_Time = 0;
    char *Message[10];
    char *1024SHA1[10];
    char *1024SHA256[10];
    char *2048SHA1[10];
    char *2048SHA256[10];

    for(i=0;i<10;i++){
        inputMsg[i]= (char*)malloc(BUFFER_SIZE);
        1024SHA1[i]= (char*)malloc(BUFFER_SIZE);
        1024SHA256[i]= (char*)malloc(BUFFER_SIZE);
        2048SHA1[i]= (char*)malloc(BUFFER_SIZE);
        2048SHA256[i]= (char*)malloc(BUFFER_SIZE);
        sprintf(inputMsg[i],"Computer_Security/Project3/Data/mail %d.msg",i+1);
        sprintf(1024SHA1[i],"Computer_Security/Project3/1024SHA1/cipher.%d",i+1);
        sprintf(1024SHA256[i],"Computer_Security/Project3/1024SHA256/cipher.%d",i+1);
        sprintf(2048SHA1[i],"Computer_Security/Project3/2048SHA1/cipher.%d",i+1);
        sprintf(2048SHA256[i],"Computer_Security/Project3/2048SHA256/cipher.%d",i+1);
    }

    for (i=1;i<=5;i++){

        	// sha1 + RSA 1024 signing
            Total_Time = 0;
            Total_Time = signature(1024SHA1,Message,"rsaprivatekey1024.pem","-sha1");
            printf("Signing: Round %d of 1024+SHA1. Total Time: %lf \n",i,Total_Time);

            // sha1 + RSA 2048 signing
            Total_Time = 0;
			Total_Time = signature(2048SHA1,Message,"rsaprivatekey2048.pem","-sha1");
            printf("Signing: Round %d of 2048+SHA1. Total Time: %lf \n",i,Total_Time);

            // sha256 + RSA 1024 signing
            timeTaken = 0;
            timeTaken = signature(hash1024SHA256,Message,"rsaprivatekey1024.pem","-sha256");
            printf("Signing: Round %d of 1024+SHA256. Total Time: %lf \n",i,Total_Time);

            // sha256 + RSA 2048 signing
            timeTaken = 0;
            timeTaken = signature(hash2048SHA256,Message,"rsaprivatekey2048.pem","-sha256");
            printf("Signing: Round %d of 2048+SHA256. Total Time: %lf \n",i,Total_Time);
    }


    for(i=1;i<=5;i++){

            // sha1 + RSA 1024 verification
            timeTaken = 0;
            timeTaken = verification(1024SHA1,Message,"rsapublickey1024.pem","-sha1");
            printf("Signing: Round %d of 1024+SHA1. Total Time: %lf \n",i,Total_Time);

            // sha1 + RSA 2048 verification
            timeTaken = 0;
            timeTaken = verification(2048SHA1,Message,"rsapublickey2048.pem","-sha1");
            printf("Signing: Round %d of 2048+SHA1. Total Time: %lf \n",i,Total_Time);

            // sha256 + RSA 1024 verification
            timeTaken = 0;
            timeTaken = verification(1024SHA256,Message,"rsapublickey1024.pem","-sha256");
            printf("Signing: Round %d of 1024+SHA256. Total Time: %lf \n",i,Total_Time);

            // sha256 + RSA 2048 verification
            timeTaken = 0;
            timeTaken = verification(2048SHA256,Message,"rsapublickey2048.pem","-sha256");
            printf("Signing: Round %d of 2048+SHA256. Total Time: %lf \n",i,Total_Time);
    }

}
